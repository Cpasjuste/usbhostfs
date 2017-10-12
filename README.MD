USBHOSTFS VITA
==============

**This is a port of usbhostfs psp plugin to the psp2 (vita). It add a "host0" drive on the vita device, allowing, for example, to browse your computer hard drive from VitaShell via USB**

-----

**Building the plugins (linux)**
```
cd usbhostfs && mkdir cmake-build && cd cmake-build
cmake ..
make
```

**Building the client (linux/deb)**
```
cd usbhostfs_pc && mkdir cmake-build && cd cmake-build
cmake ..
make
```

**Building the client (windows/cygwin)**
```
cd usbhostfs_pc
make BUILD_WIN32=1
```

**Installation (ux0)**
>- copy "usbhostfs.skprx" to "ux0:/tai/"
>- add "ux0:/tai/usbhostfs.skprx" to "*KERNEL" section of "ux0:/tai/config.txt"
>- reboot

**Installation (ur0)**
>- copy "usbhostfs.skprx" to "ur0:/tai/"
>- add "ur0:/tai/usbhostfs.skprx" to "*KERNEL" section of "ur0:/tai/config.txt"
>- reboot

Usage
--------
>- windows : install libusb driver from "usbhostfs_release\windows\driver*" directory
>- windows 10 : disable driver signature verification (https://goo.gl/tyfhHW)
>- run "usbhostfs_pc" on the computer
>- connect the vita with usb cable
>- use "VitaShell" or any application with host0 support to brows the computer 

Thanks
----------
consolex-bordeaux.fr, ScHlAuChi, noname120, motoharu, xyz, yifanlu, frangarcj, Rinnegatamante, davee and people i may forget for what they do for the ps vita.
