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
