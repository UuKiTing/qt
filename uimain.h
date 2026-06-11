#ifndef UIMAIN_H
#define UIMAIN_H

#include "global.h"
#include "styleitemdelegate.h"
#include <QWidget>
#include <QListView>
#include <QMediaPlayer>
#include <QStandardItemModel>
#include <QStackedWidget>
#include <QAbstractProxyModel>

namespace Ui {
class UIMain;
}

class UIMain : public QWidget
{
    Q_OBJECT

public:
    explicit UIMain(QWidget *parent = nullptr);
    ~UIMain();

    void connectSingal();
    void initVolumeMenu(); // 初始化音量条
    void setPlayStyle(const QModelIndex &index); // 设置音乐播放样式
    void switchStackedWidget(int pageIndex); // 页面切换
    void collectStatusToggle(bool checked); // 收藏状态切换
    void collectIconToggle(bool isFavo); // 收藏图标切换

    void setModel(QAbstractItemView *view, QAbstractItemModel *model); // 为视图设置模型
    void setPlayBtnIcon(QMediaPlayer::PlaybackState state); // 设置播放按钮图标
    void setCurDuration(qint64 position); // 设置当前的播放时长
    void setTotalDuration(const QString &durationString); // 设置总的播放时长
    void setProgressSliderRange(qint64 duration); // 设置进度条的范围
    void setProgressValue(qint64 position); // 设置进度值
    void setCoverPixmap(const QString &cover); // 设置当前播放的音乐封面
    void setVolumeValue(float volume); // 设置音量大小
    void setTitleAndArtist(const QString &title, const QString &artist); // 设置音乐标题和作者
    void setCurrentIndex(const QModelIndex &index); // 设置音乐列表视图的index

    QListView* listView();
    QListView* collectListView();
    QSlider* progressSlider();
    QSlider* volumeSlider();
    int progressValue();
    QStackedWidget* stackedWidget();

signals:
    void songPlayRequest(const QModelIndex &index, bool autoPlay); // 播放歌曲
    void playPauseRequested(); // 播放与暂停
    void skipPlayRequested(bool isNext); // 上/下一首音乐
    void modeChangeRequested(); // 播放模式更改
    void collected(const QModelIndex &index = QModelIndex()); // 收藏音乐
    void cancelCollected(const QModelIndex &index = QModelIndex()); // 取消收藏音乐

public slots:
    void onModeChanged(PlayMode mode);
    void onListViewDbClicked(const QModelIndex &index, bool autoPlay);

private slots:

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_collectListView_doubleClicked(const QModelIndex &index);

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
