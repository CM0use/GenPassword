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
#include <QSettings>
#include <QMenuBar>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QRandomGenerator>
#include <QProcess>
#include <QMessageBox>
#include <QStatusBar>
#include <QClipboard>
#include <QCloseEvent>
#include <QTimer>
#include <QStyle>
#include <QStyleFactory>

#include "passwordgeneratorapp.h"

PasswordGeneratorApp::PasswordGeneratorApp(QWidget *const parent)
    : QMainWindow{ parent },
    userSettings{ new QSettings(QCoreApplication::applicationDirPath()
                                      + "/config/Settings.ini",
                                  QSettings::Format::IniFormat) },
    currentIndexLanguage{ userSettings->
                           value("Settings/IndexLanguage").toInt() },
    currentIndexTheme{ userSettings->
                        value("Settings/IndexTheme").toInt() },
    appVersion{ qApp->applicationVersion() }, appName{ qApp->applicationName() }
{
    createActions();
    configurateActions();
    createMenus();
    configurateMenus();
    createWidgets();
    configureWidgets();
    if (myTrayIcon->isSystemTrayAvailable()) {
        createTrayIcon();
        configurateTrayIcon();
    }
    connectSignals();
    createUi();
}

void PasswordGeneratorApp::createActions()
{
    exitAction = { new QAction(this) };

    generatePasswordAction = { new QAction(this) };
    cutPasswordAction = { new QAction(this) };
    copyPasswordAction = { new QAction(this) };
    for(const QString &languageName: availableLanguages())
        languageActionList.append(new QAction{ languageName, this });

    for(const QString &themeName: QStyleFactory::keys())
        themeActionList.append(new QAction{ themeName, this });

    useStylePaletteAction = { new QAction };

    aboutAction = { new QAction(this) };
    creditsAction = { new QAction(this) };
    aboutQtAction = { new QAction(this) };
}

void PasswordGeneratorApp::configurateActions()
{
    exitAction->setText(tr("E&xit"));
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    exitAction->setShortcutVisibleInContextMenu(false);

    generatePasswordAction->setText(tr("&Generate Password"));
    generatePasswordAction->setShortcut(QKeySequence::New);
    generatePasswordAction->setShortcutVisibleInContextMenu(false);

    cutPasswordAction->setText(tr("Cut Password"));
    cutPasswordAction->setObjectName("cut");
    cutPasswordAction->setShortcut(QKeySequence::Cut);
    cutPasswordAction->setShortcutVisibleInContextMenu(false);

    copyPasswordAction->setText(tr("&Copy Password"));
    copyPasswordAction->setShortcut(QKeySequence::Copy);
    copyPasswordAction->setShortcutVisibleInContextMenu(false);

    for(qsizetype index{0}; const QString &statusTip: languagesStatusTip())
        languageActionList[index++]->setStatusTip(statusTip);

    languageActionList[currentIndexLanguage]->
        setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));

    themeActionList[currentIndexTheme]->
        setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));

    useStylePaletteAction->setText(tr
                                   ("&Use the standard palette of the theme"));
    useStylePaletteAction->setCheckable(true);

    aboutAction->setText(tr("&About %1").arg(appName));
    aboutAction->setIcon(style()->
                         standardIcon(QStyle::SP_MessageBoxInformation));

    creditsAction->setText(tr("&Credits"));
    creditsAction->setIcon(QIcon{ ":/icons/icon/heart.png" });

    aboutQtAction->setText(tr("About &Qt"));
    aboutQtAction->setIcon(style()->
                           standardIcon(QStyle::SP_TitleBarMenuButton));
}

void PasswordGeneratorApp::createMenus()
{
    fileMenu = { menuBar()->addMenu(tr("&File")) };
    editMenu = { menuBar()->addMenu(tr("&Edit")) };
    viewMenu = { menuBar()->addMenu(tr("&View")) };
    helpMenu = { menuBar()->addMenu(tr("&Help")) };
}

