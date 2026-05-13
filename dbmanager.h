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
    explicit DbManager(QObject *parent = nullptr);

    QList<SongInfo> loadSongs();

signals:

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
