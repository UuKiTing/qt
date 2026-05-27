QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/taglib/include
LIBS += -L$$PWD/taglib/lib -ltag


SOURCES += \
    collectfilterproxymodel.cpp \
    dbmanager.cpp \
    global.cpp \
    main.cpp \
    musicplayer.cpp \
    playercontroller.cpp \
    playlistmanager.cpp \
    styleitemdelegate.cpp \
    uimain.cpp \
    uisearch.cpp \
    uisidebar.cpp

HEADERS += \
    collectfilterproxymodel.h \
    dbmanager.h \
    global.h \
    musicplayer.h \
    playercontroller.h \
    playlistmanager.h \
    styleitemdelegate.h \
    uimain.h \
    uisearch.h \
    uisidebar.h

FORMS += \
    uimain.ui \
    uisearch.ui \
    uisidebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    images.qrc
