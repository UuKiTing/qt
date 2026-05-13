#ifndef UISIDEBAR_H
#define UISIDEBAR_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class UISideBar;
}

class UISideBar : public QWidget
{
    Q_OBJECT

public:
    explicit UISideBar(QWidget *parent = nullptr);
    ~UISideBar();

    void init();

    void connectSignals();


signals:
    void pageChanged(int pageIndex);

private:
    Ui::UISideBar *ui;

    QButtonGroup *group{};
};

#endif // UISIDEBAR_H
