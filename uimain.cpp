#include "uimain.h"
#include "ui_uimain.h"
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

    initVolumeMenu();
    connectSingal();
}


UIMain::~UIMain()
{
    delete ui;
}


void UIMain::connectSingal()
{
    connect(m_delegate, &StyleItemDelegate::collected, this, &UIMain::collected);
    connect(m_delegate, &StyleItemDelegate::cancelCollected, this, &UIMain::cancelCollected);
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
    this->setTotalDuration(durationString(index.data(Role::Duration).toInt())); // 设置最大时长
    this->setCoverIcon(index.data(Role::Cover).toString());  // 设置音乐封面
    this->setTitleAndArtist(index.data(Role::Title).toString(), // 设置音乐名称和作者
                            index.data(Role::Artist).toString());
    if(index.data(Role::IsFavorite).toBool()){ // 音乐是否收藏
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
    ui->stackedWidget->setCurrentIndex(pageIndex);
}


void UIMain::collectStatusToggle(bool checked)
{
    collectIconToggle(checked);
    if(checked) emit collected();
    else emit cancelCollected();
}


void UIMain::collectIconToggle(bool isFavo)
{
    if(isFavo) ui->loveBtn->setIcon(QIcon(":/icon/love.png"));
    else ui->loveBtn->setIcon(QIcon(":/icon/dislove.png"));
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
    ui->curDuration->setText(durationString(position / 1000));
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


QListView *UIMain::listView()
{
    return ui->listView;
}


QListView *UIMain::collectListView()
{
    return ui->collectListView;
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
    this->setPlayStyle(index);
    emit songPlayRequest(index, autoPlay);
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

