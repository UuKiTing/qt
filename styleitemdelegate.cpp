#include "styleitemdelegate.h"
#include "global.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QSortFilterProxyModel>
#include <QPainterPath>

StyleItemDelegate::StyleItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

void StyleItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isPlaying = index.data(Role::IsPlaying).toBool();
    const QString title = index.data(Role::Title).toString();
    const QString artist = index.data(Role::Artist).toString();
    const bool isFavorite = index.data(Role::IsFavorite).toBool();;

    const QColor blackColor = Qt::black;
    const QColor selectdColor(0x32, 0x59, 0xCE);
    const QColor greyColor(0x99, 0x99, 0x99);

    painter->save();
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, QColor(0xdfdfdf));
    } else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(option.rect, QColor(0xf1f1f1));
    } else {
        painter->fillRect(option.rect, Qt::white);
    }
    painter->restore();


    // 图标
    painter->save();

    QIcon icon = getPixmap(index.data(Role::Cover).toString(), QSize(50, 50), 5);

    QRect iconRect(option.rect.left() + 10, option.rect.top() + 10, 50, 50);
    icon.paint(painter, iconRect);
    painter->restore();

    const QColor &titleColor = isPlaying ? selectdColor : blackColor;
    const QColor &subColor = isPlaying ? selectdColor : greyColor;

    // 歌名
    painter->save();
    QFont titleFont = painter->font();
    titleFont.setPixelSize(16);
    titleFont.setBold(true);
    painter->setFont(titleFont);
    painter->setPen(titleColor);
    painter->drawText(iconRect.right() + 15, option.rect.top() + 30, title);
    painter->restore();


    // 歌手 + 时长
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(14);
    painter->setFont(font);
    painter->setPen(subColor);
    painter->drawText(iconRect.right() + 15, option.rect.bottom() - 15, artist);
    QRect durRect(option.rect.right() - 80, option.rect.top(), 50, option.rect.height());
    painter->drawText(durRect, Qt::AlignRight | Qt::AlignVCenter, index.data(Role::DurationString).toString());
    painter->restore();


    // 收藏按钮
    painter->save();
    QRect btnRect(option.rect.right() - 120, option.rect.center().y() - 10, 20, 20);

    QIcon favIcon = isFavorite ? QIcon(":/icon/love.png") : QIcon(":/icon/dislove.png");
    favIcon.paint(painter, btnRect);
    painter->restore();

    // QStyledItemDelegate::paint(painter, option, index);
}


QSize StyleItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 70);
}


bool StyleItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QRect btnRect(option.rect.right() - 120, option.rect.center().y() - 10, 20, 20);

        if (btnRect.contains(mouseEvent->pos())) {
            bool isFavo = index.data(Role::IsFavorite).toBool();

            QModelIndex sourceIndex;

            QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(model);

            if(proxyModel) sourceIndex = proxyModel->mapToSource(index);
            else sourceIndex = index;

            if(!isFavo) emit collected(sourceIndex);
            else emit cancelCollected(sourceIndex);

            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}


QPixmap StyleItemDelegate::getPixmap(const QString &path, const QSize &size, int radius) const
{
    if(m_coverCache.contains(path)){
        return m_coverCache.value(path);
    }

    if(m_coverCache.size() >= CACHE_LIMIT){
        m_coverCache.clear();
    }

    QPixmap source(path);
    if (source.isNull()) {
        source = QPixmap(":/icon/cover.png");
    }

    source = source.scaled(size,
                     Qt::KeepAspectRatioByExpanding,
                     Qt::SmoothTransformation);

    QPixmap rounded(size);
    rounded.fill(Qt::transparent);

    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿

    // 圆角裁剪路径
    QPainterPath p;
    p.addRoundedRect(QRectF(0, 0, size.width(), size.height()), radius, radius);
    painter.setClipPath(p);

    // 直接画缩放后的图，裁剪路径会自动切掉圆角外的部分
    painter.drawPixmap(0, 0, source);

    m_coverCache.insert(path, rounded);

    return rounded;
}
