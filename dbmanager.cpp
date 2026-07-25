#include "dbmanager.h"
#include <QStandardPaths>
#include <QSqlRecord>
#include <QCoreApplication>
#include <QDir>


DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    QDir dir = QDir(QCoreApplication::applicationDirPath());
    m_db.setDatabaseName(dir.filePath("music.db"));

    if(!m_db.open()){
        qCritical() << "数据库打开失败: " << m_db.lastError().text();
        QCoreApplication::quit();  // ✅ 无法继续运行
        return;
    }
}


DbManager &DbManager::getInstance()
{
    static DbManager db;
    return db;
}

QList<SongInfo> DbManager::loadSongs()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM songs LEFT JOIN (SELECT music_id FROM collection WHERE user_id = :user_id) as coll "
                  "ON coll.music_id = songs.id;");
    query.bindValue(":user_id", 1);

    if(!query.exec()){
        qDebug() << "Load songs failed:" << query.lastError().text();
        return {};
    }


    QList<SongInfo> list;

    while(query.next()){
        SongInfo info;
        info.id = query.record().value("id").toInt();
        info.title = query.record().value("title").toString();
        info.artist = query.record().value("artist").toString();
        info.duration = query.record().value("duration").toInt();
        info.filePath = query.record().value("filePath").toString();
        info.cover = query.record().value("cover").toString();
        info.lyrics = query.record().value("lyrics").toString();
        if(query.record().value("music_id").toInt())
            info.isFavo = true;
        else
            info.isFavo = false;

        list.append(info);
    }

    return list;
}


void DbManager::appendMusicData(const SongInfo &info)
{
    QSqlQuery query;
    query.prepare("INSERT INTO songs VALUES(:id, :title, :artist, :duration, :filePath, :cover, :lyrics)");
    query.bindValue(":id", info.id);
    query.bindValue(":title", info.title);
    query.bindValue(":artist", info.artist);
    query.bindValue(":duration", info.duration);
    query.bindValue(":filePath", info.filePath);
    query.bindValue(":cover", info.cover);
    query.bindValue(":lyrics", info.lyrics);

    if(!query.exec()){
        qWarning() << "Insert failed:" << query.lastError().text();
        return;
    }
}

void DbManager::collectSong(const QModelIndex &index)
{
    QSqlQuery query;
    query.prepare("INSERT INTO collection (user_id, music_id)VALUES(:user_id, :music_id)");
    query.bindValue(":user_id", 1);
    query.bindValue(":music_id", index.data(Role::Id));
    if(!query.exec()){
        qWarning() << "Insert failed:" << query.lastError().text();
        return;
    }
}

void DbManager::disCollectSong(const QModelIndex &index)
{
    QSqlQuery query;
    query.prepare("DELETE FROM collection WHERE user_id = :user_id AND music_id = :music_id");
    query.bindValue(":user_id", 1);
    query.bindValue(":music_id", index.data(Role::Id).toInt());
    if(!query.exec()){
        qWarning() << "Delete failed:" << query.lastError().text();
        return;
    }
}

PlayListInfo DbManager::createSongList(int user_id, const QString &name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO playlists (user_id, name, cover_path) VALUES(:user_id, :name, :cover_path);");
    query.bindValue(":user_id", user_id);
    query.bindValue(":name", name);
    query.bindValue(":cover_path", ":/icon/cover.png");

    if(!query.exec()){
        qWarning() << "Insert failed:" << query.lastError().text();
        return {};
    }

    return queryOneOfPlaylists(user_id, name);
}

QList<PlayListInfo> DbManager::queryPlayLists(int user_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM playlists WHERE user_id = :user_id;");
    query.bindValue(":user_id", user_id);

    if(!query.exec()){
        qWarning() << "Select failed:" << query.lastError().text();
        return {};
    }

    QList<PlayListInfo> list;

    while(query.next()){
        PlayListInfo info;

        info.id = query.record().value("id").toInt();
        info.name = query.record().value("name").toString();
        info.cover = query.record().value("cover_path").toString();

        list.append(info);
    }

    return list;
}

PlayListInfo DbManager::queryOneOfPlaylists(int user_id, const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM playlists WHERE user_id = :user_id AND name = :name;");
    query.bindValue(":user_id", user_id);
    query.bindValue(":name", name);

    PlayListInfo info;

    if(!query.exec()){
        qWarning() << "SELECT failed:" << query.lastError().text();
        return info;
    }

    if (!query.next()) {
        qWarning() << "Playlist not found:" << name;
        return {};
    }

    info.id = query.record().value("id").toInt();
    info.name = query.record().value("name").toString();
    info.cover = query.record().value("cover_path").toString();

    return info;
}

QSet<int> DbManager::queryCollectedSongs(int playlist_id)
{
    QSqlQuery query;
    query.prepare(R"(
        SELECT s.id, s.title, s.artist, ps.sort_order
        FROM songs s
        JOIN playlist_songs ps ON s.id = ps.song_id
        WHERE ps.playlist_id = :playlist_id
        ORDER BY ps.sort_order DESC;
)");

    query.bindValue(":playlist_id", playlist_id);

    QSet<int> set;

    if(!query.exec()){
        qWarning() << "Select failed:" << query.lastError().text();
        return set;
    }


    while(query.next()){
        set.insert(query.record().value("id").toInt());
    }

    return set;
}

void DbManager::addSongToPlaylist(int palylist_id, int song_id)
{
    QSqlQuery query;
    query.prepare(R"(
    INSERT INTO playlist_songs (playlist_id, song_id, sort_order)
    VALUES (
        :playlist_id,
        :song_id,
        COALESCE((SELECT MAX(sort_order) FROM playlist_songs WHERE playlist_id = :playlist_id), 0) + 1
    );
)");

    query.bindValue(":playlist_id", palylist_id);
    query.bindValue(":song_id", song_id);

    if(!query.exec()){
        qWarning() << "Insert failed:" << query.lastError().text();
        return;
    }
}

void DbManager::updatePlaylistCover(const QString &path, int playlist_id)
{
    QSqlQuery query;
    query.prepare("UPDATE playlists SET cover_path = :cover_path WHERE id = :playlist_id;");
    query.bindValue(":cover_path", path);
    query.bindValue(":playlist_id", playlist_id);

    if(!query.exec()){
        qWarning() << "Update failed:" << query.lastError().text();
        return;
    }
}




DbManager::~DbManager()
{

}