void PasswordGeneratorApp::configurateMenus()
{
    fileMenu->addAction(exitAction);

    editMenu->addAction(generatePasswordAction);
    editMenu->addSeparator();
    editMenu->addAction(cutPasswordAction);
    editMenu->addAction(copyPasswordAction);
    editMenu->addSeparator();
    languagesMenu = { editMenu->addMenu(tr("&Languages")) };
    languagesMenu->addActions(languageActionList);

    themesMenu = { viewMenu->addMenu(tr("&Themes")) };
    themesMenu->addActions(themeActionList);
    themesMenu->addSeparator();
    themesMenu->addAction(useStylePaletteAction);

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(creditsAction);
    helpMenu->addAction(aboutQtAction);
}

void PasswordGeneratorApp::createWidgets()
{
    passwordLineEdit = { new QLineEdit };
    copyToClipBoardButton = { new QPushButton };
    spinBoxPasswordLength = { new QSpinBox };
    showPasswordButton = { new QPushButton };
    checkBoxNumeric = { new QCheckBox };
    checkBoxSymbols = { new QCheckBox };
    lowercaseCheckBox = { new QCheckBox };
    upperCaseCheckBox = { new QCheckBox };
    addCharsLineEdit = { new QLineEdit };
    removeCharLineEdit = { new QLineEdit };
    buttonGeneratePassword = { new QPushButton };
}

void PasswordGeneratorApp::configureWidgets()
{
    passwordLineEdit->setPlaceholderText(tr("Your password will "
                                            "be generated here"));
    passwordLineEdit->setReadOnly(true);
    passwordLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    showPasswordButton->setCheckable(true);
    showPasswordButton->setChecked(userSettings->value("Settings/ShowPassword")
                                       .toBool());
    showPasswordButton->setIcon(QIcon{ ":/icons/icon/showPassword.png" });
    onShowPasswordButtonClicked();

    copyToClipBoardButton->setToolTip(tr("Copy the password to the clipboard"));
    copyToClipBoardButton->setIcon(QIcon{ ":/icons/icon/clipboard.png" });

    spinBoxPasswordLength->setMinimum(1);
    spinBoxPasswordLength->setMaximum(256);

    spinBoxPasswordLength->setValue(userSettings->
                                    value("Settings/Length").toInt());
    checkBoxNumeric->setChecked(userSettings->
                                value("Settings/Numeric").toBool());
    checkBoxNumeric->setToolTip(tr("Contain the numbers: 0-9"));
    checkBoxSymbols->setChecked(userSettings->
                                value("Settings/Symbols").toBool());
    checkBoxSymbols->setToolTip(tr("Contain special symbols:\n"
                                   "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"));
    lowercaseCheckBox->setChecked(userSettings->
                                  value("Settings/lowercase").toBool());
    lowercaseCheckBox->setToolTip(tr("Contain lowercase letters: a-z"));
    upperCaseCheckBox->setChecked(userSettings->
                                  value("Settings/UpperCase").toBool());
    upperCaseCheckBox->setToolTip(tr("Contain uppercase letters: A-Z"));

    addCharsLineEdit->setPlaceholderText(tr("Characters to add"));
    addCharsLineEdit->setText(userSettings->value("Settings/Add").toString());

    removeCharLineEdit->setPlaceholderText(tr("Characters to remove"));
    removeCharLineEdit->setText(userSettings->
                                value("Settings/Remove").toString());

    buttonGeneratePassword->setText(tr("Generate Password"));
}

void PasswordGeneratorApp::createTrayIcon()
{
    myTrayIconMenu = { new QMenu(this) };
    myTrayIcon = { new QSystemTrayIcon(APPICON, this) };
}

void PasswordGeneratorApp::configurateTrayIcon()
{
    myTrayIconMenu->addAction(generatePasswordAction);
    myTrayIconMenu->addSeparator();
    myTrayIconMenu->addAction(cutPasswordAction);
    myTrayIconMenu->addAction(copyPasswordAction);
    myTrayIconMenu->addSeparator();
    myTrayIconMenu->addAction(exitAction);

    myTrayIcon->setContextMenu(myTrayIconMenu);
    myTrayIcon->show();
    myTrayIcon->setToolTip(appName);
    connect(myTrayIcon, &QSystemTrayIcon::activated,
            this, &PasswordGeneratorApp::iconActivated);
}

