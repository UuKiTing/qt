#include "searchfilterproxymodel.h"
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

    if (m_keyword.isEmpty())
        return false;

    QAbstractItemModel *source = sourceModel();

    QModelIndex index = source->index(source_row, 0);
    QString text = index.data(Role::Title).toString();

    return text.contains(m_keyword, Qt::CaseInsensitive);

}
