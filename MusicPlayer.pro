QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/taglib/include
LIBS += -L$$PWD/taglib/lib -ltag


SOURCES += \
    appmediator.cpp \
    collectfilter_proxy_model.cpp \
    dbmanager.cpp \
    global.cpp \
    main.cpp \
    music_detail_widget.cpp \
    musicplayer.cpp \
    play_list_manager.cpp \
    player_controller.cpp \
    search_preview_panel.cpp \
    searchbar_delegate.cpp \
    searchfilter_proxy_model.cpp \
    song_list_proxy_model.cpp \
    styleitem_delegate.cpp \
    uimain.cpp \
    uisearch.cpp \
    uisidebar.cpp

HEADERS += \
    appmediator.h \
    collectfilter_proxy_model.h \
    dbmanager.h \
    global.h \
    music_detail_widget.h \
    musicplayer.h \
    play_list_manager.h \
    player_controller.h \
    search_preview_panel.h \
    searchbar_delegate.h \
    searchfilter_proxy_model.h \
    song_list_proxy_model.h \
    styleitem_delegate.h \
    uimain.h \
    uisearch.h \
    uisidebar.h

FORMS += \
    dialog.ui \
    music_detail_widget.ui \
    search_preview_panel.ui \
    uimain.ui \
    uisearch.ui \
    uisidebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    images.qrc \
    rightClickMenu.qrc
