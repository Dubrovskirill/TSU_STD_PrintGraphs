QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrintGraphs
TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sqlitedatasource.cpp \
    jsondatasource.cpp \
    graphrenderer.cpp

HEADERS += \
    mainwindow.h \
    datasource.h \
    sqlitedatasource.h \
    jsondatasource.h \
    igraphrenderer.h \
    graphrenderer.h \
    ioccontainer.h \
    iocsetup.h \
    pdfexporter.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += sql
