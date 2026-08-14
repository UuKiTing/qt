#include "dbmanager.h"
#include "logging.h"
#include <QStandardPaths>
#include <QSqlRecord>
#include <QCoreApplication>
#include <QDir>
#include <QSqlTableModel>


DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    // WARNING: 当前数据库放在了程序同级目录，发布前必须迁移到 QStandardPaths 标准路径下
    QDir dir = QDir(QCoreApplication::applicationDirPath());
    m_db.setDatabaseName(dir.filePath("music.db"));

    if(!m_db.open()){
        qCCritical(dbLog) << "数据库打开失败: " << m_db.lastError().text();
        m_isValid = false;
        return;
    }

    m_isValid = true;

    createUsersTable();
    createSongTable();
    createCollectionTable();
    createPlaylistsTable();
    createPlaylistSongTable();
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
        qCWarning(dbLog) << "加载歌曲信息失败：" << query.lastError().text();
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

bool DbManager::isValid()
{
    return m_isValid;
}


bool DbManager::appendMusicData(const SongInfo &info)
{
    m_db.transaction(); // 开启事务
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
        m_db.rollback();
        qCWarning(dbLog) << "插入数据到歌曲表中失败：" << query.lastError().text();
        return false;
    }

    if(!m_db.commit()){
        m_db.rollback();
        qCWarning(dbLog) << "事务提交失败：" << query.lastError().text();
        return false;
    }

    return true;
}

bool DbManager::collectSong(const QModelIndex &index)
{
    m_db.transaction(); // 开启事务
    QSqlQuery query;
    query.prepare("INSERT INTO collection (user_id, music_id)VALUES(:user_id, :music_id)");
    query.bindValue(":user_id", 1);
    query.bindValue(":music_id", index.data(Role::Id));

    if(!query.exec()){
        m_db.rollback();
        qCWarning(dbLog) << "收藏失败：" << query.lastError().text();
        return false;
    }

    if(!m_db.commit()){
        m_db.rollback();
        qCWarning(dbLog) << "事务提交失败：" << query.lastError().text();
        return false;
    }


    return true;
}

bool DbManager::disCollectSong(const QModelIndex &index)
{
    m_db.transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM collection WHERE user_id = :user_id AND music_id = :music_id");
    query.bindValue(":user_id", 1);
    query.bindValue(":music_id", index.data(Role::Id).toInt());

    if(!query.exec()){
        m_db.rollback();
        qCWarning(dbLog) << "取消收藏失败：" << query.lastError().text();
        return false;
    }

    if(!m_db.commit()){
        m_db.rollback();
        qCWarning(dbLog) << "事务提交失败：" << query.lastError().text();
        return false;
    }
    return true;
}

PlayListInfo DbManager::createSongList(int user_id, const QString &name)
{
    m_db.transaction(); // 开启事务
    QSqlQuery query;

    query.prepare("INSERT INTO playlists (user_id, name, cover_path) VALUES(:user_id, :name, :cover_path);");
    query.bindValue(":user_id", user_id);
    query.bindValue(":name", name);
    query.bindValue(":cover_path", ":/icon/cover.png");

    if(!query.exec()){
        m_db.rollback();
        qCWarning(dbLog) << "创建歌单失败：" << query.lastError().text();
        return {};
    }

    if(!m_db.commit()){
        m_db.rollback();
        qCWarning(dbLog) << "事务提交失败：" << query.lastError().text();
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
        qCWarning(dbLog) << "查询所有歌单失败：" << query.lastError().text();
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
        qCWarning(dbLog) << "歌单查找失败：" << query.lastError().text();
        return info;
    }

    info.id = query.record().value("id").toInt();
    info.name = query.record().value("name").toString();
    info.cover = query.record().value("cover_path").toString();

    return info;
}

QSet<int> DbManager::queryPlaylistSongId(int playlist_id)
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
        qCWarning(dbLog) << "查询歌单列表id失败：" << query.lastError().text();
        return {};
    }


    while(query.next())
        set.insert(query.record().value("id").toInt());

    return set;
}

