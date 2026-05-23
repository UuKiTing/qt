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
    m_collectModel = new QStandardItemModel(this);

    // generateData();
    loadPlayList();
    loadCollectPlayList();
}


void PlayListManager::loadPlayList()
{
    QDir dir = QDir(QDir::currentPath());

    for(SongInfo &info : DbManager::getInstance().loadSongs()){
        QStandardItem *item = new QStandardItem;

        QString filePath = dir.filePath(info.filePath);
        QString coverPath = dir.filePath(info.cover);

        item->setData(info.id, Role::Id);
        item->setData(info.title, Role::Title);
        item->setData(info.artist, Role::Artist);
        item->setData(info.duration, Role::Duration);
        item->setData(filePath, Role::FilePath);
        item->setData(coverPath, Role::Cover);
        item->setData(durationString(info.duration), Role::DurationString);
        item->setData(false, Role::IsPlaying);
        item->setData(info.isFavo, Role::IsFavorite);

        m_model->appendRow(item);
    }
}

void PlayListManager::loadCollectPlayList()
{
    QDir dir = QDir(QDir::currentPath());

    for(SongInfo &info : DbManager::getInstance().loadCollectSongs()){
        QStandardItem *item = new QStandardItem;

        QString filePath = dir.filePath(info.filePath);
        QString coverPath = dir.filePath(info.cover);

        item->setData(info.id, Role::Id);
        item->setData(info.title, Role::Title);
        item->setData(info.artist, Role::Artist);
        item->setData(info.duration, Role::Duration);
        item->setData(filePath, Role::FilePath);
        item->setData(coverPath, Role::Cover);
        item->setData(durationString(info.duration), Role::DurationString);
        item->setData(false, Role::IsPlaying);
        item->setData(true, Role::IsFavorite);

        m_collectModel->appendRow(item);
    }
}


void PlayListManager::generateData()
{
    int id = 1;
    QString currentPath = QDir::currentPath();
    QDir dir(QDir(currentPath).filePath("songs"));


    for(const QFileInfo &info : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)){
        QJsonObject obj = parseMusic(info.filePath());

        SongInfo song;
        song.id = id++;
        song.title = obj["title"].toString();
        song.artist = obj["artist"].toString();
        song.duration = obj["duration"].toInt();
        song.filePath = "songs/" + info.fileName();
        song.cover = "songImage/" + info.baseName() + ".jpg";

        DbManager::getInstance().appendMusicData(song);
    }
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

void PlayListManager::addCollectSong(const QModelIndex &index)
{
    QModelIndex idx;
    if(!index.isValid()) idx = this->index();
    else idx = index;

    QStandardItem *item = new QStandardItem;

    QDir dir = QDir(QDir::currentPath());
    QString filePath = dir.filePath(idx.data(Role::FilePath).toString());
    QString coverPath = dir.filePath(idx.data(Role::Cover).toString());

    item->setData(idx.data(Role::Id), Role::Id);
    item->setData(idx.data(Role::Title), Role::Title);
    item->setData(idx.data(Role::Artist), Role::Artist);
    item->setData(idx.data(Role::Duration), Role::Duration);
    item->setData(filePath, Role::FilePath);
    item->setData(coverPath, Role::Cover);
    item->setData(durationString(idx.data(Role::Duration).toInt()), Role::DurationString);
    item->setData(false, Role::IsPlaying);
    item->setData(true, Role::IsFavorite);

    m_collectModel->appendRow(item);
}

bool PlayListManager::removeCollectSong(const QModelIndex &index)
{
    QModelIndex idx;
    if(!index.isValid()) idx = this->index();
    else idx = index;

    int rowCount = m_collectModel->rowCount();
    int id = idx.data(Role::Id).toInt();

    for(int i = 0; i < rowCount; i++){
        QStandardItem *item = m_collectModel->item(i);

        if(item && item->data(Role::Id) == id){
            m_collectModel->removeRow(item->row());
            return true;
        }
    }

    return false;
}


void PlayListManager::setCurrentRow(int row)
{
    curRow = row;
}

void PlayListManager::setIsPlayingData(const QModelIndex &index, bool isPlaying)
{
    m_model->setData(index, isPlaying, Role::IsPlaying);
}

void PlayListManager::setCollectData(const QModelIndex &index, bool isCollect)
{
    m_model->setData(index, isCollect, Role::IsFavorite);
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

void PlayListManager::setData(QStandardItemModel *model, const QModelIndex &index, const QVariant &value, int role)
{
    model->setData(index, value, role);
}



QStandardItemModel *PlayListManager::model()
{
    return m_model;
}

QStandardItemModel *PlayListManager::collectModel()
{
    return m_collectModel;
}

QStandardItem *PlayListManager::item(int row)
{
    return m_model->item(row);
}

QModelIndex PlayListManager::index()
{
    return m_model->index(this->currentRow(), 0);
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
