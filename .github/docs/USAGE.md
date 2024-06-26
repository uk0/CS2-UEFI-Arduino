# Usage
> [!IMPORTANT]
> 💻 Calypso might doesnt work on legacy boot systems 

## Table of Contents
- [Visual Studio Installation](#visual-studio-installation)
- [Python Installation](#python-installation)
- [Calypso Installation](#calypso-installation)
  - [1. Download](#1-download)
  - [2. Compile](#2-compile)
  - [3. USB Setup](#3-usb-setup)
  - [4. Booting from USB Drive](#4-booting-from-usb-drive)
  - [5. Finish](#5-finish)
- [Additional Information](#additional-information)
  - [Arduino Usage](#arduino-usage)

## Visual Studio Installation

- Open [Visual Studio official page](https://visualstudio.microsoft.com/ru/downloads/)

- Scroll down and click on ``community free download``. 
<img src="https://i.imgur.com/Tqvqy5P.png" height="250" />

- After download open file and follow the installation process until you reach download tab

- On download tab select ``Desktop development with C++``
<img src="https://i.imgur.com/eWnqAD0.png" height="250" />

- After that click on install and Visual Studio will be installed


## Python Installation

- Open [Python official page](https://www.python.org/downloads/)

- Click on ``Download Python``. 
<img src="https://i.imgur.com/2PfCpNZ.png" height="250" />

- After download open file and select this сheckmark:
<img src="https://i.imgur.com/B1B2YpK.png" height="250" />

- After that click on ``Install Now`` and Python will be installed


## Calypso Installation

### 1. Download

- Download and Extract last Calypso Release from [releases page](https://github.com/3a1/CS2-Calypso/releases/) or directly from [github page](https://github.com/3a1/CS2-Calypso)
  
<img src="https://i.imgur.com/NjpLK7J.png" height="250" /><img src="https://i.imgur.com/vR5KNOT.png" height="250" />

### 2. Compile
- Open Calypso folder and start ``build.bat`` it will automatically compile binaries and copy them to the folder (CalypsoEFI.efi will be compied in USB folder)

(optional: you can open ``CalypsoUM.sln`` and ``CalypsoEFI.efi`` to build project by yourself)

### 3. USB Setup
- Insert your usb drive and format to ``FAT32``

<img src="https://i.imgur.com/XGf3iWj.png" height="250" /><img src="https://i.imgur.com/vPRhMwB.png" height="250" />

- **Download** EFI-Shell from [this link](https://github.com/tianocore/edk2-archive/raw/master/ShellBinPkg/UefiShell/X64/Shell.efi) and rename it from ``shell.efi`` to ``bootx64.efi``

- Open USB folder inside Calypso, create ``EFI/Boot/`` folders and paste inside ``bootx64.efi`` (``USB/EFI/Boot/bootx64.efi``)

- Copy contents from Calypso USB folder and paste to the usb drive like this:

```
USB:.
 │   CalypsoEFI.efi
 │   Startup.nsh
 │
 └───EFI
      └───Boot
              bootx64.efi
```

- Calypso EFI Setup Done!

### 4. Booting from USB Drive
> [!NOTE] 
> 🖥️ Disable Secure Boot in your bios in order to be able boot from usb devices!

If you have PC search in google ``{your motherboard model} bios key`` or if you have laptop search instead ``{your laptop model} bios key``
(generally in 99% it will be one of these keybinds:  ``F1``, ``F2``, ``F10``, ``F12``, ``Del``, or ``Esc``) 

After that there is two methods how you can boot from usb drive:
<details>
<summary>Boot manually from usb drive</summary>
  
  > with manually booting you need to do it every system restart when you want to use the cheat

After manual boot from usb you should back to the bios automatically, after that you need just to boot like before you did with usb but now with windows partition. on booting stage you should also see Calypso logo on the red background.
  
</details>

<details>
<summary>Change bios boot order </summary>

  > after you change the boot order, your system will be automatically booting from usb drive every system startup until you will change boot order back

After changing boot order priority you need just restart your system and you should see Calypso logo on the red background , Windows should boot automatically.

</details>

### 5. Finish
- Open ``update_offsets.py``(if you can't you can open cmd in directory and type ``python update_offsets.py``)
- Start ``CS2``
- Open Calypso folder again and start ``CalypsoUM.exe``, it will automatically creates config file
- Enjoy :)

## Additional Information

### Arduino Usage
> [!WARNING]
> 🤖 Arduino usage might doesn't work for Windows 11.

In order to make cheat work with arduino:

- Connect your Arduino
- Inside Calypso folder go to ``Arduino`` and find ``arduino.ino`` arduino scratch file
- In case that you doesn't have Arduino IDE you need to download it from [official website](https://www.arduino.cc/en/software)
- Open ``arduino.ino`` with Arduino IDE and upload scratch to your arduino (you may be required to select a board before)
<img src="https://i.imgur.com/8xwJsxY.png" height="250" />

- Open ``settings.ini`` (if you doesnt have config file - open CalypsoUM and it will create config automatically)
- Find this Arduino section:
```
[Arduino]
enable: false
name: Arduino_Leonardo
```
(remember that name in config file **can't** contain spaces, replace spaces with underscores instead)

- Change ``enable`` to ``true`` and if you have arduino different than Arduino Leonardo change its ``name`` to name from Device Manager
- Open CalypsoUM.exe and Calypso will automatically connect to the arduino
