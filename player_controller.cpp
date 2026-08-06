#include "player_controller.h"
#include "global.h"
#include <QFile>

PlayerController::PlayerController(QObject *parent)
    : QObject{parent}
{
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);

    m_player->setAudioOutput(m_audioOutput);

    setVolume(20);

    connect(m_player, &QMediaPlayer::errorOccurred, this, [this](QMediaPlayer::Error err){
        Q_UNUSED(err);
        emit playbackError(m_player->errorString());
    });

}


void PlayerController::setSource(const QModelIndex &index)
{
    QString path = index.data(Role::FilePath).toString();
    m_player->setSource(QUrl::fromLocalFile(path));
}

void PlayerController::play(bool autoPlay)
{
    if(autoPlay) m_player->play();
}

void PlayerController::setPlayProgress(int value)
{
    m_player->setPosition(value);
}

void PlayerController::setVolume(int value)
{
    m_audioOutput->setVolume(value / 100.0);
}

QMediaPlayer *PlayerController::mediaPlayer()
{
    return m_player;
}

QAudioOutput *PlayerController::audioOutput()
{
    return m_audioOutput;
}

int PlayerController::volume()
{
    return static_cast<int>(m_audioOutput->volume() * 100);
}

int PlayerController::position()
{
    return m_player->position();
}

void PlayerController::onSongPlayRequested(const QModelIndex &index, bool autoPlay)
{
    emit isPlayingRestored(); // 恢复歌曲的正在播放标识
    emit currentRowChanged(index.row()); // 更新为当前歌曲的行号
    emit isPlayingChanged(index, true); // 设置当前歌曲的正在播放标识
    this->setSource(index); // 设置播放源
    this->play(autoPlay); // 播放音乐
}

void PlayerController::onPlayPauseRequested()
{
    switch(m_player->playbackState()){
    case QMediaPlayer::PlaybackState::PlayingState:{
        m_player->pause();
        break;
    }
    case QMediaPlayer::PlaybackState::PausedState:{
        m_player->play();
        break;
    }
    case QMediaPlayer::PlaybackState::StoppedState:{
        emit playbackStarted(true);
        break;
    }
    default: break;
    }
}

void PlayerController::onSkipPlayRequested(const QModelIndex &index)
{
    QString filePath = index.data(Role::FilePath).toString();
    if(!QFile::exists(filePath)){
        qWarning() << "File does not exist:" << filePath;
        return;
    }

    emit isPlayingChanged(index, true); // 设置当前歌曲的正在播放标识
    this->setSource(index); // 设置播放源
    this->play(true); // 自动播放音乐
}

