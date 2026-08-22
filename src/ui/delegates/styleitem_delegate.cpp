#include "styleitem_delegate.h"
#include "global.h"
#include "cover_cache_manager.h"
#include "image_loader.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QSortFilterProxyModel>
#include <QPainterPath>
#include <QFile>
#include <QtConcurrent>
#include <QFuture>

StyleItemDelegate::StyleItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
    connect(&ImageLoader::getInstance(), &ImageLoader::imageLoaded,
            this, [this](const QString &path, const QImage &image, const QPersistentModelIndex &pIndex){

        QPixmap pix = QPixmap::fromImage(image);
        CoverCacheManager::getInstance().insert(path, new QPixmap(pix));
        if(pIndex.isValid()){
            emit coverReady(pIndex);
        }
    });
}

QRect StyleItemDelegate::iconRectFor(const QRect &r, int iconSize)
{
    int margin = (r.height() - iconSize) / 2;
    return QRect(r.left() + margin,
                 r.top() + margin,
                 iconSize,
                 iconSize);
}


QRect StyleItemDelegate::durationRectFor(const QRect &r, int durWidth, int durMarginRight)
{
    return QRect(r.right() - durMarginRight - durWidth,
                 r.top(),
                 durWidth,
                 r.height());
}


QRect StyleItemDelegate::favBtnRectFor(const QRect &r, int btnSize, int btnMarginRight)
{
    return QRect(r.right() - btnMarginRight - btnSize,
                 r.center().y() - btnSize / 2,
                 btnSize,
                 btnSize);
}

void StyleItemDelegate::textRectsFor(QRect &titleRect, QRect &artistRect, const QRect &r,int marginLeft, int width)
{
    int margin = r.height() / 10;
    int height = (r.height() - 2 * margin) / 2;
    titleRect = QRect(marginLeft,
                      r.top() + margin,
                      width,
                      height);

    artistRect = QRect(marginLeft,
                       titleRect.bottom(),
                       width,
                       height);
}


void StyleItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool isPlaying = index.data(Role::IsPlaying).toBool();
    const QString title = index.data(Role::Title).toString();
    const QString artist = index.data(Role::Artist).toString();
    const bool isFavorite = index.data(Role::IsFavorite).toBool();

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
    QString path = index.data(Role::Cover).toString();
    QRect iconRect = iconRectFor(option.rect, ICON_SIZE);

    QPixmap *cached = CoverCacheManager::getInstance().get(path);
    if (cached) {
        painter->drawPixmap(iconRect, *cached);
    }
    else{
        QPixmap defaultCover(":/icon/cover.png");
        painter->drawPixmap(iconRect, defaultCover);

        if(!path.isEmpty()){
            QPersistentModelIndex pIndex(index);
            ImageLoader::getInstance().addTask(path, pIndex, QSize(ICON_SIZE, ICON_SIZE), ICON_RADIUS);
        }

        // if (!path.isEmpty()) {
        //     QSize iconSize(ICON_SIZE, ICON_SIZE);
        //     QPersistentModelIndex pIndex(index);

        //     QtConcurrent::run([this, path, iconSize, pIndex](){
        //         QPixmap pix = roundPixmap(path, iconSize, ICON_RADIUS);

        //         QMetaObject::invokeMethod(const_cast<StyleItemDelegate*>(this), [this, path, pix, pIndex]() {
        //             if(!pix.isNull()){
        //                 CoverCacheManager::getInstance().insert(path, new QPixmap(pix));
        //             }

        //             if(pIndex.isValid()){
        //                 emit coverReady(pIndex);
        //             }

        //         }, Qt::QueuedConnection);
        //     });
        // }
    }

    // 右侧保留区域：时长 + 按钮
    QRect durRect = durationRectFor(option.rect, DUR_WIDTH, DUR_MARGIN_RIGHT);
    QRect btnRect = favBtnRectFor(option.rect, BUTTON_SIZE, BUTTON_MARGIN_RIGHT);


    // 文本区域
    int textLeft = iconRect.right() + TEXT_MARGIN_LEFT;
    QRect titleRect, artistRect;
    textRectsFor(titleRect, artistRect, option.rect, textLeft, (btnRect.left() - textLeft) / 2);


    const QColor &titleColor = isPlaying ? selectdColor : blackColor;
    const QColor &subColor = isPlaying ? selectdColor : greyColor;

    // 绘制歌名
    painter->save();
    QFont titleFont = painter->font();
    titleFont.setPixelSize(16);
    titleFont.setBold(true);
    painter->setFont(titleFont);
    painter->setPen(titleColor);

    QFontMetrics titleMetrics(titleFont);
    QString elidedTitle = titleMetrics.elidedText(title, Qt::ElideRight, titleRect.width());
    painter->drawText(titleRect,
                      Qt::AlignLeft | Qt::AlignVCenter,
                      elidedTitle);
    painter->restore();


    // 绘制歌手 + 时长
    painter->save();
    QFont subFont = painter->font();
    subFont.setPixelSize(14);
    painter->setFont(subFont);
    painter->setPen(subColor);

    QFontMetrics subMetrics(subFont);
    QString elidedArtist = subMetrics.elidedText(artist, Qt::ElideRight, artistRect.width());
    painter->drawText(artistRect,
                      Qt::AlignLeft | Qt::AlignVCenter,
                      elidedArtist);
    painter->drawText(durRect,
                      Qt::AlignRight | Qt::AlignVCenter,
                      index.data(Role::DurationString).toString());
    painter->restore();


    // 绘制收藏按钮
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
        QRect btnRect = favBtnRectFor(option.rect, BUTTON_SIZE, BUTTON_MARGIN_RIGHT);

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
