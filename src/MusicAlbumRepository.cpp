#include "MusicRecordRepository.hpp"
#include "MusicAlbumRepository.hpp"

MusicAlbumRepository::MusicAlbumRepository(MusicRecordRepository *&musicRecordRepository) : Repository("M.ind", "M.grb", "M.fl"),
                                                                                            musicRecordRepository(musicRecordRepository) {}

void MusicAlbumRepository::remove(const int &id)
{
  auto musicRecordItems = this->musicRecordRepository->getAll();

  for (auto &musicRecordItem : musicRecordItems)
  {
    if (std::get<1>(musicRecordItem).albumId != id)
    {
      continue;
    }

    this->musicRecordRepository->remove(std::get<0>(musicRecordItem));
  }

  this->Repository<MusicAlbumStructure>::remove(id);

  this->musicRecordRepository->save();
}
