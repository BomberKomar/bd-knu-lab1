#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <algorithm>

#include "NotFoundException.hpp"
#include "IdViolationException.hpp"

#define IndexItem std::tuple<int, int>

template <typename T>
class Repository
{
public:
  Repository(
      const std::string &indexFileName,
      const std::string &garbageFileName,
      const std::string &dataFileName) : index(NULL),
                                         garbage(NULL),
                                         indexFileName(indexFileName),
                                         garbageFileName(garbageFileName),
                                         dataFileName(dataFileName)
  {
  }

  ~Repository()
  {
    if (this->index != NULL)
    {
      delete this->index;
    }
  }

  T getOne(const int &id)
  {
    const auto position = this->getPositionById(id);
    auto dataStream = this->getDataStream();
    auto result = this->getOneByPosition(dataStream, position);
    dataStream.close();

    return result;
  }

  std::vector<std::tuple<int, T>> getAll()
  {
    std::vector<std::tuple<int, T>> result = std::vector<std::tuple<int, T>>();
    auto dataStream = this->getDataStream();

    for (auto indexItem : *this->index)
    {
      auto id = std::get<0>(indexItem);
      auto position = std::get<1>(indexItem);

      if (this->garbageContainsPosition(position))
      {
        continue;
      }

      auto record = this->getOneByPosition(dataStream, position);

      result.push_back(
          std::tuple<int, T>(
              std::get<0>(indexItem), record));
    }

    dataStream.close();

    return result;
  }

  virtual void remove(const int &id)
  {
    const auto &position = this->getPositionById(id);

    this->index->erase(std::remove(this->index->begin(), this->index->end(), std::tuple<int, int>(id, position)), this->index->end());
    this->garbage->push_back(position);
  }

  virtual void insert(int id, const T &record)
  {
    if (!this->exists(id))
    {
      if (this->garbage->size() == 0)
      {
        this->index->push_back(std::tuple<int, int>(
            id,
            this->pushContent(record)));
      }
      else
      {
        int position = this->garbage->front();
        this->updateByPosition(position, record);
        this->index->push_back(std::tuple<int, int>(id, position));
        this->garbage->erase(this->garbage->begin());
      }
    }
    else
    {
      throw IdViolationException();
    }
  }

  bool exists(const int &id)
  {
    for (auto &indexItem : *this->index)
    {
      if (std::get<0>(indexItem) == id)
      {
        return !this->garbageContainsPosition(std::get<1>(indexItem));
      }
    }

    return false;
  }

  void load()
  {
    this->loadIndex();
    this->loadGarbage();
  }

  void save()
  {
    this->saveIndex();
    this->saveGarbage();
  }

  virtual void update(const int &id, const T &updatedRecord)
  {
    const auto &position = this->getPositionById(id);
    this->updateByPosition(position, updatedRecord);
  }

  size_t count()
  {
    return this->index->size();
  }

private:
  void updateByPosition(const int &position, const T &updatedRecord)
  {
    auto dataStream = this->getDataStream();
    dataStream.seekp(position * sizeof(T));

    dataStream.write(reinterpret_cast<const char *>(&updatedRecord), sizeof(T));
    dataStream.close();
  }
  bool
  garbageContainsPosition(const int &position)
  {
    for (auto &garbagePosition : *this->garbage)
    {
      if (garbagePosition == position)
      {
        return true;
      }
    }

    return false;
  }

  T getOneByPosition(std::fstream &dataStream, int position)
  {
    T *result = new T();
    dataStream.seekg(position * sizeof(T));
    dataStream.read(reinterpret_cast<char *>(result), sizeof(T));

    return *result;
  }

  int pushContent(const T &record)
  {
    auto dataStream = this->getDataStream();
    dataStream.seekp(0, std::ios_base::end);

    int position = dataStream.tellp() / sizeof(T);

    this->writeRecordToStream(record, dataStream);

    dataStream.close();

    return position;
  }

  void writeRecordToStream(const T &record, std::fstream &dataStream)
  {
    dataStream.write(reinterpret_cast<const char *>(&record), sizeof(T));
  }

  int getPositionById(const int &id)
  {
    for (auto &indexItem : *this->index)
    {
      if (std::get<0>(indexItem) == id)
      {
        if (this->garbageContainsPosition(std::get<1>(indexItem)))
        {

          throw NotFoundException();
        }

        return std::get<1>(indexItem);
      }
    }

    throw NotFoundException();
  }

  void saveIndex()
  {
    this->clearIndexFile();

    auto indexStream = this->getIndexStream();

    for (auto indexItem : *this->index)
    {
      indexStream.write(reinterpret_cast<char *>(&std::get<0>(indexItem)), sizeof(int));
      indexStream.write(reinterpret_cast<char *>(&std::get<1>(indexItem)), sizeof(int));
    }

    indexStream.close();
  }

  void loadIndex()
  {
    auto indexStream = this->getIndexStream();

    if (this->index == NULL)
    {
      this->index = new std::vector<std::tuple<int, int>>();
    }
    else
    {
      this->index->clear();
    }

    while (!indexStream.eof())
    {
      int key;
      int position;

      indexStream.read(reinterpret_cast<char *>(&key), sizeof(key));
      indexStream.read(reinterpret_cast<char *>(&position), sizeof(position));

      if (indexStream.eof())
      {
        break;
      }

      this->index->push_back({key, position});
    }

    indexStream.close();
  }

  void loadGarbage()
  {
    auto garbageStream = this->getGarbageStream();

    if (this->garbage == NULL)
    {
      this->garbage = new std::vector<int>();
    }
    else
    {
      this->garbage->clear();
    }

    while (!garbageStream.eof())
    {
      int position;

      garbageStream.read(reinterpret_cast<char *>(&position), sizeof(position));

      if (garbageStream.eof())
      {
        break;
      }

      this->garbage->push_back(position);
    }

    garbageStream.close();
  }

  void saveGarbage()
  {
    this->clearGarbageFile();

    auto garbageStream = this->getGarbageStream();

    for (auto garbageItem : *this->garbage)
    {
      garbageStream.write(reinterpret_cast<char *>(&garbageItem), sizeof(int));
    }

    garbageStream.close();
  }

  std::fstream getIndexStream()
  {
    return std::fstream(this->indexFileName, std::ios::in | std::ios::out | std::ios::binary);
  }

  void clearIndexFile()
  {
    auto stream = std::fstream(this->indexFileName, std::ios::out | std::ios::binary | std::ios::trunc);
    stream.close();
  }

  std::fstream getGarbageStream()
  {
    return std::fstream(this->garbageFileName, std::ios::in | std::ios::out | std::ios::binary);
  }

  void clearGarbageFile()
  {
    auto stream = std::fstream(this->garbageFileName, std::ios::out | std::ios::binary | std::ios::trunc);
    stream.close();
  }

  std::fstream getDataStream()
  {
    return std::fstream(this->dataFileName, std::ios::in | std::ios::out | std::ios::binary);
  }

  std::vector<IndexItem> *index;
  std::vector<int> *garbage;
  std::string indexFileName;
  std::string garbageFileName;
  std::string dataFileName;
};
