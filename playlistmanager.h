#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "global.h"
#include "dbmanager.h"
#include <QObject>
#include <QStandardItemModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class PlayListManager : public QObject
{
    Q_OBJECT

public:
    explicit PlayListManager(QObject *parent = nullptr);


    void loadPlayList();
    void generateData();
    QJsonObject parseMusic(const QString &filePath);


    void setCurrentRow(int row); // 设置model当前的行号
    void setIsPlayingData(const QModelIndex &index, bool isPlaying);
    void setCollectData(const QModelIndex &index, bool isCollect);
    int setNextRow(bool isNext);
    void setMode(PlayMode mode);


    QStandardItemModel* model();
    int modelRowCount();
    QStandardItem* item(int row);
    int currentRow();
    PlayMode mode();

signals:
    void modeChanged(PlayMode mode);

private:
    QStandardItemModel *m_model;
    DbManager *m_dbManager;

    int curRow = -1;

    PlayMode Mode = PlayMode::Loop; // 播放模式
};

#endif // PLAYLISTMANAGER_H
