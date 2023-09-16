/**
 ** This file is part of the GenPassword project.
 ** Copyright 2023 CM0use dilanuzcs@gmail.com
 ** URL: https://github.com/CM0use/GenPassword
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QMessageBox>
#include <QScreen>
#include <QDir>
#include <QStyleFactory>
#include <QSharedMemory>

#include "passwordgeneratorapp.h"

void initializeDefaultSettings(QSettings &settings);

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };
    app.setApplicationName("GenPassword");
    app.setApplicationVersion("1.0.0");
    app.setWindowIcon(APPICON);
    app.setOrganizationName("CM0use");
    app.setOrganizationDomain("https://github.com/CM0use");

    if (!QFile::exists("config")) {
        const QDir config{ app.applicationDirPath() };
        config.mkdir("config");
    }

    QSettings settings{ app.applicationDirPath()
                           + "/config/Settings.ini",
                       QSettings::Format::IniFormat };
    initializeDefaultSettings(settings);

    QTranslator translator;
    const QStringList languages{ "en", "zh-CN", "hi",
                                 "es", "pt-BR" };
    int indexLanguage{ settings.value("Settings/IndexLanguage").toInt() };
    if (indexLanguage >= 0 && indexLanguage < languages.size()) {
        QString translationFile{ ":/i18n/languages/" +
                                languages[indexLanguage] };
        if (translator.load(translationFile))
            app.installTranslator(&translator);
        else return QMessageBox::critical(nullptr, "Error",
                                         "Could not load translation file.",
                                         "Exit");
    } else return QMessageBox::critical(nullptr, "Error",
                                     "The language index specified in the "
                                     "configuration file is invalid. \n"
                                     "Please check the value and try again.",
                                     "Exit");

    QSharedMemory sharedMemory(app.applicationName());
    if (!sharedMemory.create(1)) {
        return QMessageBox::warning(nullptr,
                                    QObject::tr("GenPassword is now running"),
                                    QObject::tr("The application is already "
                                                "running.\nAnother instance "
                                                "cannot be started."),
                                    QObject::tr("Exit"));
    }

    const QStringList themesNames{ QStyleFactory::keys() };
    int indexTheme { settings.value("Settings/IndexTheme").toInt() };
    if (indexTheme >= 0 && indexTheme < themesNames.size())
        app.setStyle(themesNames[indexTheme]);
    else return QMessageBox::critical(nullptr, QObject::tr("Error"),
                                     QObject::tr("The theme index specified "
                                                 "in the configuration file "
                                                 "is invalid. \nPlease check "
                                                 "the value and try again."),
                                     QObject::tr("Exit"));

    QFile styleSheetFile{ ":/style/qss/stylesheet.qss" };
    styleSheetFile.open(QFile::ReadOnly);
    app.setStyleSheet(styleSheetFile.readAll());

    const std::uint16_t
        WIDTH{ 400 },
        HEIGHT{ 300 },
        DPI_DEFAULT{ 96 };
    qreal screenDPI { app.primaryScreen()->logicalDotsPerInch() };
    QSize windowDimensions(WIDTH * screenDPI / DPI_DEFAULT,
                           HEIGHT * screenDPI / DPI_DEFAULT);

    PasswordGeneratorApp mainWindow;
    mainWindow.setFixedHeight(windowDimensions.height());
    mainWindow.show();
    return app.exec();
}

void initializeDefaultSettings(QSettings &settings)
{
    if (!QFile::exists(settings.fileName())) {
        settings.setValue("Settings/IndexLanguage", 0);
        settings.setValue("Settings/IndexTheme", 0);
        settings.setValue("Settings/ShowPassword", false);
        settings.setValue("Settings/Length", 16);
        settings.setValue("Settings/Numeric", false);
        settings.setValue("Settings/Symbols", false);
        settings.setValue("Settings/lowercase", false);
        settings.setValue("Settings/UpperCase", false);
        settings.setValue("Settings/Add", "");
        settings.setValue("Settings/Remove", "");
    }
}
