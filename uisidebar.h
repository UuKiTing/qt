#ifndef UISIDEBAR_H
#define UISIDEBAR_H

#include "global.h"
#include <QWidget>
#include <QButtonGroup>
#include <QDialog>

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

    void connectSignals(); // 连接信号与槽

    void createPlayList(PlayListInfo &info); // 创建歌单

signals:
    void pageChanged(int pageIndex); // 页面切换信号
    void playlistClicked(const PlayListInfo &info); // 歌单点击信号
    void playlistUpdated(const QSet<int> &songIds); // 更新歌单列表内容


private slots:
    void on_addSongBtn_clicked(); // 添加歌曲按钮点击槽函数

private:
    Ui::UISideBar *ui;
    Ui::Dialog *m_dialog; // 创建歌单模态框UI对象

    QDialog *m_songListDialog{}; // m_dialog的父窗口，用于显示歌单模态框

    QButtonGroup *group{}; // 按钮组，用于管理主页和收藏按钮的状态
};

#endif // UISIDEBAR_H