void PasswordGeneratorApp::iconActivated(QSystemTrayIcon::
                                         ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (!isActiveWindow() || isHidden() || isMinimized()) {
            activateWindow();
            showNormal();
        }
    }
}

void PasswordGeneratorApp::connectSignals()
{
    connect(exitAction, &QAction::triggered, this,
            &PasswordGeneratorApp::close);

    connect(generatePasswordAction, &QAction::triggered,
            this, &PasswordGeneratorApp::generatePassword);

    connect(cutPasswordAction, &QAction::triggered,
            this, &PasswordGeneratorApp::copyPasswordToClipboard);
    connect(copyPasswordAction, &QAction::triggered,
            this, &PasswordGeneratorApp::copyPasswordToClipboard);

    for(const QAction *const languageAction: languageActionList)
        connect(languageAction, &QAction::triggered,
                this, &PasswordGeneratorApp::changeLanguage);

    for(const QAction *const themeAction: themeActionList)
        connect(themeAction, &QAction::triggered,
                this, &PasswordGeneratorApp::changeStyle);

    connect(useStylePaletteAction, &QAction::triggered,
            this, &PasswordGeneratorApp::changePalette);
    connect(useStylePaletteAction, &QAction::triggered,
            this, [&](bool isEnabled) {
                if (isEnabled) QMessageBox::warning(this, tr("Warning"),
                                         tr("This option is enabled.\nWhen this"
                                            " option is enabled, you will need "
                                            "to reselect the theme you have "
                                            "chosen. This will ensure that "
                                            "the theme is applied correctly."
                                            "\n\nThis is because Qt does "
                                            "not currently support stylesheets "
                                            "for custom QStyle subclasses. "
                                            "This functionality will be "
                                            "implemented in "
                                            "a future release."));
                else QMessageBox::warning(this, tr("Warning"),
                                         tr("This option is disabled.\n"
                                            "After disabling this option, "
                                            "it is recommended that you "
                                            "reselect the theme you have "
                                            "chosen, once this is done you "
                                            "will not need to reselect a theme "
                                            "twice for the theme "
                                            "to be applied correctly."));
            });

    connect(aboutAction, &QAction::triggered,
            this, &PasswordGeneratorApp::about);
    connect(creditsAction, &QAction::triggered,
            this, &PasswordGeneratorApp::credits);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);

    connect(showPasswordButton, &QPushButton::clicked,
            this, &PasswordGeneratorApp::onShowPasswordButtonClicked);

    connect(copyToClipBoardButton, &QPushButton::clicked,
            this, &PasswordGeneratorApp::copyPasswordToClipboard);

    connect(buttonGeneratePassword, &QPushButton::clicked,
            this, &PasswordGeneratorApp::generatePassword);
}

