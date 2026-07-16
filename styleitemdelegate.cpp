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
    const bool isFavorite = index.data(Role::IsFavorite).toBool();

    const QColor blackColor = Qt::black;
    const QColor selectdColor(0x32, 0x59, 0xCE);
    const QColor greyColor(0x99, 0x99, 0x99);

    const int ICON_SIZE = 50;
    const int ICON_RADIUS = 5;
    const int ICON_MARGIN = (70 - ICON_SIZE) / 2;
    const int BUTTON_SIZE  = 20;
    const int BUTTON_MARGIN_RIGHT = 25;
    const int TEXT_MARGIN_LEFT = 15;
    const int TEXT_MARGIN_TOPBOTTOM = 10;
    const int DUR_MARGIN_RIGHT = 50;
    const int DUR_WIDTH = 50;

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
    QPixmap pix = getPixmap(index.data(Role::Cover).toString(),
                           QSize(ICON_SIZE, ICON_SIZE),
                           ICON_RADIUS);
    QRect iconRect(option.rect.left() + ICON_MARGIN,
                   option.rect.top() + ICON_MARGIN,
                   ICON_SIZE,
                   ICON_SIZE);
    QIcon icon = QIcon(pix);
    icon.paint(painter, iconRect);



    // 右侧保留区域：时长 + 按钮
    QRect durRect(option.rect.right() - DUR_MARGIN_RIGHT - DUR_WIDTH,
                  option.rect.top(),
                  DUR_WIDTH,
                  option.rect.height());

    QRect btnRect(durRect.left() - BUTTON_MARGIN_RIGHT - BUTTON_SIZE,
                  option.rect.center().y() - BUTTON_SIZE / 2,
                  BUTTON_SIZE,
                  BUTTON_SIZE);


    // 文本区域
    int textLeft = iconRect.right() + TEXT_MARGIN_LEFT;
    int width = (btnRect.left() - textLeft) / 2;
    QRect titleRect(textLeft,
                    option.rect.top() + TEXT_MARGIN_TOPBOTTOM,
                    width,
                    (option.rect.height() - 2 * TEXT_MARGIN_TOPBOTTOM) / 2);

    QRect artistRect(textLeft,
                    titleRect.bottom(),
                    width,
                    (option.rect.height() - 2 * TEXT_MARGIN_TOPBOTTOM) / 2);

    // 歌名
    const QColor &titleColor = isPlaying ? selectdColor : blackColor;
    const QColor &subColor = isPlaying ? selectdColor : greyColor;

    painter->save();
    QFont titleFont = painter->font();
    titleFont.setPixelSize(16);
    titleFont.setBold(true);
    painter->setFont(titleFont);
    painter->setPen(titleColor);

    QFontMetrics titleMetrics(titleFont);
    QString elidedTitle = titleMetrics.elidedText(title,
                                                  Qt::ElideRight,
                                                  titleRect.width());
    painter->drawText(titleRect,
                      Qt::AlignLeft | Qt::AlignVCenter,
                      elidedTitle);
    painter->restore();


    // 歌手 + 时长
    painter->save();
    QFont subFont = painter->font();
    subFont.setPixelSize(14);
    painter->setFont(subFont);
    painter->setPen(subColor);

    QFontMetrics subMetrics(subFont);
    QString elidedArtist = subMetrics.elidedText(artist,
                                                  Qt::ElideRight,
                                                  artistRect.width());
    painter->drawText(artistRect,
                      Qt::AlignLeft | Qt::AlignVCenter,
                      elidedArtist);
    painter->drawText(durRect,
                      Qt::AlignRight | Qt::AlignVCenter,
                      index.data(Role::DurationString).toString());
    painter->restore();

    // 收藏按钮
    painter->save();
    QIcon favIcon = isFavorite ? QIcon(":/icon/love.png") : QIcon(":/icon/dislove.png");
    favIcon.paint(painter, btnRect);
    painter->restore();
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
    if(m_coverCache.maxCost() == 0){
        m_coverCache.setMaxCost(CACHE_LIMIT);
    }

    QPixmap *cached = m_coverCache.object(path);
    if (cached)  return *cached;



    QPixmap source(path);
    if (source.isNull()) {
        source = QPixmap(":/icon/cover.png");
    }

    source = source.scaled(size, Qt::KeepAspectRatioByExpanding,
                                 Qt::SmoothTransformation);

    QPixmap rounded(size);
    rounded.fill(Qt::transparent);
    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath p;
    p.addRoundedRect(QRectF(0, 0, size.width(), size.height()), radius, radius);
    painter.setClipPath(p);
    painter.drawPixmap(0, 0, source);

    m_coverCache.insert(path, new QPixmap(rounded), 1);
    return rounded;
}
