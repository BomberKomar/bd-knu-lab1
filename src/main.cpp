#include <iostream>

#include "Shell.hpp"
#include "Command.hpp"
#include "MusicRecordRepository.hpp"
#include "MusicAlbumRepository.hpp"

int main()
{
    MusicRecordRepository *musicRecordRepository;
    MusicAlbumRepository *musicAlbumRepository;

    musicRecordRepository = new MusicRecordRepository(musicAlbumRepository);
    musicAlbumRepository = new MusicAlbumRepository(musicRecordRepository);

    musicRecordRepository->load();
    musicAlbumRepository->load();

    auto shell = Shell(
        {new GetAllMusicRecordsCommand(*musicRecordRepository),
         new GetOneMusicRecordCommand(*musicRecordRepository),
         new UpdateMusicRecordCommand(*musicRecordRepository),
         new RemoveMusicRecordCommand(*musicRecordRepository),
         new InsertMusicRecordCommand(*musicRecordRepository),
         new CountMusicRecordsCommand(*musicRecordRepository),
         new GetAllMusicAlbumsCommand(*musicAlbumRepository),
         new GetOneMusicAlbumCommand(*musicAlbumRepository),
         new UpdateMusicAlbumCommand(*musicAlbumRepository),
         new RemoveMusicAlbumCommand(*musicAlbumRepository),
         new InsertMusicAlbumCommand(*musicAlbumRepository),
         new CountMusicAlbumsCommand(*musicAlbumRepository)});

    shell.run();

    return 0;
}