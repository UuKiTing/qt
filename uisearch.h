#ifndef UISEARCH_H
#define UISEARCH_H

#include "searchbar_delegate.h"
#include "search_preview_panel.h"
#include <QWidget>
#include <QListView>

namespace Ui {
class UISearch;
}

class UISearch : public QWidget
{
    Q_OBJECT

public:
    explicit UISearch(QWidget *parent = nullptr);
    ~UISearch();


    void connectSignal();

    QString searchText();
    QAbstractItemView* searchListView();
    void showPreviewPanel();
    void hidePreviewPanel();

    void setModel(QAbstractItemView *view, QAbstractItemModel *model);

    QLineEdit* searchBar();

signals:
    void songPlayRequest(const QModelIndex &index, bool autoPlay);

private slots:
    void on_searchBtn_clicked();

    void on_searchBar_returnPressed();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::UISearch *ui;

    SearchPreviewPanel *m_previewPanel;

    SearchBarDelegate *m_delegate{};
};

#endif // UISEARCH_H
