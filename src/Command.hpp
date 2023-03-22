#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cstring>

#include "UnexpectedArgumentsException.hpp"
#include "Argument.hpp"
#include "StringArgument.hpp"
#include "NumberArgument.hpp"
#include "MusicRecordRepository.hpp"
#include "MusicAlbumRepository.hpp"

class Command
{
public:
  virtual std::string execute(const std::vector<Argument *> &arguments) const = 0;
  virtual std::string getText() const = 0;
};

class GetAllMusicRecordsCommand : public Command
{
public:
  GetAllMusicRecordsCommand(MusicRecordRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "ut-s";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    auto records = this->repository->getAll();

    std::stringstream resultStream;

    for (auto record : records)
    {
      auto id = std::get<0>(record);
      auto data = std::get<1>(record);

      resultStream << id << ' ' << data.albumId << ' ' << data.name << ' ' << data.duration << '\n';
    }

    return resultStream.str();
  }

private:
  MusicRecordRepository *repository;
};

class InsertMusicRecordCommand : public Command
{
public:
  InsertMusicRecordCommand(MusicRecordRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "insert-s";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 4 ||
        arguments[0]->getType() != ArgumentType::Number ||
        arguments[1]->getType() != ArgumentType::Number ||
        arguments[2]->getType() != ArgumentType::String ||
        arguments[3]->getType() != ArgumentType::Number)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);
    auto albumIdArgument = static_cast<NumberArgument *>(arguments[1]);
    auto nameArgument = static_cast<StringArgument *>(arguments[2]);
    auto durationArgument = static_cast<NumberArgument *>(arguments[3]);

    MusicRecordStructure record;

    std::memcpy(record.name,
                nameArgument->getValue().c_str(),
                sizeof(char) * nameArgument->getValue().size() + 1);

    record.duration = durationArgument->getValue();
    record.albumId = albumIdArgument->getValue();

    this->repository->insert(idArgument->getValue(), record);
    this->repository->save();

    return "Inserted one music record.\n";
  }

private:
  MusicRecordRepository *repository;
};

class GetOneMusicRecordCommand : public Command
{
public:
  GetOneMusicRecordCommand(MusicRecordRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "get-s";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 1 ||
        arguments[0]->getType() != ArgumentType::Number)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);

    const auto &record = this->repository->getOne(idArgument->getValue());

    std::stringstream resultStream;

    resultStream << idArgument->getValue() << ' ' << record.albumId << ' ' << record.name << ' ' << record.duration << '\n';

    return resultStream.str();
  }

private:
  MusicRecordRepository *repository;
};

class UpdateMusicRecordCommand : public Command
{
public:
  UpdateMusicRecordCommand(MusicRecordRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "update-s";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 4 ||
        arguments[0]->getType() != ArgumentType::Number ||
        arguments[1]->getType() != ArgumentType::Number ||
        arguments[2]->getType() != ArgumentType::String ||
        arguments[3]->getType() != ArgumentType::Number)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);
    auto albumIdArgument = static_cast<NumberArgument *>(arguments[1]);
    auto nameArgument = static_cast<StringArgument *>(arguments[2]);
    auto durationArgument = static_cast<NumberArgument *>(arguments[3]);

    MusicRecordStructure record;

    std::memcpy(record.name,
                nameArgument->getValue().c_str(),
                sizeof(char) * nameArgument->getValue().size() + 1);

    record.duration = durationArgument->getValue();
    record.albumId = albumIdArgument->getValue();

    this->repository->update(idArgument->getValue(), record);
    this->repository->save();

    return "Updated one music record.\n";
  }

private:
  MusicRecordRepository *repository;
};

class RemoveMusicRecordCommand : public Command
{
public:
  RemoveMusicRecordCommand(MusicRecordRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "del-s";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 1 ||
        arguments[0]->getType() != ArgumentType::Number)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);

    this->repository->remove(idArgument->getValue());
    this->repository->save();

    return "Deleted one music record.\n";
  }

private:
  MusicRecordRepository *repository;
};

