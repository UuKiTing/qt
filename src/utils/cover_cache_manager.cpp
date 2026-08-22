#include "cover_cache_manager.h"

CoverCacheManager::CoverCacheManager() {
    m_coverCache.setMaxCost(CACHE_LIMIT);

}

CoverCacheManager &CoverCacheManager::getInstance()
{
    static CoverCacheManager manager;
    return manager;
}

QPixmap *CoverCacheManager::get(const QString &key)
{
    return m_coverCache.object(key);
}

bool CoverCacheManager::insert(const QString &key, QPixmap *cover, int cost)
{
    return m_coverCache.insert(key, cover, cost);
}
