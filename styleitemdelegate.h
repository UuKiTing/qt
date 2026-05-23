#ifndef STYLEITEMDELEGATE_H
#define STYLEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class StyleItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit StyleItemDelegate(QObject *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    void collected(const QModelIndex &index);
    void notCollected(const QModelIndex &index);

protected:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

};

#endif // STYLEITEMDELEGATE_H
