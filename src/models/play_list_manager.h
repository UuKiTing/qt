#ifndef PLAY_LIST_MANAGER_H
#define PLAY_LIST_MANAGER_H

#include "global.h"
#include "dbmanager.h"
#include "collectfilter_proxy_model.h"
#include "searchfilter_proxy_model.h"
#include "song_list_proxy_model.h"
#include <QObject>
#include <QStandardItemModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

class PlayListManager : public QObject
{
    Q_OBJECT

public:
    explicit PlayListManager(QObject *parent = nullptr);

    void setCurrentRow(int row); // 设置model当前的行号
    void setIsPlayingData(const QModelIndex &index, bool isPlaying); // 设置正在播放标识
    int setNextRow(bool isNext); // 设置下一首歌曲的行号
    void setMode(PlayMode mode); // 设置播放模式
    void setData(QAbstractItemModel *model, const QModelIndex &index, const QVariant &value, int role = Role::Invalid); // 设置model数据
    void setIsSource(bool isSource);
    void setRows(const QVector<int> &rows);

    QAbstractItemModel* model(); // 返回model
    CollectFilterProxyModel* collectModel(); // 返回收藏过滤model
    SearchFilterProxyModel* searchModel(); // 返回搜索过滤model
    SongListProxyModel* songlistModel(); // 返回歌单过滤model
    int modelRowCount(); // 返回model行数
    QStandardItem* item(int row); // 返回指定行的item
    QModelIndex index(); // 返回当前行的index
    int currentRow(); // 返回当前行号
    PlayMode mode(); // 返回播放模式

signals:
    void modeChanged(PlayMode mode); // 播放模式更改信号

private:
    void loadPlayList(); // 加载音乐列表

    void generateData(); // 生成音乐数据
    QJsonObject parseMusic(const QString &filePath); // 解析音乐文件

    QStandardItemModel *m_model;
    CollectFilterProxyModel *m_collectModel;
    SearchFilterProxyModel *m_searchModel;
    SongListProxyModel *m_songlistModel;
    DbManager *m_dbManager;

    int m_curRow = -1; // 当前行号

    QVector<int> m_rows;

    int m_isSource = true; // 是否为源模型

    PlayMode m_mode = PlayMode::Loop; // 播放模式
};

#endif // PLAY_LIST_MANAGER_H
