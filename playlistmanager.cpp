#include "playlistmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QRandomGenerator>
#include <taglib/tag.h>
#include <taglib/fileref.h>


PlayListManager::PlayListManager(QObject *parent)
    : QObject{parent}
{
    m_model = new QStandardItemModel(this);
    // m_dbManager = new DbManager(this);

    // generateJson();
    loadPlayList();
}


void PlayListManager::loadPlayList()
{
    QFile file("playlist.json");
    if(!file.open(QIODevice::ReadOnly)){
        qWarning() << "[PlayListManager]:" << file.errorString();
        return;
    }
    const QJsonArray arr = QJsonDocument::fromJson(file.readAll()).array();
    for(const QJsonValue &val : arr){
        QJsonObject obj = val.toObject();
        QStandardItem *item = new QStandardItem;

        item->setData(obj["title"].toString(), Role::Title);
        item->setData(obj["artist"].toString(), Role::Artist);
        item->setData(obj["duration"].toInt(), Role::Duration);
        item->setData(obj["filePath"].toString(), Role::FilePath);
        item->setData(obj["cover"].toString(), Role::Cover);
        item->setData(durationString(obj["duration"].toInt()), Role::DurationString);
        item->setData(false, Role::IsPlaying);
        item->setData(false, Role::IsFavorite);

        m_model->appendRow(item);
    }
}


void PlayListManager::generateJson()
{
    QJsonArray playlist;

    int id = 1;
    QDir dir(QDir::currentPath() + "/songs");

    for(const QFileInfo &info : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)){
        QJsonObject obj = parseMusic(info.filePath());

        QJsonObject song;
        song["id"] = id++;
        song["title"] = obj["title"].toString();
        song["artist"] = obj["artist"].toString();
        song["duration"] = obj["duration"].toInt();
        song["filePath"] = info.filePath();
        song["cover"] = QDir::currentPath() + "/songImage/" + info.baseName() + ".jpg";

        playlist.append(song);
    }

    QFile jsonFile("playlist.json");
    if(!jsonFile.open(QIODevice::WriteOnly)){
        qWarning() << "[PlayListManager]:" << jsonFile.errorString();
        return;
    }
    jsonFile.write(QJsonDocument(playlist).toJson());
    jsonFile.close();
}

QJsonObject PlayListManager::parseMusic(const QString &filePath)
{
    // 创建 FileRef 对象（自动识别格式）
    TagLib::FileRef file(filePath.toStdWString().c_str());

    QJsonObject obj;

    // 检查文件是否有效、是否有标签信息
    if (!file.isNull() && file.tag()) {
        TagLib::Tag *tag = file.tag();

        obj["title"] = QString::fromStdWString(tag->title().toWString());
        obj["artist"] = QString::fromStdWString(tag->artist().toWString());
        obj["duration"] = file.audioProperties()->lengthInSeconds();
    }

    return obj;
}


void PlayListManager::setCurrentRow(int row)
{
    curRow = row;
}

void PlayListManager::setIsPlayingData(const QModelIndex &index, bool isPlaying)
{
    m_model->itemFromIndex(index)->setData(isPlaying, Role::IsPlaying);
}

void PlayListManager::setCollectData(const QModelIndex &index, bool isCollect)
{
    m_model->itemFromIndex(index)->setData(isCollect, Role::IsFavorite);
}

int PlayListManager::setNextRow(bool isNext)
{
    int currentRow = this->currentRow();
    int total = this->modelRowCount();

    if(Mode == PlayMode::Loop){
        if(isNext) currentRow = (currentRow + 1) % total;
        else currentRow = (currentRow - 1 + total) % total;
    }
    else if(Mode == PlayMode::Random){
        int row = QRandomGenerator::global()->bounded(total);
        while(row == currentRow && total > 1) row = QRandomGenerator::global()->bounded(total);
        currentRow = row;
    }
    else if(Mode == PlayMode::Single){}

    this->setCurrentRow(currentRow);

    return currentRow;
}

void PlayListManager::setMode(PlayMode mode)
{
    Mode = mode;
    emit modeChanged(Mode);
}


QStandardItemModel *PlayListManager::model()
{
    return m_model;
}

QStandardItem *PlayListManager::item(int row)
{
    return m_model->item(row);
}

int PlayListManager::currentRow()
{
    return curRow;
}

PlayMode PlayListManager::mode()
{
    return Mode;
}

int PlayListManager::modelRowCount()
{
    return m_model->rowCount();
}
