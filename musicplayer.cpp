#include "musicplayer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QTimer>
#include <QListView>
#include <QLineEdit>

MusicPlayer::MusicPlayer(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowIcon(QIcon(":/icon/icon.png"));

    mediator = new AppMediator(this);

    m_controller = new PlayerController(this);
    m_listManager = new PlayListManager(this);

    m_uiMain = new UIMain(this);
    m_uiSideBar = new UISideBar(this);
    m_uiSearch = new UISearch(this);

    m_uiMain->setModel(m_uiMain->listView(), m_listManager->model());
    m_uiMain->setModel(m_uiMain->collectListView(), m_listManager->collectModel());
    m_uiSearch->setModel(m_uiSearch->searchListView(), m_listManager->searchModel());

    initLayout();

    mediator->setPlayer(m_controller);
    mediator->setListManager(m_listManager);
    mediator->setUIMain(m_uiMain);
    mediator->setUISideBar(m_uiSideBar);
    mediator->setUISearch(m_uiSearch);

    mediator->connectSignal();

    loadSettings();
}

void MusicPlayer::initLayout()
{
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

    m_controller->setVolume(s.value("volume", 20).toInt());
    m_listManager->setMode(static_cast<PlayMode>(s.value("playMode", 0).toInt()));
}


void MusicPlayer::closeEvent(QCloseEvent *event)
{
    saveSettings();

    QWidget::closeEvent(event);
}

