#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T22:09:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = messenger
TEMPLATE = app


SOURCES += main.cpp\
    register.cpp \
    main_b.cpp \
    loginpage.cpp \
    getlist.cpp \
    setquery.cpp \
    sendrecievemess.cpp \
    thread.cpp \
    creation.cpp

HEADERS  += \
    register.h \
    main_b.h \
    loginpage.h \
    getlist.h \
    setquery.h \
    sendrecievemess.h \
    thread.h \
    creation.h

FORMS    += \
    register.ui \
    main_b.ui \
    loginpage.ui

DISTFILES +=

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    save.txt
