#include "uisearch.h"
#include "ui_uisearch.h"
#include "global.h"
#include <QTimer>
#include <QMouseEvent>
#include <QApplication>
#include <QSortFilterProxyModel>

UISearch::UISearch(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UISearch)
{
    ui->setupUi(this);

    ui->searchBar->installEventFilter(this);


    m_previewPanel = new SearchPreviewPanel(this);
    m_previewPanel->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);


    connectSignal();

    window()->installEventFilter(this);
}

UISearch::~UISearch()
{
    delete ui;
}

void UISearch::connectSignal()
{
    connect(m_previewPanel->searchListView(), &QListView::doubleClicked, [this](const QModelIndex &index){
        QTimer::singleShot(100, this, &UISearch::hidePreviewPanel);

        QSortFilterProxyModel *model = qobject_cast<QSortFilterProxyModel*>(m_previewPanel->searchListView()->model());

        emit songPlayRequest(model->mapToSource(index), true);
    });

    connect(ui->searchBar, &QLineEdit::textChanged, [this](QString text){
        if(text.isEmpty()) m_previewPanel->switchStackedWidget(SearchPage::Main);
        else m_previewPanel->switchStackedWidget(SearchPage::Search);
    });
}

QString UISearch::searchText()
{
    return ui->searchBar->text();
}

QAbstractItemView *UISearch::searchListView()
{
    return m_previewPanel->searchListView();
}

void UISearch::showPreviewPanel()
{
    QPoint globalPos = ui->searchBar->mapToGlobal(QPoint(0, ui->searchBar->height()));
    m_previewPanel->move(globalPos);
    m_previewPanel->resize(ui->searchBar->width(), 200);
    m_previewPanel->show();
}

void UISearch::hidePreviewPanel()
{
    m_previewPanel->hide();
    ui->searchBar->clearFocus();
}


void UISearch::setModel(QAbstractItemView *view, QAbstractItemModel *model)
{
    view->setModel(model);
}

QLineEdit *UISearch::searchBar()
{
    return ui->searchBar;
}


void UISearch::on_searchBtn_clicked()
{
}


void UISearch::on_searchBar_returnPressed()
{
}


bool UISearch::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->searchBar){
        if(event->type() == QEvent::FocusIn){
            showPreviewPanel();
        }
        else if(event->type() == QEvent::FocusOut){
            if(m_previewPanel && m_previewPanel->isVisible() && m_previewPanel->underMouse()){
                return true;
            }

            hidePreviewPanel();
        }
    }


    if (event->type() == QEvent::MouseButtonPress && m_previewPanel && m_previewPanel->isVisible()) {
        if (!ui->searchBar->underMouse() && !m_previewPanel->underMouse()) {
            hidePreviewPanel();
        }
    }


    return QWidget::eventFilter(watched, event);
}
