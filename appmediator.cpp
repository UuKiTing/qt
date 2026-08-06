#include "appmediator.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QTimer>
#include <QListView>
#include <QLineEdit>
#include <QMessageBox>

AppMediator::AppMediator(QObject *parent)
    : QObject{parent}
{

}

void AppMediator::setPlayer(PlayerController *controller)
{
    m_controller = controller;
}

void AppMediator::setListManager(PlayListManager *listManager)
{
    m_listManager = listManager;
}

void AppMediator::setUIMain(UIMain *uiMain)
{
    m_uiMain = uiMain;
}

void AppMediator::setUISideBar(UISideBar *uiSideBar)
{
    m_uiSideBar = uiSideBar;
}

void AppMediator::setUISearch(UISearch *uiSearch)
{
    m_uiSearch = uiSearch;
}


void AppMediator::setDetailWidget(MusicDetailWidget *detailWidget)
{
    m_detailWidget = detailWidget;
}


void AppMediator::connectSignal()
{
    playConnect();
    progressSliderConnect();
    volumeSliderConnect();
    pageConnect();
    collectConnect();
    searchConnect();
    playlistConnect();

    connect(m_uiMain, &UIMain::showDetailWidget, m_detailWidget, &MusicDetailWidget::setVisible);
    connect(m_uiMain, &UIMain::showDetailWidget, m_uiSideBar, &UISideBar::setHidden);
    connect(m_uiMain, &UIMain::showDetailWidget, m_uiSearch, &UISearch::setHidden);
}

void AppMediator::playConnect()
{
    // 设置播放按钮Icon
    connect(m_controller->mediaPlayer(), &QMediaPlayer::playbackStateChanged, m_uiMain, &UIMain::setPlayBtnIcon);

    // 双击播放
    connect(m_uiMain, &UIMain::songPlayRequest, [this](const QModelIndex &index, bool autoPlay){
        m_controller->onSongPlayRequested(index, autoPlay);
        m_listManager->setCurrentRow(index.row());
        m_detailWidget->flushDetail(m_listManager->index());
    });

    // 手动控制播放/停止
    connect(m_uiMain, &UIMain::playPauseRequested, m_controller, &PlayerController::onPlayPauseRequested);

    // 下/上一首
    connect(m_uiMain, &UIMain::skipPlayRequested, this, &AppMediator::onSkipPlayRequested);

    // 播放歌曲
    connect(m_controller, &PlayerController::playbackStarted, this, &AppMediator::onSkipPlayRequested);

    // 记录当前播放音乐的row
    connect(m_controller, &PlayerController::currentRowChanged, m_listManager, &PlayListManager::setCurrentRow);

    // 标识正在播放
    connect(m_controller, &PlayerController::isPlayingChanged, m_listManager, &PlayListManager::setIsPlayingData);

    // 解除正在播放标识
    connect(m_controller, &PlayerController::isPlayingRestored, [this](){
        QModelIndex index = m_listManager->index();
        if(index.isValid()) m_listManager->setIsPlayingData(index, false);
    });

    // 播放结束自动下一首
    connect(m_controller->mediaPlayer(), &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::MediaStatus::EndOfMedia)
            onSkipPlayRequested(true);
    });

    // 播放模式切换
    connect(m_uiMain, &UIMain::modeChangeRequested, m_listManager, [this](){
        PlayMode mode = static_cast<PlayMode>((m_listManager->mode() + 1) % PlayMode::Count);
        m_listManager->setMode(mode);
    });
    connect(m_listManager, &PlayListManager::modeChanged, m_uiMain, &UIMain::onModeChanged);

    // 播放错误提示
    connect(m_controller, &PlayerController::playbackError, this, [this](const QString &msg){
        QMessageBox::warning(nullptr, tr("Playback error"), msg);
    });
}


