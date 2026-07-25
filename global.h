#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QPixmap>
#include <QModelIndex>


struct SongInfo{
    qlonglong id = -1;
    QString title; // 歌名
    QString artist; // 歌手
    int duration = 0; // 时长/秒
    QString filePath; // 文件路径
    QString cover; // 封面路径
    QString lyrics; // 歌词路径
    bool isFavo; // 是否收藏
};

struct PlayListInfo{
    qlonglong id = -1;
    QString name; // 歌单名称
    int songCount = 0; // 歌曲数量
    QString cover; // 封面路径
};

enum Role{
    Id = Qt::UserRole + 1,
    Title,
    Artist,
    Duration,
    FilePath,
    Cover,
    Lyrics,
    DurationString,
    IsPlaying,
    IsFavorite,
    Invalid
};

enum PlayMode{
    Loop,
    Random,
    Single,
    Count
};

class MainPage {
public:
    enum StackedWidgetIndex {
        Main = 0,
        Collect,
        SongList
    };
};

class SearchPage {
public:
    enum StackedWidgetIndex {
        Main = 0,
        Search
    };
};


QString toDurationString(int duration); // 返回 "03:24" 格式

QPixmap roundPixmap(const QPixmap &source, const QSize &size, int radius);

SongInfo toSongInfo(const QModelIndex &index);

#endif // GLOBAL_H

