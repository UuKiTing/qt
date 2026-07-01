/********************************************************************************
** Form generated from reading UI file 'musicdetailwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICDETAILWIDGET_H
#define UI_MUSICDETAILWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicDetailWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *cover;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *title;
    QLabel *artist;
    QSpacerItem *verticalSpacer;
    QListWidget *listWidget;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *MusicDetailWidget)
    {
        if (MusicDetailWidget->objectName().isEmpty())
            MusicDetailWidget->setObjectName("MusicDetailWidget");
        MusicDetailWidget->resize(1000, 600);
        MusicDetailWidget->setMinimumSize(QSize(1000, 600));
        verticalLayout = new QVBoxLayout(MusicDetailWidget);
        verticalLayout->setSpacing(100);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(MusicDetailWidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(100, 100, 100, 180);
        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(800, 350));
        widget_5->setMaximumSize(QSize(16777215, 16777215));
        widget_5->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(widget_5);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget_5);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(320, 350));
        widget_4->setMaximumSize(QSize(448, 490));
        widget_4->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 42, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_2);

        cover = new QLabel(widget_4);
        cover->setObjectName("cover");
        cover->setMinimumSize(QSize(320, 320));
        cover->setMaximumSize(QSize(448, 448));
        cover->setStyleSheet(QString::fromUtf8(""));
        cover->setText(QString::fromUtf8(""));
        cover->setPixmap(QPixmap(QString::fromUtf8(":/images/avatar.png")));
        cover->setScaledContents(true);
        cover->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(cover);


        horizontalLayout->addWidget(widget_4);

        horizontalSpacer_3 = new QSpacerItem(150, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget_3 = new QWidget(widget_5);
        widget_3->setObjectName("widget_3");
        widget_3->setMinimumSize(QSize(400, 350));
        widget_3->setMaximumSize(QSize(560, 490));
        widget_3->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        title = new QLabel(widget_3);
        title->setObjectName("title");
        title->setMaximumSize(QSize(400, 16777215));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        title->setFont(font);
        title->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        title->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_2->addWidget(title);

        artist = new QLabel(widget_3);
        artist->setObjectName("artist");
        artist->setMaximumSize(QSize(400, 16777215));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        artist->setFont(font1);
        artist->setStyleSheet(QString::fromUtf8("color: rgb(139, 139, 139);"));
        artist->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_2->addWidget(artist);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        listWidget = new QListWidget(widget_3);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(400, 0));
        listWidget->setMaximumSize(QSize(16777215, 16777215));
        listWidget->setStyleSheet(QString::fromUtf8(""));
        listWidget->setFrameShape(QFrame::Shape::NoFrame);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        listWidget->setAutoScroll(true);
        listWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listWidget->setProperty("isWrapping", QVariant(false));
        listWidget->setSpacing(10);
        listWidget->setWordWrap(true);
        listWidget->setSelectionRectVisible(false);

        verticalLayout_2->addWidget(listWidget);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 10);

        horizontalLayout->addWidget(widget_3);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 5);

        horizontalLayout_2->addWidget(widget_5);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget);


        retranslateUi(MusicDetailWidget);

        QMetaObject::connectSlotsByName(MusicDetailWidget);
    } // setupUi

    void retranslateUi(QWidget *MusicDetailWidget)
    {
        MusicDetailWidget->setWindowTitle(QCoreApplication::translate("MusicDetailWidget", "Form", nullptr));
        title->setText(QCoreApplication::translate("MusicDetailWidget", "StarBoy", nullptr));
        artist->setText(QCoreApplication::translate("MusicDetailWidget", "The Weeknd", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MusicDetailWidget: public Ui_MusicDetailWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICDETAILWIDGET_H
