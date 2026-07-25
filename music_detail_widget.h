#ifndef MUSIC_DETAIL_WIDGET_H
#define MUSIC_DETAIL_WIDGET_H

#include <QWidget>
#include <QList>
#include <QScrollBar>
#include <QPropertyAnimation>

namespace Ui {
class MusicDetailWidget;
}

struct LyricLine{
    qint64 time;
    qint64 duration;
    QString text;
};

class MusicDetailWidget : public QWidget
{
    Q_OBJECT



public:
    explicit MusicDetailWidget(QWidget *parent = nullptr);
    ~MusicDetailWidget();

    void flushDetail(const QModelIndex &index);

    QList<LyricLine> parseLyricFile(const QString &filePath);

    void showLyrics(const QList<LyricLine> &lyricList);

    int getLyricIndexByTime(const QList<LyricLine> &lyricList, qint64 position);

public slots:
    void onAudioPositionChanged(qint64 position);

private:
    Ui::MusicDetailWidget *ui;

    QList<LyricLine> m_currentLyrics;

    int m_lastLyricIndex = -1;


    QPropertyAnimation *m_scrollAnimation = nullptr;

};

#endif // MUSIC_DETAIL_WIDGET_H
