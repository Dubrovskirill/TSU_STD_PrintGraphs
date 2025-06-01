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
    graphrenderer.cpp \
    pdfexporter.cpp \
    jpegexporter.cpp \
    exporterfactory.cpp \
    sqlitedatasource.cpp \
    jsondatasource.cpp

HEADERS += \
    mainwindow.h \
    graphrenderer.h \
    iexporter.h \
    pdfexporter.h \
    jpegexporter.h \
    exporterfactory.h \
    ioccontainer.h \
    sqlitedatasource.h \
    jsondatasource.h \
    igraphrenderer.h \
    datasource.h \
    datasourcefactory.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += sql
