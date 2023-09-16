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
        var app_desktop = "Version=1.0.0\nName=GenPassword\nComment=A random and customizable password generator\nComment[zh_CN]=随机和可定制的密码生成器\nComment[hi]=एक यादृच्छिक और अनुकूलन योग्य पासवर्ड जनरेटर\nComment[es]=Un generador de contraseñas aleatorio y personalizable\nComment[pt_BR]=Um gerador de senhas aleatórias e personalizáveis\nExec=@TargetDir@/GenPassword\nTerminal=false\nType=Application\nIcon=GenPasswordIcon\nCategories=Utility;Security",
        uninstall_desktop = "Version=1.0.0\nName=Uninstall\nExec=@TargetDir@/maintenancetool\nTerminal=false\nKeyword=GenPassword\nType=Application\nIcon=GenPasswordIcon\nCategories=Utility;Security";

        component.addOperation("CreateDesktopEntry",
                               "GenPassword.desktop",
                               app_desktop);

        component.addOperation("CreateDesktopEntry",
                               "Uninstall.desktop",
                               uninstall_desktop);
    }
}
