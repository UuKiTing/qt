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
    s.setValue("currentRow", m_listManager->currentRow());
    s.setValue("position", m_controller->position());
    s.setValue("volume", m_controller->volume());
    s.setValue("playMode", static_cast<int>(m_listManager->mode()));
}


void MusicPlayer::loadSettings()
{
    QSettings s("Luo", "MusicPlayer");

    int playProgress = s.value("position", 0).toInt();
    int row = s.value("currentRow", 0).toInt();
    int volume = s.value("volume", 20).toInt();

    m_listManager->setCurrentRow(row);

    QModelIndex index = m_listManager->index();
    if(!index.isValid()) return;

    m_uiMain->setCurrentIndex(index);

    m_uiMain->onListViewDbClicked(index, false);

    connect(m_controller->mediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, [this, playProgress](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::LoadedMedia) {
            m_controller->setPlayProgress(playProgress);
            m_controller->mediaPlayer()->pause();
        }
    }, Qt::SingleShotConnection);

    m_controller->setVolume(volume);
    m_listManager->setMode(static_cast<PlayMode>(s.value("playMode", 0).toInt()));
}


void MusicPlayer::closeEvent(QCloseEvent *event)
{
    saveSettings();

    QWidget::closeEvent(event);
}


void MusicPlayer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

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

