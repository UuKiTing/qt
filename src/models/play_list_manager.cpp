#include "play_list_manager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QRandomGenerator>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <QCoreApplication>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QFuture>

PlayListManager::PlayListManager(QObject *parent)
    : QObject{parent}
{
    m_model = new QStandardItemModel(this);

    m_collectModel = new CollectFilterProxyModel(this);
    m_collectModel->setSourceModel(m_model);

    m_searchModel = new SearchFilterProxyModel(this);
    m_searchModel->setSourceModel(m_model);

    m_songlistModel = new SongListProxyModel(this);
    m_songlistModel->setSourceModel(m_model);

    // generateData();
    loadPlayList();
}

void PlayListManager::loadPlayList()
{
    QDir dir = QDir(QCoreApplication::applicationDirPath());

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
        item->setData(info.lyrics, Role::Lyrics);
        item->setData(toDurationString(info.duration), Role::DurationString);
        item->setData(false, Role::IsPlaying);
        item->setData(info.isFavo, Role::IsFavorite);

        m_model->appendRow(item);
    }


    // auto *watcher = new QFutureWatcher<QList<SongInfo>>(this);

    // connect(watcher, &QFutureWatcher<QList<SongInfo>>::finished, this, [this, watcher](){
    //     QList<SongInfo> list = watcher->result();

    //     QDir dir = QDir(QCoreApplication::applicationDirPath());

    //     for(SongInfo &info : list){
    //         QStandardItem *item = new QStandardItem;

    //         QString filePath = dir.filePath(info.filePath);
    //         QString coverPath = dir.filePath(info.cover);

    //         item->setData(info.id, Role::Id);
    //         item->setData(info.title, Role::Title);
    //         item->setData(info.artist, Role::Artist);
    //         item->setData(info.duration, Role::Duration);
    //         item->setData(filePath, Role::FilePath);
    //         item->setData(coverPath, Role::Cover);
    //         item->setData(info.lyrics, Role::Lyrics);
    //         item->setData(toDurationString(info.duration), Role::DurationString);
    //         item->setData(false, Role::IsPlaying);
    //         item->setData(info.isFavo, Role::IsFavorite);

    //         m_model->appendRow(item);
    //     }
    // });

    // QFuture<QList<SongInfo>> future = QtConcurrent::run([](){
    //     return DbManager::getInstance().loadSongs();
    // });

    // watcher->setFuture(future);
}


void PlayListManager::generateData()
{
    int id = 1;
    QString currentPath = QCoreApplication::applicationDirPath();
    QDir dir(QDir(currentPath).filePath("songs"));


    for(const QFileInfo &info : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)){
        QJsonObject obj = parseMusic(info.filePath());

        SongInfo song;
        song.id = id++;
        song.title = obj["title"].toString();
        song.artist = obj["artist"].toString();
        song.duration = obj["duration"].toInt();
        song.filePath = "songs/" + info.fileName();
        song.cover = "songImage/" + info.baseName() + ".png";
        song.lyrics = "songLyrics/" + info.baseName() + ".lrc";

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


void PlayListManager::setCurrentRow(int row)
{
    m_curRow = row;
}


void PlayListManager::setIsPlayingData(const QModelIndex &index, bool isPlaying)
{
    m_model->setData(index, isPlaying, Role::IsPlaying);
}


int PlayListManager::setNextRow(bool isNext)
{
    int currentRow = this->currentRow();
    int total = this->modelRowCount();

    if(!m_isSource){
        for(int i = 0; i < m_rows.size(); ++i){
            if(m_rows[i] == currentRow) {
                currentRow = i;
                break;
            }
        }

        total = m_rows.size();
    }


    if(m_mode == PlayMode::Loop){
        if(isNext) currentRow = (currentRow + 1) % total;
        else currentRow = (currentRow - 1 + total) % total;
    }
    else if(m_mode == PlayMode::Random){
        int row = QRandomGenerator::global()->bounded(total);
        while(row == currentRow && total > 1) row = QRandomGenerator::global()->bounded(total);
        currentRow = row;
    }
    else if(m_mode == PlayMode::Single){}


    if(m_isSource){
        this->setCurrentRow(currentRow);
    }
    else{
        this->setCurrentRow(m_rows[currentRow]);
    }

    return m_curRow;
}

void PlayListManager::setMode(PlayMode mode)
{
    m_mode = mode;
    emit modeChanged(m_mode);
}

void PlayListManager::setData(QAbstractItemModel *model, const QModelIndex &index, const QVariant &value, int role)
{
    model->setData(index, value, role);
}

void PlayListManager::setIsSource(bool isSource)
{
    m_isSource = isSource;
}

void PlayListManager::setRows(const QVector<int> &rows)
{
    m_rows = rows;
}


QAbstractItemModel *PlayListManager::model()
{
    return m_model;
}

CollectFilterProxyModel *PlayListManager::collectModel()
{
    return m_collectModel;
}

SearchFilterProxyModel *PlayListManager::searchModel()
{
    return m_searchModel;
}

SongListProxyModel *PlayListManager::songlistModel()
{
    return m_songlistModel;
}

QStandardItem *PlayListManager::item(int row)
{
    return m_model->item(row);
}

QModelIndex PlayListManager::index()
{
    return m_model->index(m_curRow, 0);
}

int PlayListManager::currentRow()
{
    return m_curRow;
}

PlayMode PlayListManager::mode()
{
    return m_mode;
}

int PlayListManager::modelRowCount()
{
    return m_model->rowCount();
}
