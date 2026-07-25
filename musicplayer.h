#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "player_controller.h"
#include "play_list_manager.h"
#include "uimain.h"
#include "uisidebar.h"
#include "uisearch.h"
#include "appmediator.h"
#include "music_detail_widget.h"
#include <QWidget>
#include <QMoveEvent>
#include <QResizeEvent>

class MusicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit MusicPlayer(QWidget *parent = nullptr);

    void initLayout(); // 初始化布局

    void saveSettings(); // 保存配置
    void loadSettings(); // 加载配置

signals:


protected:
    void closeEvent(QCloseEvent *event) override; // 程序窗口关闭事件
    void resizeEvent(QResizeEvent *event) override; // 程序窗口更改
    void keyPressEvent(QKeyEvent *event) override; // 快捷键


private:
    AppMediator *m_mediator;
    PlayerController *m_controller; // 播放控制器
    PlayListManager *m_listManager; // 音乐列表管理器
    UIMain *m_uiMain; // 主界面
    UISideBar *m_uiSideBar; // 侧边栏
    UISearch *m_uiSearch; // 搜索栏
    MusicDetailWidget *m_detailWidget;
};

#endif // MUSICPLAYER_H