bool DbManager::insertSongToPlaylist(int palylist_id, int song_id)
{
    m_db.transaction();
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
        m_db.rollback();
        qCWarning(dbLog) << "插入歌曲到歌单列表中失败：" << query.lastError().text();
        return false;
    }

    if(!m_db.commit()){
        m_db.rollback();
        qCWarning(dbLog) << "事务提交失败：" << query.lastError().text();
        return false;
    }

    return true;
}

bool DbManager::updatePlaylistCover(const QString &path, int playlist_id)
{
    m_db.transaction();
    QSqlQuery query;
    query.prepare("UPDATE playlists SET cover_path = :cover_path WHERE id = :playlist_id;");
    query.bindValue(":cover_path", path);
    query.bindValue(":playlist_id", playlist_id);

    if(!query.exec()){
        m_db.rollback();
        qCWarning(dbLog) << "更新歌单封面失败：" << query.lastError().text();
        return false;
    }

    if(!m_db.commit()){
        m_db.rollback();
        qCWarning(dbLog) << "事务提交失败：" << query.lastError().text();
        return false;
    }

    return true;
}

int DbManager::queryPlaylistSongCount(int playlist_id)
{
    QSqlQuery query;
    query.prepare(R"(
        SELECT count(*)
        FROM songs s
        JOIN playlist_songs ps ON s.id = ps.song_id
        WHERE ps.playlist_id = :playlist_id;
)");

    query.bindValue(":playlist_id", playlist_id);

    if(!query.exec()){
        qCWarning(dbLog) << "查询歌单歌曲数量失败:" << query.lastError().text();
        return -1;
    }

    return query.next() ? query.value(0).toInt() : -1;
}

bool DbManager::deletePlaylist(int playlist_id)
{
    m_db.transaction();
    QSqlQuery query;
    query.prepare("DELETE FROM playlists WHERE id = :playlist_id;");
    query.bindValue(":playlist_id", playlist_id);

    if(!query.exec()){
        m_db.rollback();
        qCWarning(dbLog) << "删除歌单失败：" << query.lastError().text();
        return false;
    }

    if(!m_db.commit()){
        m_db.rollback();
        qCWarning(dbLog) << "事务提交失败：" << query.lastError().text();
        return false;
    }

    return true;
}

void DbManager::createUsersTable()
{
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS users(
            int integer primarykey increment,
            username text not null
            );
    )";

    if(!query.exec(sql)){
        qCWarning(dbLog) << "创建 users 表失败::" << query.lastError().text();
        return;
    }
}

void DbManager::createSongTable()
{
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS songs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            artist TEXT,
            duration INTEGER,
            filePath TEXT,
            cover TEXT,
            lyrics text
            );
    )";

    if(!query.exec(sql)){
        qCWarning(dbLog) << "创建 songs 表失败:" << query.lastError().text();
        return;
    }
}

void DbManager::createCollectionTable()
{
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS collection (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            music_id INTEGER NOT NULL,
            FOREIGN KEY (user_id) REFERENCES users(id),
            FOREIGN KEY (music_id) REFERENCES songs(id),
            UNIQUE (user_id, music_id)
            );
    )";

    if(!query.exec(sql)){
        qCWarning(dbLog) << "创建 collection 表失败:" << query.lastError().text();
        return;
    }
}

void DbManager::createPlaylistsTable()
{
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS playlists (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            cover_path TEXT
        );
    )";

    if(!query.exec(sql)){
        qCWarning(dbLog) << "创建 playlists 表失败:" << query.lastError().text();
        return;
    }
}

void DbManager::createPlaylistSongTable()
{
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS playlist_songs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            playlist_id INTEGER NOT NULL,
            song_id INTEGER NOT NULL,
            sort_order INTEGER NOT NULL DEFAULT 0,
            FOREIGN KEY (playlist_id) REFERENCES playlists(id) ON DELETE CASCADE,
            FOREIGN KEY (song_id) REFERENCES songs(id) ON DELETE CASCADE
        );
    )";

    if(!query.exec(sql)){
        qCWarning(dbLog) << "创建 playlist_songs 表失败:" << query.lastError().text();
        return;
    }
}


DbManager::~DbManager()
{
}

