#include "musicplayer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>

MusicPlayer::MusicPlayer(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowIcon(QIcon(":/icon/icon.png"));

    m_mediator = new AppMediator(this);

    m_controller = new PlayerController(this);
    m_listManager = new PlayListManager(this);

    m_uiMain = new UIMain(this);
    m_uiSideBar = new UISideBar(this);
    m_uiSearch = new UISearch(this);
    m_detailWidget = new MusicDetailWidget(m_uiMain);

    m_uiMain->setModel(m_uiMain->listView(), m_listManager->model());
    m_uiMain->setModel(m_uiMain->collectListView(), m_listManager->collectModel());
    m_uiMain->setModel(m_uiMain->songListView(), m_listManager->songlistModel());
    m_uiSearch->setModel(m_uiSearch->searchListView(), m_listManager->searchModel());

    initLayout();

    m_mediator->setPlayer(m_controller);
    m_mediator->setListManager(m_listManager);
    m_mediator->setUIMain(m_uiMain);
    m_mediator->setUISideBar(m_uiSideBar);
    m_mediator->setUISearch(m_uiSearch);
    m_mediator->setDetailWidget(m_detailWidget);

    m_mediator->connectSignal();

    loadSettings();
}


void MusicPlayer::initLayout()
{
    QHBoxLayout *HBox = new QHBoxLayout(this);
    HBox->setContentsMargins(0, 0, 0, 0);
    HBox->addWidget(m_uiSideBar);
    HBox->setSpacing(0);

    QVBoxLayout *VBox = new QVBoxLayout;
    VBox->setContentsMargins(0, 0, 0, 0);
    VBox->setSpacing(0);
    VBox->addWidget(m_uiSearch);
    VBox->addWidget(m_uiMain);

    HBox->addLayout(VBox);

    m_detailWidget->hide();
    m_detailWidget->setGeometry(m_uiMain->rect());
    m_detailWidget->stackUnder(m_uiMain->controlBar());
}


void MusicPlayer::saveSettings()
{
    QSettings s("Luo", "MusicPlayer");

    s.setValue("currentRow", m_listManager->currentRow()); // 保存当前播放的音乐在列表中的行号
    s.setValue("position", m_controller->position()); // 保存当前播放的音乐的播放进度
    s.setValue("volume", m_controller->volume()); // 保存当前的音量大小
    s.setValue("playMode", static_cast<int>(m_listManager->mode())); // 保存当前的播放模式
}


void MusicPlayer::loadSettings()
{
    QSettings s("Luo", "MusicPlayer");

    int playProgress = s.value("position", 0).toInt(); // 获取上次部分的播放进度，默认为0
    int row = s.value("currentRow", 0).toInt(); // 获取上次播放的音乐在列表中的行号，默认为0
    int volume = s.value("volume", 20).toInt(); // 获取上次的音量大小，默认为20

    m_listManager->setCurrentRow(row); // 设置当前播放的音乐在列表中的行号

    QModelIndex index = m_listManager->index(); // 获取当前播放的音乐在列表中的 QModelIndex
    if(!index.isValid()) return;

    m_uiMain->setCurrentIndex(index); // 设置音乐列表视图的当前选中项

    m_uiMain->onListViewDbClicked(index, false); // 设置当前播放的音乐的标题、作者、封面等信息，并不自动播放

    // 当音乐加载完成后，设置播放进度，并暂停播放
    connect(m_controller->mediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, [this, playProgress](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::LoadedMedia) {
            m_controller->setPlayProgress(playProgress);
            m_controller->mediaPlayer()->pause();
        }
    }, Qt::SingleShotConnection);

    m_controller->setVolume(volume); // 设置当前的音量大小

    m_listManager->setMode(static_cast<PlayMode>(s.value("playMode", 0).toInt())); // 设置当前的播放模式
}


void MusicPlayer::closeEvent(QCloseEvent *event)
{
    saveSettings(); // 关闭程序时保存当前配置

    QWidget::closeEvent(event);
}

void MusicPlayer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // 当窗口大小改变时，调整音乐详情页的大小和位置
    if(m_detailWidget){
        m_detailWidget->setGeometry(0, 0, this->width(), this->height());
    }
}

void MusicPlayer::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        m_controller->onPlayPauseRequested();
    }
    else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Left){
        emit m_uiMain->skipPlayRequested(false);
    }
    else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Right){
        emit m_uiMain->skipPlayRequested(true);
    }

    QWidget::keyPressEvent(event);
}

