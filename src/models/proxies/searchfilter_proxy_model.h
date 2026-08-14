#ifndef SEARCHFILTER_PROXY_MODEL_H
#define SEARCHFILTER_PROXY_MODEL_H

#include <QSortFilterProxyModel>

class SearchFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SearchFilterProxyModel(QObject *parent = nullptr);

    void setKeyWord(const QString &keyword);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QString m_keyword;
};

#endif // SEARCHFILTER_PROXY_MODEL_H
