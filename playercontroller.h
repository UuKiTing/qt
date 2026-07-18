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
    void playbackError(const QString &msg);

public slots:
    void onSongPlayRequested(const QModelIndex &index,  bool autoPlay); // 播放音乐
    void onPlayPauseRequested(); // 自动播放/暂停
    void onSkipPlayRequested(const QModelIndex &index); // 上/下一首音乐

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
};


#endif // PLAYERCONTROLLER_H
