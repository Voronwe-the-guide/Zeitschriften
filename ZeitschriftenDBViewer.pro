QT += quick
QT += positioning
QT += svg
QT += quickcontrols2


CONFIG += c++11
CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DatenbankInfo/cartikeleditor.cpp \
        DatenbankInfo/ccolumn.cpp \
        DatenbankInfo/csqlitedbloader.cpp \
        DatenbankListen/cartikel.cpp \
        DatenbankListen/cartikeldisplaylist.cpp \
        DatenbankListen/causgabe.cpp \
        DatenbankListen/causgabedisplaylist.cpp \
        DatenbankListen/cjahr.cpp \
        DatenbankListen/cjahrdisplaylist.cpp \
        DatenbankListen/clistencontroller.cpp \
        DatenbankListen/czeitschrift.cpp \
        DatenbankListen/czeitschriftdisplaylist.cpp \
        Helper/cerrordisplay.cpp \
        Helper/helper.cpp \
        Settings/csettings.cpp \
        main.cpp \
        sqlite/sqlite3.c

RESOURCES +=  QML/desktop.qrc

TRANSLATIONS += \
    Translation/ZeitschriftenDBViewer_de_DE.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DatenbankInfo/cartikeleditor.h \
    DatenbankInfo/ccolumn.h \
    DatenbankInfo/csqlitedbloader.h \
    DatenbankListen/cartikel.h \
    DatenbankListen/cartikeldisplaylist.h \
    DatenbankListen/causgabe.h \
    DatenbankListen/causgabedisplaylist.h \
    DatenbankListen/cjahr.h \
    DatenbankListen/cjahrdisplaylist.h \
    DatenbankListen/clistencontroller.h \
    DatenbankListen/czeitschrift.h \
    DatenbankListen/czeitschriftdisplaylist.h \
    Helper/cerrordisplay.h \
    Helper/helper.h \
    Settings/csettings.h \
    sqlite/sqlite3.h \
    sqlite/sqlite3ext.h
