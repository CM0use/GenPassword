QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
VERSION = 2.0.0
QMAKE_TARGET_PRODUCT = GenPassword
QMAKE_TARGET_DESCRIPTION = "A free generator password"
QMAKE_TARGET_COPYRIGHT = CM0use

win32: RC_ICONS = icons/appIcon.ico

SOURCES += \
    framelesswindow.cpp \
    main.cpp \
    passwordgenerator.cpp \
    switchbutton.cpp \
    window.cpp

HEADERS += \
    framelesswindow.h \
    icons.h \
    passwordgenerator.h \
    switchbutton.h \
    window.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    i18n.qrc \
    icons.qrc \
    qss.qrc
