#include "styleitemdelegate.h"
#include "global.h"
#include <QPainter>

StyleItemDelegate::StyleItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

void StyleItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isPlaying = index.data(Role::IsPlaying).toBool();
    const QString title = index.data(Role::Title).toString();
    const QString artist = index.data(Role::Artist).toString();
    const int duration = index.data(Role::Duration).toInt();

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
    QIcon icon = roundPixmap(QPixmap(index.data(Role::Cover).toString()), QSize(50, 50), 5);
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
    painter->drawText(durRect, Qt::AlignRight | Qt::AlignVCenter, durationString(duration));
    painter->restore();

    QStyledItemDelegate::paint(painter, option, index);
}

QSize StyleItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 70);
}
