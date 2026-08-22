#include "musicplayer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QApplication>
#include <QMessageBox>


MusicPlayer::MusicPlayer(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowIcon(QIcon(":/icon/icon.png"));

    if (!DbManager::getInstance().isValid()) {
        QMessageBox::critical(nullptr, "启动失败", "无法连接数据库，应用将退出。");
        return;
    }


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

    createTrayIcon();

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

    m_uiMain->doubleClickPlay(index, false); // 设置当前播放的音乐的标题、作者、封面等信息，并不自动播放

    // 当音乐加载完成后，设置播放进度，并暂停播放
    connect(m_controller->mediaPlayer(), &QMediaPlayer::mediaStatusChanged, this, [this, playProgress](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::LoadedMedia) {
            m_controller->setPlayProgress(playProgress);
        }
    }, Qt::SingleShotConnection);

    m_controller->setVolume(volume); // 设置当前的音量大小

    m_listManager->setMode(static_cast<PlayMode>(s.value("playMode", 0).toInt())); // 设置当前的播放模式
}


void MusicPlayer::createTrayIcon()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        return;
    }

    m_trayIcon = new QSystemTrayIcon(this);  // 指定父对象，自动管理内存
    m_trayIcon->setIcon(QIcon(":/icon/icon.png"));
    m_trayIcon->setToolTip(tr("我的应用"));

    // 创建菜单
    m_trayMenu = new QMenu(this);
    QAction *quitAction = new QAction(tr("退出"), this);
    quitAction->setIcon(QIcon(":/icon/quit.png"));

    connect(quitAction, &QAction::triggered, [this](){
        m_isQuitting = true;
        this->close();
    });

    connect(m_trayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {
        // 判断触发的原因是否为“双击”
        if (reason == QSystemTrayIcon::DoubleClick) {
            // 【双击要执行的代码】：通常是显示/还原主窗口
            if (this->isMinimized()) {
                this->showNormal(); // 如果最小化了，还原
            } else {
                this->show();       // 如果隐藏了，显示
            }
            this->activateWindow(); // 将窗口置顶并获取焦点
        }
    });

    m_trayMenu->addAction(quitAction);

    m_trayIcon->setContextMenu(m_trayMenu);

    m_trayIcon->show();
}


void MusicPlayer::closeEvent(QCloseEvent *event)
{
    if (!m_isQuitting && m_trayIcon && m_trayIcon->isVisible()) {
        hide();  // 隐藏到托盘
        event->ignore();  // 忽略关闭事件
        return;
    }

    saveSettings(); // 关闭程序时保存当前配置

    event->accept();
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
        m_controller->playOrPause();
    }
    else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Left){
        emit m_uiMain->musicSkipped(false);
    }
    else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Right){
        emit m_uiMain->musicSkipped(true);
    }

    QWidget::keyPressEvent(event);
}