void PasswordGeneratorApp::createUi()
{
    QGridLayout *const mainGridLayout{ new QGridLayout };

    std::array<QHBoxLayout *const, 6> horizontalLayout
    {
        new QHBoxLayout,
        new QHBoxLayout,
        new QHBoxLayout,
        new QHBoxLayout,
        new QHBoxLayout,
        new QHBoxLayout
    };

    horizontalLayout[0]->addWidget(passwordLineEdit);
    horizontalLayout[0]->addWidget(showPasswordButton);
    horizontalLayout[0]->addWidget(copyToClipBoardButton);

    horizontalLayout[1]->addWidget(new QLabel{ tr("Password Length") });
    horizontalLayout[1]->addWidget(spinBoxPasswordLength);

    horizontalLayout[2]->addWidget(new QLabel{ tr("Numeric characters") });
    horizontalLayout[2]->addWidget(checkBoxNumeric);
    horizontalLayout[2]->addWidget(new QLabel{ tr("Symbols characters") });
    horizontalLayout[2]->addWidget(checkBoxSymbols);

    horizontalLayout[3]->addWidget(new QLabel{ tr("Lowercase letters") });
    horizontalLayout[3]->addWidget(lowercaseCheckBox);
    horizontalLayout[3]->addWidget(new QLabel{ tr("Uppercase letters") });
    horizontalLayout[3]->addWidget(upperCaseCheckBox);

    horizontalLayout[4]->addWidget(new QLabel{ tr("Add") }, 0, Qt::AlignCenter);
    horizontalLayout[4]->addWidget(new QLabel{ tr("Remove") }, 0,
                                   Qt::AlignCenter);

    horizontalLayout[5]->addWidget(addCharsLineEdit);
    horizontalLayout[5]->addWidget(removeCharLineEdit);

    mainGridLayout->addLayout(horizontalLayout[0], 0, 0);
    mainGridLayout->addLayout(horizontalLayout[1], 1, 0, Qt::AlignCenter);
    mainGridLayout->addLayout(horizontalLayout[2], 2, 0, Qt::AlignCenter);
    mainGridLayout->addLayout(horizontalLayout[3], 3, 0, Qt::AlignCenter);
    mainGridLayout->addLayout(horizontalLayout[4], 4, 0);
    mainGridLayout->addLayout(horizontalLayout[5], 5, 0);
    mainGridLayout->addWidget(buttonGeneratePassword, 6, 0);

    QWidget *const mainWidget{ new QWidget };
    mainWidget->setLayout(mainGridLayout);
    setCentralWidget(mainWidget);

    statusBar()->showMessage(tr("Version %1").arg(appVersion), 5000);
}

QStringList PasswordGeneratorApp::availableLanguages()
{
    return QStringList{ "[en] English", "[zh-CN] 简体中文", "[hi] हिंदी",
                        "[es] Español", "[pt-BR] Português" };
}

QStringList PasswordGeneratorApp::languagesStatusTip()
{
    return QStringList{ "Change to English", "更改为简体中文", "हिंदी में बदलें",
                        "Cambiar a Español", "Mudar para o português"};
}

void PasswordGeneratorApp::generatePassword()
{
    const std::array<bool, 4> selectedCharacters
    {
        checkBoxNumeric->isChecked(),
        checkBoxSymbols->isChecked(),
        lowercaseCheckBox->isChecked(),
        upperCaseCheckBox->isChecked()
    };

    bool hasAnyCharactersSelected
    {
        std::any_of(selectedCharacters.begin(), selectedCharacters.end(),
        [](const bool &checkBoxValue)
        {
            return checkBoxValue;
        })
    }, hasAdditionalCharactersToInclude
        { !addCharsLineEdit->text().isEmpty() };

    if (hasAnyCharactersSelected || hasAdditionalCharactersToInclude) {
        const static std::array<QString, 4> possibleCharacters
        {
            "0123456789",
            "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~",
            "abcdefghijklmnopqrstuvwxyz",
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        };

        QString charactersToUse;
        for(const QString &characters: possibleCharacters)
            charactersToUse.append(characters);

        for(size_t index{0}; index < selectedCharacters.size(); ++index)
            if (!selectedCharacters[index])
                charactersToUse.remove(possibleCharacters[index]);

        for(QChar &c: addCharsLineEdit->text())
            if (!charactersToUse.contains(c))
                charactersToUse.append(c);

        for(QChar &c: removeCharLineEdit->text())
            if (charactersToUse.contains(c))
                charactersToUse.remove(c);

        QString password{ spinBoxPasswordLength->value(), ' ' };

        bool hasCharactersToUse{ !charactersToUse.isEmpty() };
        if (hasCharactersToUse) {
            for(QChar &letter: password)
                letter = { charactersToUse[QRandomGenerator::global()->
                                          bounded(0, charactersToUse.size())] };
            passwordLineEdit->setText(password);
            return;
        }
    }
    QMessageBox::information(this, tr("Information"),
                             tr("No characters have been "
                                "selected for the password. "
                                "\nPlease select at least one character."));
}

void PasswordGeneratorApp::onShowPasswordButtonClicked()
{
    passwordLineEdit->setEchoMode(showPasswordButton->isChecked()?
                                QLineEdit::Password: QLineEdit::Normal);
    showPasswordButton->setToolTip(showPasswordButton->isChecked()?
                                tr("Show Password"): tr("Hide Password"));
}

