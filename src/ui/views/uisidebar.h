#ifndef UISIDEBAR_H
#define UISIDEBAR_H

#include "global.h"
#include <QWidget>
#include <QButtonGroup>
#include <QDialog>
#include <QMenu>

namespace Ui {
class UISideBar;
class Dialog;
}


Q_DECLARE_METATYPE(PlayListInfo)

class UISideBar : public QWidget
{
    Q_OBJECT

public:
    explicit UISideBar(QWidget *parent = nullptr);
    ~UISideBar();

    QAbstractButton* findPlaylist(int playlist_id); // 查找歌单
    int findPlaylistOrder(QAbstractButton *btn);

    void setPlaylistCover(const QString &path, int playlist_id); // 设置歌单封面

signals:
    void pageChanged(int pageIndex); // 页面切换信号
    void playlistClicked(const PlayListInfo &info); // 歌单点击信号
    void playlistUpdated(const QSet<int> &songIds); // 更新歌单列表内容
    void playlistCreated(const PlayListInfo &inf); // 歌单创建信号
    void playlistDeleted(int playlist_id); // 歌单删除信号
    void playlistPlayed();

private slots:
    void on_addSongBtn_clicked(); // 添加歌曲按钮点击槽函数

private:
    void connectSignals(); // 连接信号与槽
    void initMainBtn();
    void toggleToHomePage(bool checked); // 切换到主页
    void toggleToCollectPage(bool checked); // 切换到收藏页
    void toggleToNetworkPage(bool checked); // 切换到联网页
    void createPlayList(const PlayListInfo &info); // 创建歌单
    void initContextMenu(); // 初始化右键菜单
    void clearInputBox(); // 清空输入框
    void rightClickPlaylist(QAction *action); // 添加音乐到歌单

    Ui::UISideBar *ui;
    Ui::Dialog *m_dialog; // 创建歌单模态框UI对象

    QDialog *m_songListDialog{}; // m_dialog的父窗口，用于显示歌单模态框

    QButtonGroup *m_group{}; // 按钮组

    QMenu *m_contextMenu{}; // 右键菜单
};

#endif // UISIDEBAR_H
