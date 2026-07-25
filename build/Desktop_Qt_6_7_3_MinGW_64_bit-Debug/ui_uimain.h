/********************************************************************************
** Form generated from reading UI file 'uimain.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIMAIN_H
#define UI_UIMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UIMain
{
public:
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_4;
    QListView *listView;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QListView *collectListView;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *playlistCover;
    QLabel *playlistName;
    QListView *songListView;
    QFrame *controlBar;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *coverBtn;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *titleSinger;
    QPushButton *loveBtn;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *modeBtn;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *lastBtn;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *playBtn;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *nextBtn;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *volumeBtn;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *curDuration;
    QSlider *progressSlider;
    QLabel *totalDuration;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *UIMain)
    {
        if (UIMain->objectName().isEmpty())
            UIMain->setObjectName("UIMain");
        UIMain->resize(1000, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UIMain->sizePolicy().hasHeightForWidth());
        UIMain->setSizePolicy(sizePolicy);
        UIMain->setMinimumSize(QSize(1000, 600));
        UIMain->setBaseSize(QSize(0, 0));
        UIMain->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(UIMain);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 10, 10);
        stackedWidget = new QStackedWidget(UIMain);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"\n"
"\n"
""));
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        listView = new QListView(page);
        listView->setObjectName("listView");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy1);
        listView->setStyleSheet(QString::fromUtf8("    QListView {\n"
"		background-color: white;\n"
"        border: none;\n"
"        outline: none;\n"
"    }\n"
"    QListView::item {\n"
"        height: 48px;\n"
"        padding: 6px 10px;\n"
"        font-size: 14px;\n"
"        color: #333333;\n"
"        border-bottom: 1px solid #f0f0f0;\n"
"    }\n"
""));
        listView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_4->addWidget(listView);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        collectListView = new QListView(page_2);
        collectListView->setObjectName("collectListView");
        collectListView->setStyleSheet(QString::fromUtf8(" QListView {\n"
"		background-color: white;\n"
"        border: none;\n"
"        outline: none;\n"
"    }\n"
"    QListView::item {\n"
"        height: 48px;\n"
"        padding: 6px 10px;\n"
"        font-size: 14px;\n"
"        color: #333333;\n"
"        border-bottom: 1px solid #f0f0f0;\n"
"    }\n"
""));
        collectListView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_5->addWidget(collectListView);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        verticalLayout_6 = new QVBoxLayout(page_3);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(page_3);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_7 = new QVBoxLayout(widget_2);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(30);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        playlistCover = new QLabel(widget_2);
        playlistCover->setObjectName("playlistCover");
        playlistCover->setMinimumSize(QSize(50, 50));
        playlistCover->setMaximumSize(QSize(100, 100));
        playlistCover->setPixmap(QPixmap(QString::fromUtf8(":/icon/cover.png")));
        playlistCover->setScaledContents(true);

        horizontalLayout_4->addWidget(playlistCover);

        playlistName = new QLabel(widget_2);
        playlistName->setObjectName("playlistName");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        playlistName->setFont(font);

        horizontalLayout_4->addWidget(playlistName);


        verticalLayout_7->addLayout(horizontalLayout_4);

        songListView = new QListView(widget_2);
        songListView->setObjectName("songListView");
        songListView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        songListView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_7->addWidget(songListView);


        verticalLayout_6->addWidget(widget_2);

        stackedWidget->addWidget(page_3);

        verticalLayout_2->addWidget(stackedWidget);

        controlBar = new QFrame(UIMain);
        controlBar->setObjectName("controlBar");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(controlBar->sizePolicy().hasHeightForWidth());
        controlBar->setSizePolicy(sizePolicy2);
        controlBar->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	background: white;\n"
"	border-radius: 10px;\n"
"}"));
        controlBar->setFrameShape(QFrame::Shape::StyledPanel);
        controlBar->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(controlBar);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(12, 10, 12, 10);
        coverBtn = new QPushButton(controlBar);
        coverBtn->setObjectName("coverBtn");
        coverBtn->setMinimumSize(QSize(70, 70));
        coverBtn->setMaximumSize(QSize(70, 70));
        coverBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/cover.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        coverBtn->setIcon(icon);
        coverBtn->setIconSize(QSize(60, 60));
        coverBtn->setCheckable(true);
        coverBtn->setFlat(true);

        horizontalLayout_3->addWidget(coverBtn);

        widget = new QWidget(controlBar);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(200, 70));
        widget->setMaximumSize(QSize(200, 70));
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        titleSinger = new QLabel(widget);
        titleSinger->setObjectName("titleSinger");
        titleSinger->setMinimumSize(QSize(0, 20));
        titleSinger->setStyleSheet(QString::fromUtf8("font-size: 16px;"));
        titleSinger->setTextFormat(Qt::TextFormat::RichText);

        verticalLayout_3->addWidget(titleSinger);

        loveBtn = new QPushButton(widget);
        loveBtn->setObjectName("loveBtn");
        loveBtn->setEnabled(true);
        loveBtn->setMinimumSize(QSize(22, 22));
        loveBtn->setMaximumSize(QSize(22, 22));
        loveBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        loveBtn->setMouseTracking(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/dislove.png"), QSize(), QIcon::Mode::Selected, QIcon::State::On);
        loveBtn->setIcon(icon1);
        loveBtn->setIconSize(QSize(22, 22));
        loveBtn->setCheckable(true);
        loveBtn->setFlat(true);

        verticalLayout_3->addWidget(loveBtn);


        horizontalLayout_3->addWidget(widget);

        widget_3 = new QWidget(controlBar);
        widget_3->setObjectName("widget_3");
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        widget_3->setMinimumSize(QSize(32, 32));
        widget_3->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        modeBtn = new QPushButton(widget_3);
        modeBtn->setObjectName("modeBtn");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(modeBtn->sizePolicy().hasHeightForWidth());
        modeBtn->setSizePolicy(sizePolicy3);
        modeBtn->setMinimumSize(QSize(35, 35));
        modeBtn->setMaximumSize(QSize(35, 35));
        modeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/loop.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        modeBtn->setIcon(icon2);
        modeBtn->setIconSize(QSize(20, 20));
        modeBtn->setFlat(true);

        horizontalLayout->addWidget(modeBtn);

        horizontalSpacer_6 = new QSpacerItem(25, 25, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        lastBtn = new QPushButton(widget_3);
        lastBtn->setObjectName("lastBtn");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lastBtn->sizePolicy().hasHeightForWidth());
        lastBtn->setSizePolicy(sizePolicy4);
        lastBtn->setMinimumSize(QSize(35, 35));
        lastBtn->setMaximumSize(QSize(35, 35));
        lastBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/last.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        lastBtn->setIcon(icon3);
        lastBtn->setIconSize(QSize(20, 20));
        lastBtn->setFlat(true);

        horizontalLayout->addWidget(lastBtn);

        horizontalSpacer_8 = new QSpacerItem(25, 25, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        playBtn = new QPushButton(widget_3);
        playBtn->setObjectName("playBtn");
        sizePolicy4.setHeightForWidth(playBtn->sizePolicy().hasHeightForWidth());
        playBtn->setSizePolicy(sizePolicy4);
        playBtn->setMinimumSize(QSize(45, 45));
        playBtn->setMaximumSize(QSize(50, 50));
        playBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        playBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	min-width: 43;\n"
"	min-height: 43;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/pause.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        playBtn->setIcon(icon4);
        playBtn->setIconSize(QSize(43, 43));
        playBtn->setFlat(true);

        horizontalLayout->addWidget(playBtn);

        horizontalSpacer_9 = new QSpacerItem(25, 25, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        nextBtn = new QPushButton(widget_3);
        nextBtn->setObjectName("nextBtn");
        sizePolicy4.setHeightForWidth(nextBtn->sizePolicy().hasHeightForWidth());
        nextBtn->setSizePolicy(sizePolicy4);
        nextBtn->setMinimumSize(QSize(35, 35));
        nextBtn->setMaximumSize(QSize(35, 35));
        nextBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/next.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        nextBtn->setIcon(icon5);
        nextBtn->setIconSize(QSize(20, 20));
        nextBtn->setFlat(true);

        horizontalLayout->addWidget(nextBtn);

        horizontalSpacer_7 = new QSpacerItem(25, 25, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        volumeBtn = new QPushButton(widget_3);
        volumeBtn->setObjectName("volumeBtn");
        sizePolicy3.setHeightForWidth(volumeBtn->sizePolicy().hasHeightForWidth());
        volumeBtn->setSizePolicy(sizePolicy3);
        volumeBtn->setMinimumSize(QSize(35, 35));
        volumeBtn->setMaximumSize(QSize(35, 35));
        volumeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/volume.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        volumeBtn->setIcon(icon6);
        volumeBtn->setIconSize(QSize(25, 25));
        volumeBtn->setFlat(true);

        horizontalLayout->addWidget(volumeBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        curDuration = new QLabel(widget_3);
        curDuration->setObjectName("curDuration");
        curDuration->setMinimumSize(QSize(40, 0));
        curDuration->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(curDuration);

        progressSlider = new QSlider(widget_3);
        progressSlider->setObjectName("progressSlider");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(progressSlider->sizePolicy().hasHeightForWidth());
        progressSlider->setSizePolicy(sizePolicy5);
        progressSlider->setMinimumSize(QSize(200, 0));
        progressSlider->setMaximumSize(QSize(16777215, 16777215));
        progressSlider->setStyleSheet(QString::fromUtf8("	/* \345\207\271\346\247\275\357\274\232\346\265\205\347\201\260\350\203\214\346\231\257 */\n"
