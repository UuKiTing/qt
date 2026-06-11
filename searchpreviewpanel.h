#ifndef SEARCHPREVIEWPANEL_H
#define SEARCHPREVIEWPANEL_H

#include <QWidget>
#include <QListView>

namespace Ui {
class SearchPreviewPanel;
}

class SearchPreviewPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPreviewPanel(QWidget *parent = nullptr);
    ~SearchPreviewPanel();

    void switchStackedWidget(int pageIndex);

    QListView* searchListView();

private:
    Ui::SearchPreviewPanel *ui;
};

#endif // SEARCHPREVIEWPANEL_H
