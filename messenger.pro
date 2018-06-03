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
    loginpage.cpp

HEADERS  += \
    register.h \
    main_b.h \
    loginpage.h

FORMS    += \
    register.ui \
    main_b.ui \
    login.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
