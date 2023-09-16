#
# ** This file is part of the GenPassword project.
# ** Copyright 2023 CM0use dilanuzcs@gmail.com
# ** URL: https://github.com/CM0use/GenPassword
# **
# ** This program is free software: you can redistribute it and/or modify
# ** it under the terms of the GNU General Public License as published by
# ** the Free Software Foundation, either version 3 of the License, or
# ** (at your option) any later version.
# **
# ** This program is distributed in the hope that it will be useful,
# ** but WITHOUT ANY WARRANTY; without even the implied warranty of
# ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# ** GNU General Public License for more details.
# **
# ** You should have received a copy of the GNU General Public License
# ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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
