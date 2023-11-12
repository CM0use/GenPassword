// GenPassword
// Copyright (c) 2023 CM0use

function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    try {
        component.createOperations();
    } catch (e) {
        console.log(e);
    }

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut",
                               "@TargetDir@/GenPassword.exe",
                               "@StartMenuDir@/GenPassword.lnk");
        component.addOperation("CreateShortcut",
                               "@TargetDir@/GenPassword.exe",
                               "@DesktopDir@/GenPassword.lnk");

        component.addOperation("CreateShortcut",
                               "@TargetDir@/maintenancetool.exe",
                               "@StartMenuDir@/Uninstall.lnk",
                               "iconPath=@TargetDir@/GenPassword.exe");
    } else if (installer.value("os") === "x11") {
        component.addOperation("InstallIcons", "@TargetDir@/icons");
        var app_desktop = "Version=2.0.0\nName=GenPassword\nComment=A random and customizable password generator\nComment[es]=Un generador de contraseñas aleatorio y personalizable\nExec=@TargetDir@/GenPassword\nTerminal=false\nType=Application\nIcon=GenPasswordIcon\nCategories=Utility;Security",
        uninstall_desktop = "Version=2.0.0\nName=Uninstall\nExec=@TargetDir@/maintenancetool\nTerminal=false\nKeyword=GenPassword\nType=Application\nIcon=GenPasswordIcon\nCategories=Utility;Security";

        component.addOperation("CreateDesktopEntry",
                               "GenPassword.desktop",
                               app_desktop);

        component.addOperation("CreateDesktopEntry",
                               "Uninstall.desktop",
                               uninstall_desktop);
    }
}
