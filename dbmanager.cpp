#include "dbmanager.h"
#include "global.h"
#include <QStandardPaths>
#include <QSqlRecord>


DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("music.db");

    if(!m_db.open()){
        qWarning() << "数据库打开失败：" << m_db.lastError().text();
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

    int count = query.record().count();

    QList<SongInfo> list;

    while(query.next()){
        SongInfo info;
        info.id = query.value(0).toInt();
        info.title = query.value(1).toString();
        info.artist = query.value(2).toString();
        info.duration = query.value(3).toInt();
        info.filePath = query.value(4).toString();
        info.cover = query.value(5).toString();
        info.lyrics = query.value(6).toString();
        if(query.value(count - 1).toInt()) info.isFavo = true;
        else info.isFavo = false;

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
    query.exec();
}

void DbManager::collectSong(const QModelIndex &index)
{
    QSqlQuery query;
    query.prepare("INSERT INTO collection (user_id, music_id)VALUES(:user_id, :music_id)");
    query.bindValue(":user_id", 1);
    query.bindValue(":music_id", index.data(Role::Id));
    query.exec();
}

void DbManager::disCollectSong(const QModelIndex &index)
{
    QSqlQuery query;
    query.prepare("DELETE FROM collection WHERE user_id = :user_id AND music_id = :music_id");
    query.bindValue(":user_id", 1);
    query.bindValue(":music_id", index.data(Role::Id).toInt());
    query.exec();
}



DbManager::~DbManager()
{

}

