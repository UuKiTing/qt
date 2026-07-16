#include "dbmanager.h"
#include "global.h"
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

    int count = query.record().count();

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
        qWarning() << "Insert failed:" << query.lastError().text();
        return;
    }
}



DbManager::~DbManager()
{

}

