#include "image_loader.h"
#include "global.h"
#include <QThreadPool>

ImageLoader::ImageLoader(QObject *parent)
    : QThread{parent}
{
    start();
}

ImageLoader::~ImageLoader()
{
    m_stop = true;
    m_cond.wakeAll();
    wait();
}

QImage ImageLoader::processImage(const QString &path, QSize size, int radius)
{
    QPixmap pix;
    if (!path.isEmpty()) {
        pix = roundPixmap(path, size, radius);
    }


    return pix.toImage();
}

ImageLoader &ImageLoader::getInstance()
{
    static ImageLoader loader;
    return loader;
}

void ImageLoader::addTask(const QString &path, const QPersistentModelIndex &pIndex, QSize size, int radius)
{
    QMutexLocker locker(&m_mutex);

    if(m_set.contains(path)) return;

    m_set.insert(path);

    m_queue.enqueue({path, pIndex, size, radius});

    m_cond.wakeOne();
}

void ImageLoader::run()
{
    while(!m_stop){

        ImageTask task;
        {
            QMutexLocker locker(&m_mutex);
            while(m_queue.isEmpty() && !m_stop){
                m_cond.wait(&m_mutex);
            }

            if(m_stop) break;
            task = m_queue.dequeue();

        }
        QImage image = processImage(task.path, task.size, task.radius);


        {
            QMutexLocker locker(&m_mutex);
            m_set.remove(task.path);
        }


        if(!image.isNull()){
            emit imageLoaded(task.path, image, task.pIndex);
        }
    }
}
