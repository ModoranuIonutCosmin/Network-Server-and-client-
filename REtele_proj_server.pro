QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    clienthandlingthread.cpp \
    connection.cpp \
    enumhelpers.cpp \
    mmain.cpp \
    netcode.cpp \
    networkserver.cpp \
    rbook.cpp \
    recommendengine.cpp \
    rrating.cpp \
    serverwindow.cpp \
    sqlcontroller.cpp \
    stringhelpers.cpp \
    transferscontroller.cpp

HEADERS += \
    book.h \
    clienthandlingthread.h \
    connection.h \
    enumhelpers.h \
    netcode.h \
    networkserver.h \
    rbook.h \
    recommendengine.h \
    rrating.h \
    serverwindow.h \
    sqlcontroller.h \
    stringhelpers.h \
    transferscontroller.h

FORMS += \
    serverwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
