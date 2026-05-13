#ifndef UISEARCH_H
#define UISEARCH_H

#include <QWidget>

namespace Ui {
class UISearch;
}

class UISearch : public QWidget
{
    Q_OBJECT

public:
    explicit UISearch(QWidget *parent = nullptr);
    ~UISearch();

private:
    Ui::UISearch *ui;
};

#endif // UISEARCH_H
