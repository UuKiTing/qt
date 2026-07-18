#ifndef STYLEITEMDELEGATE_H
#define STYLEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QCache>
#include <QPixmap>

class StyleItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit StyleItemDelegate(QObject *parent = nullptr);

    static QRect iconRectFor(const QRect &r, int iconSize);
    static QRect durationRectFor(const QRect &r, int durWidth, int durMarginRight);
    static QRect favBtnRectFor(const QRect &r, int btnSize, int btnMarginRight);
    static void textRectsFor(QRect &titleRect, QRect &artistRect, const QRect &r,int marginLeft, int width);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    void collected(const QModelIndex &index);
    void cancelCollected(const QModelIndex &index);

protected:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    QPixmap getPixmap(const QString &path, const QSize &size, int radius) const;

    mutable QCache<QString, QPixmap> m_coverCache;

    static constexpr int CACHE_LIMIT = 200;
};

#endif // STYLEITEMDELEGATE_H
