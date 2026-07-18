#include "playercontroller.h"
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
    emit isPlayingRestored();
    emit currentRowChanged(index.row());
    emit isPlayingChanged(index, true);
    this->setSource(index);
    this->play(autoPlay);
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

    emit isPlayingChanged(index, true);
    this->setSource(index);
    this->play(true);
}

