#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T21:07:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyLittleDragon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    inflation.cpp \
    raw_data.c

HEADERS  += mainwindow.h \
    inflation.h \
    version.h

FORMS    += mainwindow.ui \
    itemdialog.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

DISTFILES += \
    android/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android


windows: RC_FILE = MyLittleDragon.rc

OTHER_FILES += \
    MyLittleDragon.rc
