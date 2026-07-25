/********************************************************************************
** Form generated from reading UI file 'uisidebar.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UISIDEBAR_H
#define UI_UISIDEBAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UISideBar
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *avatarBtn;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QToolButton *homeBtn;
    QToolButton *collectBtn;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *addSongBtn;
    QWidget *songList;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *UISideBar)
    {
        if (UISideBar->objectName().isEmpty())
            UISideBar->setObjectName("UISideBar");
        UISideBar->resize(68, 465);
        UISideBar->setMinimumSize(QSize(0, 0));
        UISideBar->setMaximumSize(QSize(68, 16777215));
        UISideBar->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(UISideBar);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(UISideBar);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 10px;\n"
"	padding: 5px;\n"
"	min-height: 40px;\n"
"	max-height:40px;\n"
"	min-width: 40px;\n"
"	max-width: 40px;\n"
"}\n"
"\n"
"/*QPushButton:checked {\n"
"	background-color: #E9E9E9;\n"
"}*/\n"
"\n"
"\n"
"\n"
"\n"
""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        avatarBtn = new QPushButton(widget_3);
        avatarBtn->setObjectName("avatarBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(40);
        sizePolicy1.setVerticalStretch(40);
        sizePolicy1.setHeightForWidth(avatarBtn->sizePolicy().hasHeightForWidth());
        avatarBtn->setSizePolicy(sizePolicy1);
        avatarBtn->setMinimumSize(QSize(50, 50));
        avatarBtn->setMaximumSize(QSize(50, 50));
        avatarBtn->setStyleSheet(QString::fromUtf8(""));
        avatarBtn->setIconSize(QSize(30, 30));
        avatarBtn->setFlat(true);

        verticalLayout_4->addWidget(avatarBtn);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName("widget_2");
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	background-color: rgb(235, 235, 235);\n"
"    border-radius: 10px;\n"
"	padding: 5px;\n"
"	min-height: 40px;\n"
"	max-height:40px;\n"
"	min-width: 40px;\n"
"	max-width: 40px;\n"
"}\n"
"\n"
"QToolButton:checked {\n"
"    background-color: #D8D8D8;\n"
"}\n"
"\n"
"QToolButton:pressed {\n"
"	padding: 5px;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        homeBtn = new QToolButton(widget_2);
        homeBtn->setObjectName("homeBtn");
        homeBtn->setMinimumSize(QSize(50, 50));
        homeBtn->setMaximumSize(QSize(50, 50));
        homeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/homeSelect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        homeBtn->setIcon(icon);
        homeBtn->setIconSize(QSize(28, 28));
        homeBtn->setCheckable(true);
        homeBtn->setChecked(true);

        verticalLayout_3->addWidget(homeBtn);

        collectBtn = new QToolButton(widget_2);
        collectBtn->setObjectName("collectBtn");
        collectBtn->setMinimumSize(QSize(50, 50));
        collectBtn->setMaximumSize(QSize(50, 50));
        collectBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/dislove.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        collectBtn->setIcon(icon1);
        collectBtn->setIconSize(QSize(22, 22));
        collectBtn->setCheckable(true);
        collectBtn->setChecked(false);

        verticalLayout_3->addWidget(collectBtn);


        verticalLayout_4->addWidget(widget_2);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        widget_4->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"	background-color: rgb(235, 235, 235);\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(widget_4);
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        addSongBtn = new QPushButton(widget_4);
        addSongBtn->setObjectName("addSongBtn");
        addSongBtn->setMinimumSize(QSize(50, 50));
        addSongBtn->setMaximumSize(QSize(50, 50));
        addSongBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addSongBtn->setIcon(icon2);
        addSongBtn->setIconSize(QSize(30, 30));
        addSongBtn->setFlat(true);

        verticalLayout_5->addWidget(addSongBtn);

        songList = new QWidget(widget_4);
        songList->setObjectName("songList");
        songList->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #D8D8D8;\n"
"}\n"
""));
        verticalLayout_6 = new QVBoxLayout(songList);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        verticalLayout_5->addWidget(songList);


        verticalLayout->addWidget(widget_4);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);

        verticalLayout_2->addWidget(widget);


        retranslateUi(UISideBar);

        QMetaObject::connectSlotsByName(UISideBar);
    } // setupUi

    void retranslateUi(QWidget *UISideBar)
    {
        UISideBar->setWindowTitle(QCoreApplication::translate("UISideBar", "Form", nullptr));
        avatarBtn->setText(QString());
#if QT_CONFIG(tooltip)
        homeBtn->setToolTip(QCoreApplication::translate("UISideBar", "\344\270\273\351\241\265", nullptr));
#endif // QT_CONFIG(tooltip)
        homeBtn->setText(QString());
#if QT_CONFIG(tooltip)
        collectBtn->setToolTip(QCoreApplication::translate("UISideBar", "\345\226\234\346\254\242", nullptr));
#endif // QT_CONFIG(tooltip)
        collectBtn->setText(QString());
#if QT_CONFIG(tooltip)
        addSongBtn->setToolTip(QCoreApplication::translate("UISideBar", "\346\226\260\345\273\272\346\255\214\345\215\225", nullptr));
#endif // QT_CONFIG(tooltip)
        addSongBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UISideBar: public Ui_UISideBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UISIDEBAR_H
