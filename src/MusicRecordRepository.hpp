#pragma once

#include "Repository.hpp"
#include "ForeignIdViolationException.hpp"

class MusicAlbumRepository;

struct MusicRecordStructure
{
  int albumId;
  char name[100];
  int duration;
};

class MusicRecordRepository : public Repository<MusicRecordStructure>
{
public:
  MusicRecordRepository(MusicAlbumRepository *&musicAlbumRepository);

  void insert(int id, const MusicRecordStructure &record) override;
  void update(const int &id, const MusicRecordStructure &updatedRecord) override;

private:
  MusicAlbumRepository *&musicAlbumRepository;
};