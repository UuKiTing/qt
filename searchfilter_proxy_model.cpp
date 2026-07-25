#include "searchfilter_proxy_model.h"
#include "global.h"
#include <QAbstractItemModel>

SearchFilterProxyModel::SearchFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

void SearchFilterProxyModel::setKeyWord(const QString &keyword)
{
    m_keyword = keyword;
    invalidateFilter(); // 重新过滤
}

bool SearchFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{

    if(m_keyword.isEmpty()) return true;

    QAbstractItemModel *source = sourceModel();

    QModelIndex index = source->index(source_row, 0, source_parent);
    QString title = index.data(Role::Title).toString();
    QString artist = index.data(Role::Artist).toString();

    return title.contains(m_keyword, Qt::CaseInsensitive) ||
           artist.contains(m_keyword, Qt::CaseInsensitive);
}
