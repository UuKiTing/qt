#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QSet>
#include <QPersistentModelIndex>
#include <QSize>

struct ImageTask{
    QString path;
    QPersistentModelIndex pIndex;
    QSize size;
    int radius;
};


class ImageLoader : public QThread
{
    Q_OBJECT
public:
    static ImageLoader& getInstance();

    void addTask(const QString &path, const QPersistentModelIndex &pIndex, QSize size, int radius);

protected:
    void run() override;

signals:
    void imageLoaded(const QString &path, const QImage &image, const QPersistentModelIndex &pIndex);

private:
    ImageLoader(QObject *parent = nullptr);
    ~ImageLoader();

    QImage processImage(const QString &path, QSize size, int radius);

    QMutex m_mutex;
    QWaitCondition m_cond;
    QQueue<ImageTask> m_queue;
    QSet<QString> m_set;

    bool m_stop = false;
};

#endif // IMAGE_LOADER_H
