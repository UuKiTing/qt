#ifndef COVER_CACHE_MANAGER_H
#define COVER_CACHE_MANAGER_H

#include <QCache>
#include <QPixmap>

class CoverCacheManager
{
public:
    static CoverCacheManager& getInstance();

    QPixmap* get(const QString &key);

    bool insert(const QString &key, QPixmap *cover, int cost = 1);

private:
    CoverCacheManager();

private:
    mutable QCache<QString, QPixmap> m_coverCache;

    const int CACHE_LIMIT = 200;
};

#endif // COVER_CACHE_MANAGER_H
