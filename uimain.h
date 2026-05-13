#ifndef UIMAIN_H
#define UIMAIN_H

#include "global.h"
#include "styleitemdelegate.h"
#include <QWidget>
#include <QListView>
#include <QMediaPlayer>
#include <QStandardItemModel>
#include <QStackedWidget>

namespace Ui {
class UIMain;
}

class UIMain : public QWidget
{
    Q_OBJECT

public:
    explicit UIMain(QWidget *parent = nullptr);
    ~UIMain();


    void initVolumeMenu();
    void setPlayStyle(const QModelIndex &index);
    void switchStackedWidget(int pageIndex);

    void setModel(QStandardItemModel *model);
    void setPlayBtnIcon(QMediaPlayer::PlaybackState state);
    void setCurDuration(qint64 position);
    void setProgressSliderRange(qint64 duration);
    void setProgressValue(qint64 position);
    void setCoverPixmap(const QString &cover);
    void setVolumeValue(float volume);
    void setTotalDuration(const QString &durationString);
    void setTitleAndArtist(const QString &title, const QString &artist);
    void setCurrentIndex(const QModelIndex &index);

    QListView* listView();
    QSlider* progressSlider();
    QSlider* volumeSlider();
    int progressValue();
    QStackedWidget* stackedWidget();

signals:
    void songPlayRequest(const QModelIndex &index, bool autoPlay);
    void playPauseRequested();
    void skipRequested(bool isNext);
    void modeChangeRequested();
    void programClosed();
    void collected();
    void notCollected();

public slots:
    void onModeChanged(PlayMode mode);
    void onlistViewDbClicked(const QModelIndex &index, bool autoPlay);

private slots:

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_playBtn_clicked();

    void on_modeBtn_clicked();

    void on_nextBtn_clicked();

    void on_lastBtn_clicked();

    void on_volumeBtn_clicked();

    void on_loveBtn_clicked(bool checked);

private:
    Ui::UIMain *ui;

    StyleItemDelegate *m_delegate{};

    QMenu *m_volumeMenu{};
    QSlider *m_volumeSlider{};
};

#endif // UIMAIN_H
