QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    passwordgeneratorapp.cpp

HEADERS += \
    passwordgeneratorapp.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: RC_ICONS = icon/appIcon.ico
macx: ICON = icon/appIcon.icns

RESOURCES += \
    i18n.qrc \
    icons.qrc \
    qss.qrc
