#include "dbmanager.h"
#include <QStandardPaths>

DbManager::DbManager(QObject *parent)
    : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("music.db");

    if(!m_db.open()){
        qDebug() << "数据库打开失败：" << m_db.lastError().text();
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
    query.exec("SELECT * FROM songs");
    QList<SongInfo> list;

    while(query.next()){
        SongInfo info;
        info.id = query.value(0).toInt();
        info.title = query.value(1).toString();
        info.artist = query.value(2).toString();
        info.duration = query.value(3).toInt();
        info.filePath = query.value(4).toString();
        info.cover = query.value(5).toString();

        list.append(info);
    }

    return list;
}

void DbManager::appendData(const SongInfo &info)
{
    QSqlQuery query;
    query.prepare("insert into songs values(:id, :title, :artist, :duration, :filePath, :cover)");
    query.bindValue(":id", info.id);
    query.bindValue(":title", info.title);
    query.bindValue(":artist", info.artist);
    query.bindValue(":duration", info.duration);
    query.bindValue(":filePath", info.filePath);
    query.bindValue(":cover", info.cover);
    query.exec();
}

DbManager::~DbManager()
{
    QString connectName = m_db.connectionName();
    m_db.close();
    QSqlDatabase::removeDatabase(connectName);
}

