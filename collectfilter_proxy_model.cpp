#include "collectfilter_proxy_model.h"
#include "global.h"
#include <QAbstractItemModel>

CollectFilterProxyModel::CollectFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

bool CollectFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QAbstractItemModel *source = sourceModel();

    return  source->index(source_row, 0).data(Role::IsFavorite).toBool();
}
