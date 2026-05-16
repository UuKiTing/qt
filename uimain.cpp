#include "uimain.h"
#include "ui_uimain.h"
#include <QPainter>
#include <QPainterPath>
#include <QWidgetAction>
#include <QMenu>


UIMain::UIMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UIMain)
{
    ui->setupUi(this);

    // 设置委托
    m_delegate = new StyleItemDelegate(this);
    ui->listView->setItemDelegate(m_delegate);

    initVolumeMenu();
}


UIMain::~UIMain()
{
    delete ui;
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
    width: 10px;
    border-radius: 5px;
    margin: 0 -6px;
    border: 1px solid #64B5F6;
}
)");


    QWidgetAction *action = new QWidgetAction(m_volumeMenu);
    action->setDefaultWidget(m_volumeSlider);

    m_volumeMenu->addAction(action);
}

void UIMain::setPlayStyle(const QModelIndex &index)
{
    this->setTotalDuration(durationString(index.data(Role::Duration).toInt()));
    this->setCoverPixmap(index.data(Role::Cover).toString());
    this->setTitleAndArtist(index.data(Role::Title).toString(),
                            index.data(Role::Artist).toString());
}

void UIMain::switchStackedWidget(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void UIMain::setModel(QStandardItemModel *model)
{
    ui->listView->setModel(model);
}

void UIMain::setPlayBtnIcon(QMediaPlayer::PlaybackState state)
{
    if(state == QMediaPlayer::PlayingState){
        ui->playBtn->setIcon(QIcon(":/icon/play.png"));
    }
    else if(state == QMediaPlayer::PausedState){
        ui->playBtn->setIcon(QIcon(":/icon/pause.png"));
    }
    else if(state == QMediaPlayer::StoppedState){

    }
}

void UIMain::setCurDuration(qint64 position)
{
    QString str = durationString(position / 1000);
    ui->curDuration->setText(str);
}

void UIMain::setProgressSliderRange(qint64 duration)
{
    ui->progressSlider->setRange(0, duration);
}

void UIMain::setProgressValue(qint64 position)
{
    ui->progressSlider->setValue(position);
}

void UIMain::setCoverPixmap(const QString &cover)
{
    ui->coverLabel->setPixmap(roundPixmap(QPixmap(cover), QSize(60, 60), 5));
}

void UIMain::setVolumeValue(float volume)
{
    m_volumeSlider->setValue(volume * 100);
}

void UIMain::setTotalDuration(const QString &durationString)
{
    ui->totalDuration->setText(durationString);
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

void UIMain::onlistViewDbClicked(const QModelIndex &index, bool autoPlay)
{
    this->setPlayStyle(index);
    emit songPlayRequest(index, autoPlay);
}


void UIMain::on_listView_doubleClicked(const QModelIndex &index)
{
    this->onlistViewDbClicked(index, true);
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
    if(ui->listView->model()->rowCount() > 0 ){
        emit skipRequested(true);
    }
}


void UIMain::on_lastBtn_clicked()
{
    if(ui->listView->model()->rowCount() > 0 ){
        emit skipRequested(false);
    }
}


void UIMain::on_volumeBtn_clicked()
{
    m_volumeMenu->popup(ui->volumeBtn->mapToGlobal(QPoint(0, -m_volumeMenu->sizeHint().height())));
}


void UIMain::on_loveBtn_clicked(bool checked)
{
    if(checked){
        ui->loveBtn->setIcon(QIcon(":/icon/love.png"));
        emit collected();
    }
    else {
        ui->loveBtn->setIcon(QIcon(":/icon/dislove.png"));
        emit notCollected();
    }
}

