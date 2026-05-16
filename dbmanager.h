#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "global.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

class DbManager : public QObject
{
    Q_OBJECT
public:


    static DbManager& getInstance();

    QList<SongInfo> loadSongs();

    void appendData(const SongInfo &info);


signals:

private:
    QSqlDatabase m_db;

    explicit DbManager(QObject *parent = nullptr);
    ~DbManager();

};

#endif // DBMANAGER_H
