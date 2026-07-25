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

    group = new QButtonGroup(this);
    group->addButton(ui->homeBtn);
    group->addButton(ui->collectBtn);

    QIcon icon = roundPixmap(QPixmap(":/images/avatar.png"), QSize(50, 50), 25);
    ui->avatarBtn->setIcon(icon);

    m_songListDialog = new QDialog(this);
    m_songListDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    m_songListDialog->setAttribute(Qt::WA_TranslucentBackground);

    m_dialog->setupUi(m_songListDialog);

    connectSignals();

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
    connect(ui->homeBtn, &QToolButton::toggled, [this](bool checked){
        if(checked) {
            emit pageChanged(MainPage::Main);
            ui->homeBtn->setIcon(QIcon(":/icon/homeSelect.png"));
        }
        else{
            ui->homeBtn->setIcon(QIcon(":/icon/homeNormal.png"));
        }
    });

    connect(ui->collectBtn, &QToolButton::toggled, [this](bool checked){
        if(checked) {
            emit pageChanged(MainPage::Collect);
            ui->collectBtn->setIcon(QIcon(":/icon/collect.png"));
        }
        else{
            ui->collectBtn->setIcon(QIcon(":/icon/dislove.png"));
        }
    });

    connect(m_dialog->acceptBtn, &QPushButton::clicked, m_songListDialog, &QDialog::accept);
    connect(m_dialog->cancelBtn, &QPushButton::clicked, m_songListDialog, &QDialog::reject);
}


void UISideBar::createPlayList(PlayListInfo &info)
{
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->songList->layout());

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
        emit playlistClicked(info);
        emit playlistUpdated(DbManager::getInstance().queryCollectedSongs(info.id));
        emit pageChanged(MainPage::SongList);
    });
}

void UISideBar::on_addSongBtn_clicked()
{

    int result = m_songListDialog->exec();
    QString name = m_songListDialog->findChild<QLineEdit*>("lineEdit")->text();

    if(result == QDialog::Accepted && !name.isEmpty()){
        PlayListInfo info = DbManager::getInstance().createSongList(1, name);
        createPlayList(info);
    }
}


