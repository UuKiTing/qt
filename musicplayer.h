#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "playercontroller.h"
#include "playlistmanager.h"
#include "uimain.h"
#include "uisidebar.h"
#include "uisearch.h"
#include <QWidget>

class MusicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit MusicPlayer(QWidget *parent = nullptr);

    void initLayout(); // 初始化布局

    // 信号连接
    void playConnect(); // 播放功能
    void progressSliderConnect(); // 进度条
    void volumeSliderConnect(); //  音量
    void pageConnect(); // 页面切换
    void collectConnect(); // 音乐收藏

    void collectSong(bool isCollect, const QModelIndex &index = QModelIndex()); // 收藏音乐

    void saveSettings(); // 保存配置
    void loadSettings(); // 加载配置

signals:

public slots:
    void onSkipRequested(bool isNext); // 处理上/下一首音乐

protected:
    void closeEvent(QCloseEvent *event) override; // 程序窗口关闭事件

private:
    PlayerController *m_controller; // 播放控制器
    PlayListManager *m_listManager; // 音乐列表管理器
    UIMain *m_uiMain; // 主界面
    UISideBar *m_uiSideBar; // 侧边栏
    UISearch *m_uiSearch; // 搜索栏

    bool m_isDragging = false;// 标志位：是否关闭播放器进度和进度条滑块的同步
};

#endif // MUSICPLAYER_H
