#include "song_list_proxy_model.h"
#include "global.h"

SongListProxyModel::SongListProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

void SongListProxyModel::setAllowedSongIds(const QSet<int> &songIds)
{
    m_allowedSongIds = songIds;
    invalidateFilter();
}

bool SongListProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (m_allowedSongIds.isEmpty()) {
        return false;
    }

    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    int songId = index.data(Role::Id).toInt();

    return m_allowedSongIds.contains(songId);
}
