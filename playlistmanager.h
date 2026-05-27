#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "global.h"
#include "dbmanager.h"
#include "collectfilterproxymodel.h"
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


    void loadPlayList(); // 加载音乐列表

    void generateData(); // 生成音乐数据
    QJsonObject parseMusic(const QString &filePath); // 解析音乐文件

    void setCurrentRow(int row); // 设置model当前的行号
    void setIsPlayingData(const QModelIndex &index, bool isPlaying);
    int setNextRow(bool isNext);
    void setMode(PlayMode mode);
    void setData(QAbstractItemModel *model, const QModelIndex &index, const QVariant &value, int role = Role::Invalid);


    QAbstractItemModel* model();
    QAbstractItemModel* collectModel();
    int modelRowCount();
    QStandardItem* item(int row);
    QModelIndex index();
    int currentRow();
    PlayMode mode();

signals:
    void modeChanged(PlayMode mode);

private:
    QStandardItemModel *m_model;
    // QStandardItemModel *m_collectModel;
    CollectFilterProxyModel *m_collectModel;
    DbManager *m_dbManager;

    int curRow = -1;

    PlayMode Mode = PlayMode::Loop; // 播放模式
};

#endif // PLAYLISTMANAGER_H
