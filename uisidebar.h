#ifndef UISIDEBAR_H
#define UISIDEBAR_H

#include "global.h"
#include <QWidget>
#include <QButtonGroup>
#include <QDialog>

namespace Ui {
class UISideBar;
class Dialog;
}


Q_DECLARE_METATYPE(PlayListInfo)

class UISideBar : public QWidget
{
    Q_OBJECT

public:
    explicit UISideBar(QWidget *parent = nullptr);
    ~UISideBar();

    void connectSignals();

    void createPlayList(PlayListInfo &info);

signals:
    void pageChanged(int pageIndex);
    void playlistClicked(const PlayListInfo &info);
    void playlistUpdated(const QSet<int> &songIds);


private slots:
    void on_addSongBtn_clicked();



private:
    Ui::UISideBar *ui;
    Ui::Dialog *m_dialog;

    QDialog *m_songListDialog{};


    QButtonGroup *group{};
};

#endif // UISIDEBAR_H
