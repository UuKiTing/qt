#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QPixmap>


struct SongInfo{
    qlonglong id = -1;
    QString title; // 歌名
    QString artist; // 歌手
    int duration = 0; // 时长/秒
    QString filePath; // 文件路径
    QString cover; // 封面路径
};

enum Role{
    Title = Qt::UserRole,
    Artist,
    Duration,
    FilePath,
    Cover,
    DurationString,
    IsPlaying,
    IsFavorite
};

enum PlayMode{
    Loop,
    Random,
    Single,
    Count
};


QString durationString(int duration); // 返回 "03:24" 格式

QPixmap roundPixmap(const QPixmap &source, const QSize &size, int radius);


#endif // GLOBAL_H

