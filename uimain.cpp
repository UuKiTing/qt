#include "uimain.h"
#include "ui_uimain.h"
#include "dbmanager.h"
#include <QPainter>
#include <QPainterPath>
#include <QWidgetAction>
#include <QMenu>
#include <QSortFilterProxyModel>
#include <QLabel>


UIMain::UIMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UIMain)
{
    ui->setupUi(this);

    // 设置委托
    m_delegate = new StyleItemDelegate(this);
    ui->listView->setItemDelegate(m_delegate);
    ui->collectListView->setItemDelegate(m_delegate);
    ui->songListView->setItemDelegate(m_delegate);

    // 设置列表视图的右键菜单策略
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);

    initContextMenu(); // 初始化右键菜单
    initVolumeMenu(); // 初始化音量菜单

    connectSignal(); // 连接信号槽
}


UIMain::~UIMain()
{
    delete ui;
}


void UIMain::connectSignal()
{
    // 连接委托的收藏信号到UIMain的收藏槽函数
    connect(m_delegate, &StyleItemDelegate::collected, this, &UIMain::collected);
    connect(m_delegate, &StyleItemDelegate::cancelCollected, this, &UIMain::cancelCollected);

    // 显示主页歌曲列表的右键菜单
    connect(ui->listView, &QListView::customContextMenuRequested, this, [this](const QPoint &pos){
        QModelIndex index = ui->listView->indexAt(pos); // 获取右键的歌曲列表index
        if(index.isValid()){
            m_contextMenu->setProperty("song_id", index.data(Role::Id)); // 为右键菜单栏设置当前右键的歌曲id属性
            m_contextMenu->setProperty("cover", index.data(Role::Cover)); // 为右键菜单栏设置当前右键的歌曲封面属性
            m_contextMenu->exec(ui->listView->viewport()->mapToGlobal(pos)); // 显示右键菜单
        }
    });


    // 添加歌曲到播放列表
    connect(m_contextMenu, &QMenu::triggered, this, [=](QAction *action){
        int playlist_id = action->data().toInt();
        int song_id = m_contextMenu->property("song_id").toInt();
        DbManager::getInstance().addSongToPlaylist(playlist_id, song_id);

        // QString cover = m_contextMenu->property("cover").toString();
        // DbManager::getInstance().updatePlaylistCover(cover, playlist_id);
    });
}


void UIMain::initVolumeMenu()
{
    m_volumeMenu = new QMenu(this);

    m_volumeSlider = new QSlider(Qt::Vertical);
    m_volumeSlider->setRange(0, 100);

    m_volumeMenu->setStyleSheet(R"(
        QSlider {
            background-color: transparent;
        }

        QSlider::groove:vertical {
            background: #E3F2FD;
            width: 4px;
        }

        QSlider::add-page:vertical {
            background: #64B5F6;
            width: 4px;
        }

        QSlider::handle:vertical {
            background: #FFFFFF;
            height: 10px;
            width: 15px;
            border-radius: 5px;
            margin: 0 -6px;
            border: 1px solid #64B5F6;
        })");


    QWidgetAction *action = new QWidgetAction(m_volumeMenu);
    action->setDefaultWidget(m_volumeSlider);

    m_volumeMenu->addAction(action);
}


void UIMain::setPlayStyle(const QModelIndex &index)
{
    this->setTotalDuration(toDurationString(index.data(Role::Duration).toInt())); // 设置最大时长
    this->setCoverIcon(index.data(Role::Cover).toString());  // 设置音乐封面
    this->setTitleAndArtist(index.data(Role::Title).toString(), // 设置音乐名称和作者
                            index.data(Role::Artist).toString());

    if(index.data(Role::IsFavorite).toBool()){ // 设置收藏状态
        ui->loveBtn->setIcon(QIcon(":/icon/love.png"));
        ui->loveBtn->setChecked(true);
    }
    else{
        ui->loveBtn->setIcon(QIcon(":/icon/dislove.png"));
        ui->loveBtn->setChecked(false);
    }
}


void UIMain::switchStackedWidget(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex); // 切换堆叠窗口的页面
}


void UIMain::collectStatusToggle(bool checked)
{
    collectIconToggle(checked); // 收藏图标切换
    if(checked) emit collected(); // 发射收藏信号
    else emit cancelCollected(); // 发射取消收藏信号
}


void UIMain::collectIconToggle(bool isFavo)
{
    if(isFavo) {
        ui->loveBtn->setChecked(true);
        ui->loveBtn->setIcon(QIcon(":/icon/love.png"));
    }
    else{
        ui->loveBtn->setChecked(false);
        ui->loveBtn->setIcon(QIcon(":/icon/dislove.png"));
    }
}

