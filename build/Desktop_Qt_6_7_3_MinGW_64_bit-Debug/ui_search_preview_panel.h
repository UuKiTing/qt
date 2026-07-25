/********************************************************************************
** Form generated from reading UI file 'search_preview_panel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_PREVIEW_PANEL_H
#define UI_SEARCH_PREVIEW_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchPreviewPanel
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QHBoxLayout *horizontalLayout;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_2;
    QListView *searchListView;

    void setupUi(QWidget *SearchPreviewPanel)
    {
        if (SearchPreviewPanel->objectName().isEmpty())
            SearchPreviewPanel->setObjectName("SearchPreviewPanel");
        SearchPreviewPanel->resize(400, 300);
        verticalLayout = new QVBoxLayout(SearchPreviewPanel);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(SearchPreviewPanel);
        stackedWidget->setObjectName("stackedWidget");
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        horizontalLayout = new QHBoxLayout(page_3);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        verticalLayout_2 = new QVBoxLayout(page_4);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        searchListView = new QListView(page_4);
        searchListView->setObjectName("searchListView");

        verticalLayout_2->addWidget(searchListView);

        stackedWidget->addWidget(page_4);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(SearchPreviewPanel);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SearchPreviewPanel);
    } // setupUi

    void retranslateUi(QWidget *SearchPreviewPanel)
    {
        SearchPreviewPanel->setWindowTitle(QCoreApplication::translate("SearchPreviewPanel", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchPreviewPanel: public Ui_SearchPreviewPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_PREVIEW_PANEL_H
