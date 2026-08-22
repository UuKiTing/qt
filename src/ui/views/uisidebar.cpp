#include "uisidebar.h"
#include "ui_uisidebar.h"
#include "ui_dialog.h"
#include "dbmanager.h"
#include "cover_cache_manager.h"

UISideBar::UISideBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UISideBar)
    , m_dialog(new Ui::Dialog)
{
    ui->setupUi(this);

    // 设置按钮组
    m_group = new QButtonGroup(this);

    // 设置用户头像
    QIcon icon = roundPixmap(QPixmap(":/images/avatar.png"), QSize(50, 50), 25);
    ui->avatarBtn->setIcon(icon);

    m_songListDialog = new QDialog(this);
    m_songListDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog); // 设置无边框和对话框属性
    m_songListDialog->setAttribute(Qt::WA_TranslucentBackground); // 设置背景透明

    m_dialog->setupUi(m_songListDialog); // 将m_dialog的UI设置到m_songListDialog中

    initMainBtn();

    initContextMenu();

    connectSignals();

    // 从数据库中查询用户的歌单，并创建对应的歌单按钮
    QList<PlayListInfo> list = DbManager::getInstance().queryPlayLists(1);
    for(const auto &info : list){
        createPlayList(info);
    }
}


UISideBar::~UISideBar()
{
    delete ui;
    delete m_dialog;
}


void UISideBar::connectSignals()
{
    // 创建歌单对话框的接受和取消按钮的点击事件连接
    connect(m_dialog->acceptBtn, &QPushButton::clicked, m_songListDialog, &QDialog::accept);
    connect(m_dialog->cancelBtn, &QPushButton::clicked, m_songListDialog, &QDialog::reject);

    // 当取消按钮被点击时，清空歌单名称输入框的文本
    connect(m_dialog->cancelBtn, &QPushButton::clicked, this, &UISideBar::clearInputBox);

    // 添加歌曲到歌单中
    connect(m_contextMenu, &QMenu::triggered, this, &UISideBar::rightClickPlaylist);
}

void UISideBar::initMainBtn()
{
    QList<QPushButton*> buttons = ui->mainBtnWidget->findChildren<QPushButton*>();
    for (auto btn : buttons) {
        btn->setCheckable(true);
        btn->setCursor(Qt::PointingHandCursor);

        m_group->addButton(btn);

        const QString &name = btn->objectName();
        if(name == "homeBtn"){
            btn->setChecked(true);
            connect(btn, &QPushButton::toggled, this, &UISideBar::toggleToHomePage);
        }
        else if(name == "collectBtn"){
            connect(btn, &QPushButton::toggled, this, &UISideBar::toggleToCollectPage);
        }
        else if(name == "networkBtn"){
            connect(btn, &QPushButton::toggled, this, &UISideBar::toggleToNetworkPage);
        }
    }
}

void UISideBar::toggleToCollectPage(bool checked)
{
    if(checked) {
        emit pageChanged(MainPage::Collect);
        ui->collectBtn->setIcon(QIcon(":/icon/collect.png"));
    }
    else{
        ui->collectBtn->setIcon(QIcon(":/icon/dislove.png"));
    }
}

void UISideBar::toggleToNetworkPage(bool checked)
{
    if(checked) {
        emit pageChanged(MainPage::NetWork);
        ui->networkBtn->setIcon(QIcon(":/icon/networking.png"));
    }
    else{
        ui->networkBtn->setIcon(QIcon(":/icon/network.png"));
    }
}

void UISideBar::toggleToHomePage(bool checked)
{

    if(checked) {
        emit pageChanged(MainPage::Main);
        ui->homeBtn->setIcon(QIcon(":/icon/homeSelect.png"));
    }
    else{
        ui->homeBtn->setIcon(QIcon(":/icon/homeNormal.png"));
    }
}


void UISideBar::createPlayList(const PlayListInfo &info)
{
    // 获取歌单按钮的布局
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->songList->layout());

    // 创建一个新的歌单按钮，设置其图标、提示信息和属性，然后将按钮添加到按钮组和布局中，并连接按钮的点击事件以发射相应的信号
    QPushButton *btn = new QPushButton;
    QPixmap pix = roundPixmap(QPixmap(info.cover), QSize(30, 30), 5);

    btn->setIconSize(QSize(30, 30));
    btn->setToolTip(info.name);
    btn->setIcon(pix);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setProperty("playlist", QVariant::fromValue(info));
    btn->setCheckable(true);

    m_group->addButton(btn);

    layout->insertWidget(layout->count() - 1, btn);

    // 点击歌单按钮
    connect(btn, &QPushButton::clicked, [this, btn](){
        PlayListInfo info = btn->property("playlist").value<PlayListInfo>();
        emit playlistUpdated(DbManager::getInstance().queryPlaylistSongId(info.id)); // 发射歌单更新信号，传递歌单中的歌曲ID集合
        emit playlistClicked(info); // 发射歌单点击信号，传递歌单信息
        emit pageChanged(MainPage::SongList); // 发射页面切换信号，切换到歌单页面
    });

    btn->setContextMenuPolicy(Qt::CustomContextMenu);

    // 右击歌单按钮显示菜单栏
    connect(btn, &QPushButton::customContextMenuRequested, this, [btn, this, info](const QPoint &pos) {
        m_contextMenu->setProperty("playlist_id", info.id); // 将歌单ID存储在右键菜单的属性中);
        btn->click();
        m_contextMenu->exec(btn->mapToGlobal(pos)); // 显示右键菜单
    });
}

