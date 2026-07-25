#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "global.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QModelIndex>

class DbManager
{
public:
    static DbManager& getInstance();

    QList<SongInfo> loadSongs();

    void appendMusicData(const SongInfo &info);
    void collectSong(const QModelIndex &index);
    void disCollectSong(const QModelIndex &index);

    PlayListInfo createSongList(int user_id, const QString &name);
    QList<PlayListInfo> queryPlayLists(int user_id);
    PlayListInfo  queryOneOfPlaylists(int user_id, const QString &name);
    QSet<int> queryCollectedSongs(int playlist_id);
    void addSongToPlaylist(int palylist_id, int song_id);

    void updatePlaylistCover(const QString &path, int playlist_id);

    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

private:
    QSqlDatabase m_db;

    explicit DbManager();
    ~DbManager();

};

#endif // DBMANAGER_H
