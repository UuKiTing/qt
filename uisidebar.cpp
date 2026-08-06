#include "uisidebar.h"
#include "ui_uisidebar.h"
#include "ui_dialog.h"
#include "dbmanager.h"

UISideBar::UISideBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UISideBar)
    , m_dialog(new Ui::Dialog)
{
    ui->setupUi(this);

    // 设置按钮组，确保主页和收藏按钮的互斥性
    group = new QButtonGroup(this);
    group->addButton(ui->homeBtn);
    group->addButton(ui->collectBtn);

    // 设置用户头像
    QIcon icon = roundPixmap(QPixmap(":/images/avatar.png"), QSize(50, 50), 25);
    ui->avatarBtn->setIcon(icon);

    m_songListDialog = new QDialog(this);
    m_songListDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog); // 设置无边框和对话框属性
    m_songListDialog->setAttribute(Qt::WA_TranslucentBackground); // 设置背景透明

    m_dialog->setupUi(m_songListDialog); // 将m_dialog的UI设置到m_songListDialog中

    connectSignals();

    // 从数据库中查询用户的歌单，并创建对应的歌单按钮
    QList<PlayListInfo> list = DbManager::getInstance().queryPlayLists(1);
    for(auto &info : list){
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
    // 当主页按钮被选中时，页面切换信号，并更改按钮图标
    connect(ui->homeBtn, &QToolButton::toggled, [this](bool checked){
        if(checked) {
            emit pageChanged(MainPage::Main);
            ui->homeBtn->setIcon(QIcon(":/icon/homeSelect.png"));
        }
        else{
            ui->homeBtn->setIcon(QIcon(":/icon/homeNormal.png"));
        }
    });

    // 当收藏按钮被选中时，页面切换信号，并更改按钮图标
    connect(ui->collectBtn, &QToolButton::toggled, [this](bool checked){
        if(checked) {
            emit pageChanged(MainPage::Collect);
            ui->collectBtn->setIcon(QIcon(":/icon/collect.png"));
        }
        else{
            ui->collectBtn->setIcon(QIcon(":/icon/dislove.png"));
        }
    });

    // 创建歌单对话框的接受和取消按钮的点击事件连接
    connect(m_dialog->acceptBtn, &QPushButton::clicked, m_songListDialog, &QDialog::accept);
    connect(m_dialog->cancelBtn, &QPushButton::clicked, m_songListDialog, &QDialog::reject);

    // 当取消按钮被点击时，清空歌单名称输入框的文本
    connect(m_dialog->cancelBtn, &QPushButton::clicked, [this](){
        QLineEdit* lineEdit = m_songListDialog->findChild<QLineEdit*>("lineEdit");
        lineEdit->clear();
    });
}


void UISideBar::createPlayList(PlayListInfo &info)
{
    // 获取歌单按钮的布局
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->songList->layout());

    // 创建一个新的歌单按钮，设置其图标、提示信息和属性，然后将按钮添加到按钮组和布局中，并连接按钮的点击事件以发射相应的信号
    QPushButton *btn = new QPushButton;
    QPixmap pix = roundPixmap(QPixmap(info.cover), QSize(30, 30), 5);
    btn->setIconSize(QSize(30, 30));
    btn->setIcon(pix);
    btn->setToolTip(info.name);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setProperty("playlist", QVariant::fromValue(info));
    btn->setCheckable(true);

    group->addButton(btn);

    layout->insertWidget(layout->count() - 1, btn);

    connect(btn, &QPushButton::clicked, [this, info](){
        emit playlistClicked(info); // 发射歌单点击信号，传递歌单信息
        emit playlistUpdated(DbManager::getInstance().queryCollectedSongs(info.id)); // 发射歌单更新信号，传递歌单中的歌曲ID集合
        emit pageChanged(MainPage::SongList); // 发射页面切换信号，切换到歌单页面
    });
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
    }

    // 清空歌单名称输入框的文本，以便下次创建歌单时输入框为空
    lineEdit->clear();
}


