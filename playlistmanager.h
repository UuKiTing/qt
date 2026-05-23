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
    void loadCollectPlayList();
    void generateData();
    QJsonObject parseMusic(const QString &filePath);
    void addCollectSong(const QModelIndex &index);
    bool removeCollectSong(const QModelIndex &index);

    void setCurrentRow(int row); // 设置model当前的行号
    void setIsPlayingData(const QModelIndex &index, bool isPlaying);
    void setCollectData(const QModelIndex &index, bool isCollect);
    int setNextRow(bool isNext);
    void setMode(PlayMode mode);
    void setData(QStandardItemModel *model, const QModelIndex &index, const QVariant &value, int role = Role::Invalid);


    QStandardItemModel* model();
    QStandardItemModel* collectModel();
    int modelRowCount();
    QStandardItem* item(int row);
    QModelIndex index();
    int currentRow();
    PlayMode mode();

signals:
    void modeChanged(PlayMode mode);

private:
    QStandardItemModel *m_model;
    QStandardItemModel *m_collectModel;
    DbManager *m_dbManager;

    int curRow = -1;

    PlayMode Mode = PlayMode::Loop; // 播放模式
};

#endif // PLAYLISTMANAGER_H
