#include "musicplayer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QTimer>
#include <QListView>


MusicPlayer::MusicPlayer(QWidget *parent)
    : QWidget{parent}
{
    initUI();

    m_listManager = new PlayListManager(this);

    m_uiMain->setModel(m_uiMain->listView(), m_listManager->model());
    m_uiMain->setModel(m_uiMain->collectListView(), m_listManager->collectModel());

    m_controller = new PlayerController(this);

    playConnect(); // 播放
    progressSliderConnect(); // 进度条
    volumeSliderConnect(); // 音量条
    pageConnect();
    collectConnect();

    loadSettings();

}

void MusicPlayer::initUI()
{
    this->setWindowIcon(QIcon(":/icon/icon.png"));

    m_uiMain = new UIMain(this);
    m_uiSideBar = new UISideBar(this);
    m_uiSearch = new UISearch(this);

    QHBoxLayout *HBox = new QHBoxLayout(this);
    HBox->setContentsMargins(0, 0, 0, 0);
    HBox->addWidget(m_uiSideBar);

    QVBoxLayout *VBox = new QVBoxLayout;
    VBox->setContentsMargins(0, 0, 0, 0);
    VBox->setSpacing(0);
    VBox->addWidget(m_uiSearch);
    VBox->addWidget(m_uiMain);

    HBox->addLayout(VBox);
}

void MusicPlayer::playConnect()
{
    // 设置播放按钮Icon
    connect(m_controller->mediaPlayer(), &QMediaPlayer::playbackStateChanged, m_uiMain, &UIMain::setPlayBtnIcon);

    // 双击播放
    connect(m_uiMain, &UIMain::songPlayRequest, m_controller, &PlayerController::onSongPlayRequested);
    connect(m_uiMain, &UIMain::songPlayRequest,
            [this](const QModelIndex &index){m_listManager->setCurrentRow(index.row());});

    // 手动控制播放/停止
    connect(m_uiMain, &UIMain::playPauseRequested, m_controller, &PlayerController::onPlayPauseRequested);

    // 下/上一首
    connect(m_uiMain, &UIMain::skipRequested, this, &MusicPlayer::onSkipRequested);

    // 播放歌曲
    connect(m_controller, &PlayerController::playbackStarted, this, &MusicPlayer::onSkipRequested);

    // 当前音乐播放的row
    connect(m_controller, &PlayerController::currentRowChanged, m_listManager, &PlayListManager::setCurrentRow);

    // 标识正在播放
    connect(m_controller, &PlayerController::isPlayingChanged, m_listManager, &PlayListManager::setIsPlayingData);

    // 解除正在播放标识
    connect(m_controller, &PlayerController::isPlayingRestored, [this](){
        int row = m_listManager->currentRow();
        if(row < 0) return;
        QModelIndex index = m_listManager->item(row)->index();
        m_listManager->setIsPlayingData(index, false);
    });

    // 播放结束自动下一首
    connect(m_controller->mediaPlayer(), &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::MediaStatus::EndOfMedia){
            this->onSkipRequested(true);
        }
    });

    // 播放模式切换
    connect(m_uiMain, &UIMain::modeChangeRequested, m_listManager, [this](){
        PlayMode mode = static_cast<PlayMode>((m_listManager->mode() + 1) % PlayMode::Count);
        m_listManager->setMode(mode);
    });
    connect(m_listManager, &PlayListManager::modeChanged, m_uiMain, &UIMain::onModeChanged);
}


void MusicPlayer::progressSliderConnect()
{
    // 设置进度条范围
    connect(m_controller->mediaPlayer(), &QMediaPlayer::durationChanged, m_uiMain, &UIMain::setProgressSliderRange);

    // 当前进度时长
    connect(m_controller->mediaPlayer(), &QMediaPlayer::positionChanged, m_uiMain, &UIMain::setCurDuration);

    // 播放器进度同步给进度条滑块
    connect(m_controller->mediaPlayer(), &QMediaPlayer::positionChanged, [this](qint64 position){
        if(!m_isDragging) m_uiMain->setProgressValue(position);
    });

    // 拖动开始：标记正在拖动
    connect(m_uiMain->progressSlider(), &QSlider::sliderPressed, [this](){
        m_isDragging = true;
    });

    // 拖动结束：标记结束拖动
    connect(m_uiMain->progressSlider(), &QSlider::sliderReleased, [this](){
        m_isDragging = false;
        m_controller->setPlayProgress(m_uiMain->progressValue());
    });
}

void MusicPlayer::volumeSliderConnect()
{
    connect(m_uiMain->volumeSlider(), &QSlider::valueChanged,
            m_controller, &PlayerController::setVolume);

    connect(m_controller->audioOutput(), &QAudioOutput::volumeChanged,
            m_uiMain, &UIMain::setVolumeValue);
}

void MusicPlayer::pageConnect()
{
    connect(m_uiSideBar, &UISideBar::pageChanged, m_uiMain, &UIMain::switchStackedWidget);
}

void MusicPlayer::collectConnect()
{
    connect(m_uiMain, &UIMain::collected, [this](const QModelIndex &index){
        collectSong(true, index);
        m_listManager->addCollectSong(index);
    });

    connect(m_uiMain, &UIMain::notCollected, [this](const QModelIndex &index){
        collectSong(false, index);
        m_listManager->removeCollectSong(index);
    });
}

void MusicPlayer::collectSong(bool isCollect, const QModelIndex &index)
{
    QModelIndex idx;
    if(!index.isValid()) idx = m_listManager->index();
    else idx = index;


    if(isCollect) DbManager::getInstance().collectSong(idx);
    else DbManager::getInstance().disCollectSong(idx);

    m_listManager->setData(m_listManager->model(), idx, isCollect, Role::IsFavorite);

    if(m_listManager->index() == index){
        m_uiMain->collectIconToggle(isCollect);
    }
}


void MusicPlayer::saveSettings()
{
    QSettings s;
    s.setValue("currentRow", m_listManager->currentRow());
    s.setValue("position", m_controller->position());
    s.setValue("volume", m_controller->volume());
    s.setValue("playMode", static_cast<int>(m_listManager->mode()));
}

void MusicPlayer::loadSettings()
{
    QSettings s;
    int playProgress = s.value("position", 0).toInt();
    int row = s.value("currentRow", 0).toInt();


    m_listManager->setCurrentRow(row);

    QStandardItem *item = m_listManager->item(row);
    if(item == nullptr){
        return;
    }

    QModelIndex index = item->index();
    m_uiMain->setCurrentIndex(index);

    m_uiMain->onlistViewDbClicked(index, false);

    connect(m_controller->mediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, [this, playProgress](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::LoadedMedia) {
            m_controller->setPlayProgress(playProgress);
            m_controller->mediaPlayer()->pause();
        }
    }, Qt::SingleShotConnection);

    m_controller->setVolume(s.value("volume", 20).toInt());
    m_listManager->setMode(static_cast<PlayMode>(s.value("playMode", 0).toInt()));
}

void MusicPlayer::onSkipRequested(bool isNext)
{
    emit m_controller->isPlayingRestored();

    int currentRow = m_listManager->setNextRow(isNext);

    QStandardItem *item = m_listManager->item(currentRow);
    QModelIndex index = item->index();

    m_uiMain->setCurrentIndex(index);
    m_uiMain->setPlayStyle(index);
    m_controller->onSkipPlayRequested(index);
}

void MusicPlayer::closeEvent(QCloseEvent *event)
{
    saveSettings();

}