void PasswordGeneratorApp::copyPasswordToClipboard()
{
    QString password{ passwordLineEdit->text() };
    if (!password.isEmpty()) {
        if (sender()->objectName() == "cut")
            passwordLineEdit->clear();
        QApplication::clipboard()->setText(password);
        statusBar()->showMessage(tr("Password copied!"), 3000);

        copyToClipBoardButton->setIcon(
            style()->standardIcon(QStyle::SP_DialogApplyButton));

        QTimer::singleShot(3000, this,  [&]() {
            copyToClipBoardButton->
                setIcon(QIcon{ ":/icons/icon/clipboard.png" });
        });
    } else
        statusBar()->showMessage(tr("The password is empty. "
                                    "Can't copy to clipboard."), 3000);
}

void PasswordGeneratorApp::changeIcon(QList<QAction *> &list, qsizetype &index,
                                      const qsizetype &newIndex,
                                      const QIcon &icon)
{
    list[index]->setIcon(QIcon{});
    list[newIndex]->setIcon(icon);
    index = { newIndex };
}

void PasswordGeneratorApp::changeLanguage()
{
    qsizetype languageActionIndex
        { languageActionList.indexOf(sender()) };

    const static qsizetype programLanguage{ currentIndexLanguage };

    if (programLanguage != languageActionIndex) {
        changeIcon(languageActionList, currentIndexLanguage,
                   languageActionIndex,
                   style()->standardIcon(QStyle::SP_MessageBoxWarning));
        restart();
    } else changeIcon(languageActionList, currentIndexLanguage,
                   languageActionIndex,
                   style()->standardIcon(QStyle::SP_DialogApplyButton));
}

void PasswordGeneratorApp::restart()
{
    QMessageBox question{ this };
    question.setWindowTitle(tr("Restart Required"));
    question.setText(tr("You will need to restart in order to"
                        " use your new language setting\n"
                        "Your password will be lost if you do not "
                        "save it before restarting."));
    question.addButton(tr("Restart Now"), QMessageBox::YesRole);
    question.buttons().at(0)->
        setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    question.addButton(tr("Restart Later"), QMessageBox::NoRole);
    question.buttons().at(1)->
        setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
    bool isRestartNow{ !question.exec() };
    if (isRestartNow) {
        QProcess process;
        const QString program{ qApp->arguments()[0] },
            workingDirectory{ qApp->applicationDirPath() };
        QStringList arguments{ qApp->arguments() };
        arguments.removeAt(0);
        bool processHasError
            { !process.startDetached(program, arguments, workingDirectory) };
        if (processHasError) {
            QProcess::ProcessError error{ process.error() };
            QMessageBox errorBox{ this };
            errorBox.setWindowTitle(tr("Error"));
            errorBox.setText(tr("Error: \"enum QProcess::ProcessError\"\n"
                                "Value error: %1\n"
                                "The program can still be used\n"
                                "but cannot be restarted due to an error.\n\n"
                                "Do you want copy this error "
                                "in your clipboad?").arg(error));
            errorBox.addButton(tr("Copy to clipboard"), QMessageBox::YesRole);
            errorBox.buttons().at(0)->
                setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
            errorBox.addButton(tr("No"), QMessageBox::NoRole);
            errorBox.buttons().at(1)->
                setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
            bool userDecisionIsYes{ !errorBox.exec() };

            if (userDecisionIsYes)
                QApplication::clipboard()->
                    setText(QString("enum QProcess::ProcessError: %1")
                                                       .arg(error));
        } else close();
    }
}

void PasswordGeneratorApp::closeEvent(QCloseEvent *const event)
{
    saveSettings();
    if (myTrayIcon->isSystemTrayAvailable()) {
        if (!event->spontaneous())
            QApplication::postEvent(qApp, new QEvent(QEvent::Quit));
        else {
            hide();
            event->ignore();
        }
    }
    else event->accept();
}

