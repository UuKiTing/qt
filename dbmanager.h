#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "global.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QModelIndex>
// sk-e172d8271bd74146ac571d6024d1e3d7
class DbManager
{
public:
    static DbManager& getInstance();

    QList<SongInfo> loadSongs();

    void appendMusicData(const SongInfo &info); // 添加新歌曲
    void collectSong(const QModelIndex &index); // 收藏歌曲
    void disCollectSong(const QModelIndex &index); // 取消歌曲收藏

    PlayListInfo createSongList(int user_id, const QString &name); // 创建一个歌单
    QList<PlayListInfo> queryPlayLists(int user_id); // 查询该用户的所有歌单
    PlayListInfo  queryOneOfPlaylists(int user_id, const QString &name); // 查询该用户的某个歌单
    QSet<int> queryCollectedSongs(int playlist_id); // 查询该歌单下的所有歌曲id
    void addSongToPlaylist(int palylist_id, int song_id); // 添加歌曲到歌单
    void updatePlaylistCover(const QString &path, int playlist_id); // 更新歌单封面

    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

private:
    QSqlDatabase m_db;

    explicit DbManager();
    ~DbManager();

};

#endif // DBMANAGER_H
