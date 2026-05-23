#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "global.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QModelIndex>

class DbManager : public QObject
{
    Q_OBJECT
public:


    static DbManager& getInstance();

    QList<SongInfo> loadSongs();
    QList<SongInfo> loadCollectSongs();

    void appendMusicData(const SongInfo &info);
    void collectSong(const QModelIndex &index);
    void disCollectSong(const QModelIndex &index);


signals:

private:
    QSqlDatabase m_db;

    explicit DbManager(QObject *parent = nullptr);
    ~DbManager();

};

#endif // DBMANAGER_H