void PasswordGeneratorApp::changeEvent(QEvent *const event)
{
    if (event->type() == QEvent::StyleChange)
        changePalette();
}

void PasswordGeneratorApp::saveSettings()
{
    userSettings->setValue("Settings/IndexLanguage", currentIndexLanguage);
    userSettings->setValue("Settings/IndexTheme", currentIndexTheme);
    userSettings->setValue("Settings/ShowPassword",
                           showPasswordButton->isChecked());
    userSettings->setValue("Settings/Length", spinBoxPasswordLength->value());
    userSettings->setValue("Settings/Numeric", checkBoxNumeric->isChecked());
    userSettings->setValue("Settings/Symbols", checkBoxSymbols->isChecked());
    userSettings->setValue("Settings/lowercase",
                           lowercaseCheckBox->isChecked());
    userSettings->setValue("Settings/UpperCase",
                           upperCaseCheckBox->isChecked());
    userSettings->setValue("Settings/Add", addCharsLineEdit->text());
    userSettings->setValue("Settings/Remove", removeCharLineEdit->text());
}

void PasswordGeneratorApp::changeStyle()
{
    const QAction *const selectedAction{ qobject_cast<QAction *>(sender()) };
    qApp->setStyle(QStyleFactory::create(selectedAction->text()));
    changeIcon(themeActionList, currentIndexTheme, themeActionList.
                                                   indexOf(selectedAction),
               style()->standardIcon(QStyle::SP_DialogApplyButton));
}

void PasswordGeneratorApp::changePalette()
{
    qApp->setPalette(useStylePaletteAction->isChecked() ?
                         qApp->style()->standardPalette() : QPalette{});
}

void PasswordGeneratorApp::about()
{
    const static QString description
    {
        tr("<div style=\"text-align: center\">"
                "<h1>%1</h1>\n"
                "<p>Version: %2</p>\n"
                "<p>GenPassword is a free password generator that helps you"
                " create random and customizable passwords. "
                "The program adds or removes characters in the "
                "following order:\n</p>\n"
                "<ol>"
                    "<li>Numbers, Symbols, Lowercase letters, "
                    "Uppercase letters</li>\n"
                    "<li>Adds the letters that the user has specified</li>\n"
                    "<li>Removes the letters that the user has specified</li>\n"
                "</ol>"
                "<p>For issues or contributions, visit "
                "the <a href=https://github.com/"
                "CM0use/GenPassword style=color:#0097CF>GitHub repository</a>"
                "</p>\n"
                "<p>Copyright © 2023 - CM0use</p>\n"
                "<p>This program comes with NO WARRANTY OF ANY KIND.<br>\n"
                "See the <a href=https://www.gnu.org/licenses/gpl-3.0.html"
                " style=color:#0097CF>GNU General Public License</a> "
                "for details.</p>"
           "</div>").arg(appName, appVersion)
    };

    QMessageBox::about(this, tr("About %1").arg(appName), description);
}

void PasswordGeneratorApp::credits()
{
    const static QString description
    {
        tr("<div style=\"text-align: center\">"
                "<h1>%1</h1>\n"
                "<p>Created by <a href=https://github.com/CM0use "
                "style=color:#0097CF>CM0use</a></p>\n"
                "<p>Contributors:</p>\n"
                "<ul>"
                   "<li><a href=https://bard.google.com style=color:"
                   "#0097CF>Google Bard</a> (Helper)</li>\n"
                   "<li><a href=https://www.flaticon.com/authors/fr-media "
                   "style=color:#0097CF>"
                   "FR_Media - Flaticon</a> (Icons)</li>\n"
                   "<li><a href=https://www.deepl.com/translator style="
                   "color:#0097CF>DeepL</a> and <a href=https://translate."
                   "google.com style=color:#0097CF>Google Translate</a>"
                   " (Translator)</li>\n"
                "</ul>"
                "<p>Inspired by design: <a href=https://github.com/"
                "ChristopherNugent/Locksmith style=color:#0097CF>"
                "Locksmith</a></p>"
           "</div>").arg(appName)
    };

    QMessageBox::about(this, tr("Credits"), description);
}
