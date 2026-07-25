#include "musicplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::Round);

    QCoreApplication::setOrganizationName("Luo");
    QCoreApplication::setApplicationName("MusicPlayer");

    qRegisterMetaType<PlayListInfo>("PlayListInfo");


    MusicPlayer player;
    player.show();

    return a.exec();
}