void UISideBar::initContextMenu()
{
    m_contextMenu = new QMenu(this);
    QAction *playAction = new QAction(QIcon(":/icon/playlistRightClick/play.png"), "播放", this);
    QAction *delAction = new QAction(QIcon(":/icon/playlistRightClick/del.png"), "删除", this);
    QAction *renameAction = new QAction("重命名", this);

    playAction->setObjectName("play");
    delAction->setObjectName("del");
    renameAction->setObjectName("rename");

    m_contextMenu->addAction(playAction);
    m_contextMenu->addAction(delAction);
    m_contextMenu->addAction(renameAction);
}


void UISideBar::clearInputBox()
{
    QLineEdit* lineEdit = m_songListDialog->findChild<QLineEdit*>("lineEdit");
    lineEdit->clear();
}


void UISideBar::rightClickPlaylist(QAction *action)
{
    int playlist_id = m_contextMenu->property("playlist_id").toInt();

    QAbstractButton* btn = findPlaylist(playlist_id);

    if(!btn) return;

    if(action->objectName() == "play"){
        emit playlistPlayed(); // 播放歌单
    }
    else if(action->objectName() == "del"){
        int order = findPlaylistOrder(btn); // 查看当前右键的歌单在所有歌单中的序号
        if(order < 0) return;

        QList<QPushButton*> list = ui->songList->findChildren<QPushButton*>();
        if(list.isEmpty()) return;

        int next = (order + 1) % list.size(); // 计算当前右键的歌单下一个歌单的序号

        if(next == order){ // 如果只有一个歌单，没有下一个歌单了，就跳转到主页
            emit pageChanged(MainPage::Main);
            return;
        }

        list[next]->click();
        m_group->removeButton(btn);
        ui->songList->layout()->removeWidget(btn);
        btn->deleteLater();

        DbManager::getInstance().deletePlaylist(playlist_id);

        emit playlistDeleted(playlist_id);
    }
    else if(action->objectName() == "rename"){


    }
}


QAbstractButton* UISideBar::findPlaylist(int playlist_id)
{
    QList<QPushButton*> buttons = ui->songList->findChildren<QPushButton*>();
    for(auto btn : buttons){
        PlayListInfo info = btn->property("playlist").value<PlayListInfo>();
        if(info.id == playlist_id){
            return btn;
        }
    }

    return nullptr;
}

int UISideBar::findPlaylistOrder(QAbstractButton *btn)
{
    QList<QPushButton*> buttons = ui->songList->findChildren<QPushButton*>();
    for(int i = 0; i < buttons.size(); ++i){
        if(buttons[i] == btn){
            return i;
        }
    }
    return -1;
}

void UISideBar::setPlaylistCover(const QString &path, int playlist_id)
{
    QAbstractButton* btn = findPlaylist(playlist_id);
    QPixmap pix = roundPixmap(QPixmap(path), QSize(30, 30), 5);
    btn->setIcon(pix);

    PlayListInfo info = btn->property("playlist").value<PlayListInfo>();
    info.cover = path;
    btn->setProperty("playlist", QVariant::fromValue(info));
}

void UISideBar::on_addSongBtn_clicked()
{
    // 显示创建歌单对话框
    int result = m_songListDialog->exec();

    // 获取用户输入的歌单名称
    QLineEdit* lineEdit = m_songListDialog->findChild<QLineEdit*>("lineEdit");
    QString name = lineEdit->text();

    // 如果用户点击了接受按钮并且输入不为空，则在数据库中创建新的歌单，并调用createPlayList方法创建对应的歌单按钮
    if(result == QDialog::Accepted && !name.isEmpty()){
        PlayListInfo info = DbManager::getInstance().createSongList(1, name);
        createPlayList(info);
        emit playlistCreated(info);
    }

    // 清空歌单名称输入框的文本，以便下次创建歌单时输入框为空
    lineEdit->clear();
}


