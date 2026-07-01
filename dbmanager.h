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
private:
    QSqlDatabase m_db;

    explicit DbManager();
    ~DbManager();

};

#endif // DBMANAGER_H