class CountMusicRecordsCommand : public Command
{
public:
  CountMusicRecordsCommand(MusicRecordRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "calc-s";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {

    std::stringstream resultStream;

    resultStream << this->repository->count() << '\n';

    return resultStream.str();
  }

private:
  MusicRecordRepository *repository;
};

class GetAllMusicAlbumsCommand : public Command
{
public:
  GetAllMusicAlbumsCommand(MusicAlbumRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "ut-m";
  }

  std::string execute(const std::vector<Argument *> &arguments) const override
  {
    auto records = this->repository->getAll();

    std::stringstream resultStream;

    for (auto record : records)
    {
      auto id = std::get<0>(record);
      auto data = std::get<1>(record);

      resultStream << id << ' ' << data.name << ' ' << data.authorName << '\n';
    }

    return resultStream.str();
  }

private:
  MusicAlbumRepository *repository;
};

class InsertMusicAlbumCommand : public Command
{
public:
  InsertMusicAlbumCommand(MusicAlbumRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "insert-m";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 3 ||
        arguments[0]->getType() != ArgumentType::Number ||
        arguments[1]->getType() != ArgumentType::String ||
        arguments[2]->getType() != ArgumentType::String)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);
    auto nameArgument = static_cast<StringArgument *>(arguments[1]);
    auto authorNameArgument = static_cast<StringArgument *>(arguments[2]);

    MusicAlbumStructure record;

    std::memcpy(record.name,
                nameArgument->getValue().c_str(),
                sizeof(char) * nameArgument->getValue().size() + 1);

    std::memcpy(record.authorName,
                authorNameArgument->getValue().c_str(),
                sizeof(char) * authorNameArgument->getValue().size() + 1);

    this->repository->insert(idArgument->getValue(), record);
    this->repository->save();

    return "Inserted one music album.\n";
  }

private:
  MusicAlbumRepository *repository;
};

class GetOneMusicAlbumCommand : public Command
{
public:
  GetOneMusicAlbumCommand(MusicAlbumRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "get-m";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 1 ||
        arguments[0]->getType() != ArgumentType::Number)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);

    const auto &record = this->repository->getOne(idArgument->getValue());

    std::stringstream resultStream;

    resultStream << idArgument->getValue() << ' ' << record.name << ' ' << record.authorName << '\n';

    return resultStream.str();
  }

private:
  MusicAlbumRepository *repository;
};

class UpdateMusicAlbumCommand : public Command
{
public:
  UpdateMusicAlbumCommand(MusicAlbumRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "update-m";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 3 ||
        arguments[0]->getType() != ArgumentType::Number ||
        arguments[1]->getType() != ArgumentType::String ||
        arguments[2]->getType() != ArgumentType::String)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);
    auto nameArgument = static_cast<StringArgument *>(arguments[1]);
    auto authorNameArgument = static_cast<StringArgument *>(arguments[2]);

    MusicAlbumStructure record;

    std::memcpy(record.name,
                nameArgument->getValue().c_str(),
                sizeof(char) * nameArgument->getValue().size() + 1);

    std::memcpy(record.authorName,
                authorNameArgument->getValue().c_str(),
                sizeof(char) * authorNameArgument->getValue().size() + 1);

    this->repository->update(idArgument->getValue(), record);
    this->repository->save();

    return "Updated one music album.\n";
  }

private:
  MusicAlbumRepository *repository;
};

class RemoveMusicAlbumCommand : public Command
{
public:
  RemoveMusicAlbumCommand(MusicAlbumRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "del-m";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {
    if (arguments.size() != 1 ||
        arguments[0]->getType() != ArgumentType::Number)
    {
      throw UnexpectedArgumentsException();
    }

    auto idArgument = static_cast<NumberArgument *>(arguments[0]);

    this->repository->remove(idArgument->getValue());
    this->repository->save();

    return "Deleted one album record.\n";
  }

private:
  MusicAlbumRepository *repository;
};

class CountMusicAlbumsCommand : public Command
{
public:
  CountMusicAlbumsCommand(MusicAlbumRepository &repository) : repository(&repository) {}

  virtual std::string getText() const override
  {
    return "calc-m";
  }

  virtual std::string execute(const std::vector<Argument *> &arguments) const override
  {

    std::stringstream resultStream;

    resultStream << this->repository->count() << '\n';

    return resultStream.str();
  }

private:
  MusicAlbumRepository *repository;
};
