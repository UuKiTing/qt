#ifndef COLLECTFILTERPROXYMODEL_H
#define COLLECTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class CollectFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CollectFilterProxyModel(QObject *parent = nullptr);


protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // COLLECTFILTERPROXYMODEL_H
