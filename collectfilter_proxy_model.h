#ifndef COLLECTFILTER_PROXY_MODEL_H
#define COLLECTFILTER_PROXY_MODEL_H

#include <QSortFilterProxyModel>

class CollectFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CollectFilterProxyModel(QObject *parent = nullptr);


protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // COLLECTFILTER_PROXY_MODEL_H
