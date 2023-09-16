<!--
*** If you like this README,
*** it is available as a template in my repositories,
*** here is the link:
*** https://github.com/CM0use/README-TEMPLATE
-->

<h1 align="center">
  <img src="https://github.com/CM0use/GenPassword/assets/102839710/2f03c7c0-a8a4-41fa-8a26-caaad75e9049" alt="Lock icon from FR_Media - Flaticon">
  <br>GenPassword<br>
  <a href="https://shields.io/"><img src="https://img.shields.io/badge/Windows-0078d7?style=for-the-badge&logo=windows&logoColor=ffffff" alt="Windows"></a>
  <a href="https://shields.io/"><img src="https://img.shields.io/badge/mac%20OS-313131?style=for-the-badge&logo=macos&logoColor=d7d7d7" alt="MacOS"></a>
  <a href="https://shields.io/"><img src="https://img.shields.io/badge/Linux-ffffff?style=for-the-badge&logo=linux&logoColor=000000" alt="Linux"></a>
  <br>
  <a href="https://github.com/CM0use/GenPassword/blob/main/LICENSE">
    <img src="https://img.shields.io/badge/License-GPLv3-4a6484?style=for-the-badge" alt="License GPLv3">
  </a>
</h1>
<h4 align="center">A random and customizable password generator.</h4>
<p align="center">
  <a href="#features">Features</a> •
  <a href="#requirements">Requirements</a> •
  <a href="#install--run">Install & Run</a> •
  <a href="#build--run">Build & Run</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#license">License</a>
</p>

<div align="center">

![program](https://github.com/CM0use/GenPassword/assets/102839710/9b013e51-28e2-4da8-a1ce-f95e1d647269)

</div>

## Features
* Support for multiple languages: English, Chinese, Hindi, Spanish and Portuguese.
* Generates passwords of variable length, from 1 to 256 characters.
* Support for custom characters.
* Modular source code
* Cross-Platform
  - Windows, MacOS and Linux.

## Requirements
Windows: No requirements<br>
Linux: Any X11/Xorg-based windowing system.<br>
MacOS: <a href="https://github.com/CM0use/GenPassword#windowsmacos">Install Qt</a> to build the project.

## Install & Run
### Windows
1. Install <a href="https://github.com/CM0use/GenPassword/releases/download/v1.0.0/GenPasswordInstaller.exe">GenPasswordInstaller.exe</a>

### Linux
1. Download libxcb for Ubuntu/Debian (other <a href="https://wiki.qt.io/Building_Qt_5_from_Git#Libxcb">distributions</a>):
```bash
sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev
```
2. Install <a href="https://github.com/CM0use/GenPassword/releases/download/v1.0.0/GenPasswordInstaller.run">GenPasswordInstaller.run</a>

## Build & Run
### Windows/MacOS
1. Download <a href="https://www.qt.io/download-qt-installer-oss">Qt Online Installer</a> and install the Qt components:
   * Qt Creator
   * MinGW (only on Windows)
   * macOS (only on MacOS)
3. Open the `GenPassword.pro` file in Qt Creator.
4. Make sure to build the project in Release mode.
5. Press the shortcut `Ctrl+B` to build the project.

The build will create a folder called `build-GenPassword` outside the project folder.<br>
The project executable will be inside the `build-GenPassword/release` folder.

### Linux
1. Install the build essentials for Ubuntu/Debian (Other <a href="https://wiki.qt.io/Building_Qt_5_from_Git#Build_essentials">distributions</a>):
```
sudo apt-get install build-essential perl python3 git
```
2. Install libxcb for Ubuntu/Debian (Other <a href="https://wiki.qt.io/Building_Qt_5_from_Git#Libxcb">distributions</a>):
```
sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev
```
3. Download <a href="https://www.qt.io/download-qt-installer-oss">Qt Online Installer</a><br>
3.1 Give permissions to the installer:
```
chmod u+x qt-unified-linux-x64-yourVersion-online.run
````
4. install the Qt components:
   * Qt Creator
   * Desktop gcc
5. Open the `GenPassword.pro` file in Qt Creator.
6. Make sure to build the project in Release mode.
7. Press the shortcut `Ctrl+B` to build the project.

The build will create a folder called `build-GenPassword` outside the project folder.<br>
The project executable will be inside the `build-GenPassword/release` folder.

## Contributing
**Any contribution you make will be greatly appreciated.**<br>
If you have any ideas/suggestions to improve this repository, make a fork and create a pull request.<br>
You can also <a href="https://github.com/CM0use/GenPassword/issues">open the issue tracker</a> to report any improvements or bugs.<br>

## License
**Distributed under the GNU General Public License v3.0**<br>
See accompanying file <a href="https://github.com/CM0use/GenPassword/blob/main/LICENSE">LICENSE</a><br>
or copy at <a href="https://www.gnu.org/licenses/gpl-3.0.txt">GNU General Public License</a>