void UIMain::initContextMenu()
{
    m_contextMenu = new QMenu(this);

    QAction *play = new QAction(QIcon(":/icon/rightClickMenu/play.png"), "播放");
    QAction *nextPlay = new QAction(QIcon(":/icon/rightClickMenu/next.png"), "下一首播放");
    QAction *love = new QAction("我喜欢");

    m_contextMenu->addAction(play);
    m_contextMenu->addAction(nextPlay);
    m_contextMenu->addAction(love);

    QMenu *addTo = new QMenu("添加到");
    QMenu *moveTo = new QMenu("移动到");

    QList<PlayListInfo> list = DbManager::getInstance().queryPlayLists(1);
    for(auto &info : list){
        QAction *action = new QAction(info.name);
        action->setIcon(QIcon(info.cover)); // 设置右键菜单中歌单选项的图标
        action->setData(info.id); // 设置右键菜单中歌单选项的id
        addTo->addAction(action);
    }

    addTo->setIcon(QIcon(":/icon/rightClickMenu/add.png"));

    m_contextMenu->addMenu(addTo);
    m_contextMenu->addMenu(moveTo);
}


void UIMain::setModel(QAbstractItemView *view, QAbstractItemModel *model)
{
    view->setModel(model);
}


void UIMain::setPlayBtnIcon(QMediaPlayer::PlaybackState state)
{
    if(state == QMediaPlayer::PlayingState){
        ui->playBtn->setIcon(QIcon(":/icon/play.png"));
    }
    else if(state == QMediaPlayer::PausedState){
        ui->playBtn->setIcon(QIcon(":/icon/pause.png"));
    }
}


void UIMain::setCurDuration(qint64 position)
{
    ui->curDuration->setText(toDurationString(position / 1000));
}


void UIMain::setTotalDuration(const QString &durationString)
{
    ui->totalDuration->setText(durationString);
}


void UIMain::setProgressSliderRange(qint64 duration)
{
    ui->progressSlider->setRange(0, duration);
}


void UIMain::setProgressValue(qint64 position)
{
    ui->progressSlider->setValue(position);
}


void UIMain::setCoverIcon(const QString &path)
{
    ui->coverBtn->setIcon(roundPixmap(QPixmap(path), QSize(60, 60), 5));
}


void UIMain::setVolumeValue(float volume)
{
    m_volumeSlider->setValue(volume * 100);
}


void UIMain::setTitleAndArtist(const QString &title, const QString &artist)
{
    QString str = QString("<span vertical-align:middle;'>%1</span>"
                          "<span style='font-size:12px; vertical-align:middle;'> - %2</span>");

    ui->titleSinger->setText(str.arg(title, artist));
}


void UIMain::setCurrentIndex(const QModelIndex &index)
{
    ui->listView->setCurrentIndex(index);
}

void UIMain::setPlaylistName(const QString name)
{
    ui->playlistName->setText(name);
}

void UIMain::setPlaylistCover(const QString path)
{
    ui->playlistCover->setPixmap(QPixmap(path));
}


QListView *UIMain::listView()
{
    return ui->listView;
}


QListView *UIMain::collectListView()
{
    return ui->collectListView;
}

QListView *UIMain::songListView()
{
    return ui->songListView;
}


QSlider *UIMain::progressSlider()
{
    return ui->progressSlider;
}


QSlider *UIMain::volumeSlider()
{
    return m_volumeSlider;
}


int UIMain::progressValue()
{
    return ui->progressSlider->value();
}


QStackedWidget *UIMain::stackedWidget()
{
    return ui->stackedWidget;
}

QFrame *UIMain::controlBar()
{
    return ui->controlBar;
}


void UIMain::onModeChanged(PlayMode mode)
{
    if(mode == PlayMode::Loop){
        ui->modeBtn->setIcon(QIcon(":/icon/loop.png"));
    }
    else if(mode == PlayMode::Random){
        ui->modeBtn->setIcon(QIcon(":/icon/random.png"));
    }
    else if(mode == PlayMode::Single){
        ui->modeBtn->setIcon(QIcon(":/icon/single.png"));
    }

}


void UIMain::onListViewDbClicked(const QModelIndex &index, bool autoPlay)
{
    this->setPlayStyle(index); // 设置播放样式
    emit songPlayRequest(index, autoPlay); // 发射播放请求信号
}

void UIMain::onSkipButtonClicked(bool isNext)
{
    if(ui->listView->model()->rowCount() > 0)
        emit skipPlayRequested(isNext);
}


void UIMain::on_listView_doubleClicked(const QModelIndex &index)
{
    this->onListViewDbClicked(index, true);
}


void UIMain::on_collectListView_doubleClicked(const QModelIndex &index)
{

    QSortFilterProxyModel *model = qobject_cast<QSortFilterProxyModel*>(ui->collectListView->model());

    this->onListViewDbClicked(model->mapToSource(index), true);
}


void UIMain::on_playBtn_clicked()
{
    emit playPauseRequested();
}


void UIMain::on_modeBtn_clicked()
{
    emit modeChangeRequested();
}


void UIMain::on_nextBtn_clicked()
{
    this->onSkipButtonClicked(true);
}


void UIMain::on_lastBtn_clicked()
{
    this->onSkipButtonClicked(false);
}

void UIMain::on_volumeBtn_clicked()
{
    m_volumeMenu->popup(ui->volumeBtn->mapToGlobal(QPoint(0, -m_volumeMenu->sizeHint().height())));
}


void UIMain::on_loveBtn_clicked(bool checked)
{
    this->collectStatusToggle(checked);
}


void UIMain::on_coverBtn_toggled(bool checked)
{
    if(checked){
        emit showDetailWidget(true);
    }
    else{
        emit showDetailWidget(false);
    }
}

