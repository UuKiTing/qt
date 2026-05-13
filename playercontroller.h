#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QModelIndex>

class PlayerController : public QObject
{
    Q_OBJECT
public:
    explicit PlayerController(QObject *parent = nullptr);

    void setSource(const QModelIndex &index);
    void play(bool autoPlay);

    void setPlayProgress(int value);
    void setVolume(int value);

    QMediaPlayer* mediaPlayer();
    QAudioOutput* audioOutput();
    int volume();
    int position();

signals:
    void playbackStarted(bool isNext);
    void currentRowChanged(int row);
    void isPlayingChanged(const QModelIndex &index, bool isPlaying);
    void isPlayingRestored();

public slots:
    void onSongPlayRequested(const QModelIndex &index,  bool autoPlay); // 播放音乐
    void onPlayPauseRequested(); // 自动播放/暂停
    void onSkipPlayRequested(const QModelIndex &index);

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;

    int currentVolume = 20;
};


#endif // PLAYERCONTROLLER_H
