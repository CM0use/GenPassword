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

#ifndef PASSWORDGENERATORAPP_H
#define PASSWORDGENERATORAPP_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#define APPICON QIcon{ ":/icons/icon/appIcon.png" }

QT_BEGIN_NAMESPACE
class QSettings;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QCheckBox;
QT_END_NAMESPACE

class PasswordGeneratorApp final: public QMainWindow
{
    Q_OBJECT
public:
    explicit PasswordGeneratorApp(QWidget *const parent = nullptr);
    virtual ~PasswordGeneratorApp() = default;

protected:
    virtual void closeEvent(QCloseEvent *const event) override;
    virtual void changeEvent(QEvent *const event) override;

private:
    void createActions();
    void configurateActions();
    void createMenus();
    void configurateMenus();
    void createWidgets();
    void configureWidgets();
    void createTrayIcon();
    void configurateTrayIcon();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void connectSignals();
    void createUi();

    QStringList languagesStatusTip();
    QStringList availableLanguages();

    void generatePassword();
    void onShowPasswordButtonClicked();
    void copyPasswordToClipboard();

    void changeIcon(QList<QAction *> &list, qsizetype &index,
                    const qsizetype &newIndex, const QIcon &icon);
    void changeLanguage();
    void restart();
    void saveSettings();
    void changeStyle();
    void changePalette();

    void about();
    void credits();

    QSettings *const userSettings;
    qsizetype currentIndexLanguage, currentIndexTheme;
    const QString appVersion, appName;
    QAction *exitAction,
        *generatePasswordAction, *cutPasswordAction, *copyPasswordAction,
        *useStylePaletteAction,
        *aboutAction, *creditsAction, *aboutQtAction;
    QList<QAction *> languageActionList, themeActionList;
    QMenu *fileMenu,
        *editMenu, *languagesMenu,
        *viewMenu, *themesMenu,
        *helpMenu,
        *myTrayIconMenu;
    QSystemTrayIcon *myTrayIcon;
    QLineEdit *passwordLineEdit,
        *addCharsLineEdit, *removeCharLineEdit;
    QPushButton *showPasswordButton, *copyToClipBoardButton,
        *buttonGeneratePassword;
    QSpinBox *spinBoxPasswordLength;
    QCheckBox *checkBoxNumeric, *checkBoxSymbols,
        *lowercaseCheckBox, *upperCaseCheckBox;
};

#endif // PASSWORDGENERATORAPP_H