void AppMediator::progressSliderConnect()
{
    // 设置进度条范围
    connect(m_controller->mediaPlayer(), &QMediaPlayer::durationChanged, m_uiMain, &UIMain::setProgressSliderRange);

    // 当前进度条时长（文本）
    connect(m_controller->mediaPlayer(), &QMediaPlayer::positionChanged, m_uiMain, &UIMain::setCurDuration);

    // 播放器进度同步给进度条滑块
    connect(m_controller->mediaPlayer(), &QMediaPlayer::positionChanged, [this](qint64 position){
        if(!m_isDragging) m_uiMain->setProgressValue(position);
    });

    // 拖动开始：标记正在拖动
    connect(m_uiMain->progressSlider(), &QSlider::sliderPressed, [this](){ m_isDragging = true;});

    // 拖动结束：标记结束拖动
    connect(m_uiMain->progressSlider(), &QSlider::sliderReleased, [this](){
        m_isDragging = false;
        m_controller->setPlayProgress(m_uiMain->progressValue());
    });

    //播放进度同步到歌词
    connect(m_controller->mediaPlayer(), &QMediaPlayer::positionChanged,
            m_detailWidget, &MusicDetailWidget::onAudioPositionChanged);
}


void AppMediator::volumeSliderConnect()
{
    // 进度条和播放器音量同步
    connect(m_uiMain->volumeSlider(), &QSlider::valueChanged, m_controller, &PlayerController::setVolume);
    connect(m_controller->audioOutput(), &QAudioOutput::volumeChanged, m_uiMain, &UIMain::setVolumeValue);
}

void AppMediator::pageConnect()
{
    connect(m_uiSideBar, &UISideBar::pageChanged, m_uiMain, &UIMain::switchStackedWidget);
}

void AppMediator::collectConnect()
{
    connect(m_uiMain, &UIMain::collected, [this](const QModelIndex &index){
        collectSong(true, index);
    });

    connect(m_uiMain, &UIMain::cancelCollected, [this](const QModelIndex &index){
        collectSong(false, index);
    });
}

void AppMediator::searchConnect()
{
    connect(m_uiSearch->searchBar(), &QLineEdit::textChanged, m_listManager->searchModel(), &SearchFilterProxyModel::setKeyWord);
    connect(m_uiSearch, &UISearch::songPlayRequest, m_uiMain, &UIMain::onListViewDbClicked);
}

void AppMediator::playlistConnect()
{
    // 侧边栏歌单点击，更新主界面歌单信息
    connect(m_uiSideBar, &UISideBar::playlistClicked, m_uiMain, [this](const PlayListInfo &info){
        m_uiMain->setPlaylistName(info.name);
        m_uiMain->setPlaylistCover(info.cover);
    });

    // 侧边栏歌单点击，更新主界面歌单歌曲列表
    connect(m_uiSideBar, &UISideBar::playlistUpdated, m_listManager->songlistModel(), &SongListProxyModel::setAllowedSongIds);
}

void AppMediator::collectSong(bool isCollect, const QModelIndex &index)
{
    QModelIndex idx;
    if(!index.isValid()) idx = m_listManager->index();
    else idx = index;

    if(isCollect) DbManager::getInstance().collectSong(idx);
    else DbManager::getInstance().disCollectSong(idx);

    m_listManager->setData(m_listManager->model(), idx, isCollect, Role::IsFavorite);

    if(m_listManager->currentRow() == idx.row()){
        m_uiMain->collectIconToggle(isCollect);
    }
}

void AppMediator::onSkipPlayRequested(bool isNext)
{
    emit m_controller->isPlayingRestored(); // 解除当前播放歌曲的当前正在播放标识

    int currentRow = m_listManager->setNextRow(isNext); // 设置下一首歌曲的行号
    if(currentRow < 0 || currentRow >= m_listManager->modelRowCount()){
        return;
    }

    QModelIndex index = m_listManager->index();
    m_uiMain->setCurrentIndex(index);
    m_uiMain->setPlayStyle(index);

    m_controller->onSkipPlayRequested(index);

    m_detailWidget->flushDetail(index); // 刷新全屏播放页
}




