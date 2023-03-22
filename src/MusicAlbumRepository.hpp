#pragma once

#include <tuple>

#include "Repository.hpp"

class MusicRecordRepository;

struct MusicAlbumStructure
{
  char name[100];
  char authorName[100];
};

class MusicAlbumRepository : public Repository<MusicAlbumStructure>
{
public:
  MusicAlbumRepository(MusicRecordRepository *&musicRecordRepository);

  void remove(const int &id) override;

private:
  MusicRecordRepository *&musicRecordRepository;
};