QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apcs_system.cpp \
    SRJ_Consts.cpp \
    acustic.cpp \
    apcs.cpp \
    crack.cpp \
    dist_system.cpp \
    fifthtypemessage.cpp \
    firsttypemassage.cpp \
    fourthtypemessage.cpp \
    main.cpp \
    mainwindow.cpp \
    measerement_for.cpp \
    messagesendthread.cpp \
    protsrj.cpp \
    protsrjdata.cpp \
    secondtypemessage.cpp \
    sks.cpp \
    sks_system.cpp \
    srj_consts.cpp \
    stabilization.cpp \
    tenzometria.cpp \
    thirdtypemessage.cpp \
    system.cpp \
    zerotypemesage.cpp

HEADERS += \
    apcs_system.h \
    acustic.h \
    apcs.h \
    crack.h \
    dist_system.h \
    fifthtypemessage.h \
    firsttypemassage.h \
    fourthtypemessage.h \
    mainwindow.h \
    measerement_for.h \
    messagesendthread.h \
    protsrj.h \
    protsrjdata.h \
    secondtypemessage.h \
    sks.h \
    sks_system.h \
    srj_consts.h \
    stabilization.h \
    tenzometria.h \
    thirdtypemessage.h \
    system.h \
    zerotypemesage.h

FORMS += \
    acustic.ui \
    apcs.ui \
    crack.ui \
    dist_system.ui \
    mainwindow.ui \
    measerement_for.ui \
    sks.ui \
    stabilization.ui \
    tenzometria.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
