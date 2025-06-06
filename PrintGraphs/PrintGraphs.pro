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
    jsondatasource.cpp \
    linegraphrenderer.cpp \
    areagraphrenderer.cpp \
    scattergraphrenderer.cpp \
    basegraphrenderer.cpp \
    sqlitedatasource.cpp \
    jpegexporter.cpp \
    pdfexporter.cpp

HEADERS += \
    mainwindow.h \
    jsondatasource.h \
    ioccontainer.h \
    iocsetup.h \
    linegraphrenderer.h \
    areagraphrenderer.h \
    scattergraphrenderer.h \
    basegraphrenderer.h \
    sqlitedatasource.h \
    datasource.h \
    iexporter.h \
    igraphrenderer.h \
    jpegexporter.h \
    pdfexporter.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += sql
