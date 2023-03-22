#include "MusicAlbumRepository.hpp"
#include "ForeignIdViolationException.hpp"
#include "MusicRecordRepository.hpp"

MusicRecordRepository::MusicRecordRepository(MusicAlbumRepository *&musicAlbumRepository) : Repository<MusicRecordStructure>("S.ind", "S.grb", "S.fl"),
                                                                                            musicAlbumRepository(musicAlbumRepository) {}

void MusicRecordRepository::insert(int id, const MusicRecordStructure &record)
{
  if (!this->musicAlbumRepository->exists(record.albumId))
  {
    throw ForeignIdViolationException();
  }

  this->Repository<MusicRecordStructure>::insert(id, record);
}

void MusicRecordRepository::update(const int &id, const MusicRecordStructure &updatedRecord)
{
  if (!this->musicAlbumRepository->exists(updatedRecord.albumId))
  {
    throw ForeignIdViolationException();
  }

  this->Repository<MusicRecordStructure>::update(id, updatedRecord);
}
