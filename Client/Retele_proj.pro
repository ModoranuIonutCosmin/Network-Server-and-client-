QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    bookinspect.cpp \
    clientthread.cpp \
    dashboardui.cpp \
    loginform.cpp \
    main.cpp \
    clientwindow.cpp \
    parseinputoutput.cpp \
    searchresultsitem.cpp \
    spoiler.cpp \
    transfer.cpp

HEADERS += \
    book.h \
    bookinspect.h \
    clientthread.h \
    clientwindow.h \
    dashboardui.h \
    loginform.h \
    parseinputoutput.h \
    searchresultsitem.h \
    spoiler.h \
    transfer.h

FORMS += \
    clientwindow.ui \
    testwind.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    photos.qrc

DISTFILES += \
    photos/bookico.png \
    photos/client_backup_code