"    QSlider::groove:horizontal {\n"
"        background: #f0f0f0;\n"
"        height: 3px;\n"
"        border-radius: 3px;\n"
"    }\n"
"    \n"
"    /* \345\267\262\346\273\221\350\277\207\345\214\272\345\237\237\357\274\232\350\223\235\350\211\262 */\n"
"    QSlider::sub-page:horizontal {\n"
"        background: #4a90d9;\n"
"        border-radius: 3px;\n"
"    }\n"
"    \n"
"    /* \346\273\221\345\235\227\357\274\232\347\231\275\350\211\262\345\234\206\345\275\242\357\274\214\350\223\235\350\211\262\346\217\217\350\276\271 */\n"
"    QSlider::handle:horizontal {\n"
"        background: #ffffff;\n"
"        border: 2px solid #4a90d9;\n"
"        width: 10px;\n"
"        height: -3px;\n"
"        margin: -5px 0;\n"
"        border-radius: 5px;\n"
"    }\n"
"    \n"
"\n"
""));
        progressSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_2->addWidget(progressSlider);

        totalDuration = new QLabel(widget_3);
        totalDuration->setObjectName("totalDuration");
        totalDuration->setMinimumSize(QSize(40, 0));
        totalDuration->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(totalDuration);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 2);

        horizontalLayout_3->addWidget(widget_3);

        horizontalSpacer_4 = new QSpacerItem(200, 60, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        horizontalSpacer = new QSpacerItem(60, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(controlBar);


        retranslateUi(UIMain);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UIMain);
    } // setupUi

    void retranslateUi(QWidget *UIMain)
    {
        UIMain->setWindowTitle(QCoreApplication::translate("UIMain", "Form", nullptr));
        playlistCover->setText(QString());
        playlistName->setText(QCoreApplication::translate("UIMain", "\346\226\260\345\273\272\346\255\214\345\215\2251", nullptr));
        coverBtn->setText(QString());
        titleSinger->setText(QString());
        loveBtn->setText(QString());
        modeBtn->setText(QString());
#if QT_CONFIG(shortcut)
        modeBtn->setShortcut(QCoreApplication::translate("UIMain", "CapsLock, Return", nullptr));
#endif // QT_CONFIG(shortcut)
        lastBtn->setText(QString());
        playBtn->setText(QString());
        nextBtn->setText(QString());
        volumeBtn->setText(QString());
        curDuration->setText(QCoreApplication::translate("UIMain", "00:00", nullptr));
        totalDuration->setText(QCoreApplication::translate("UIMain", "00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UIMain: public Ui_UIMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIMAIN_H
