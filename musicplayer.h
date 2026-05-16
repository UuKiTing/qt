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

    void initUI();

    void playConnect();
    void progressSliderConnect();
    void volumeSliderConnect();
    void pageConnect();

    void saveSettings(); // 保存
    void loadSettings(); // 加载

signals:

public slots:
    void onSkipRequested(bool isNext);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    PlayerController *m_controller;
    PlayListManager *m_listManager;
    UIMain *m_uiMain;
    UISideBar *m_uiSideBar;
    UISearch *m_uiSearch;


    bool m_isDragging = false;// 标志位：是否关闭播放器进度和进度条滑块的同步
};

#endif // MUSICPLAYER_H
