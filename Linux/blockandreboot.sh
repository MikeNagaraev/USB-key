#! /bin/bash
# Disable keyboard, mouse, in 5 seconds reboot system

mousedevice='FocalTechPS/2 FocalTech FocalTech Touchpad'
keydevice='AT Translated Set 2 keyboard'

if [[ $1 == -d ]]; then
    #Disable keyboard and mouse
    #Wait for 5 sec and enable
    xinput --disable "$mousedevice"
    xinput --disable "$keydevice"
    sleep 5
    xinput --enable "$mousedevice"
    xinput --enable "$keydevice" 
elif [[ $1 == -r ]]; then
    #Reboot
    sudo reboot
else 
   echo "what?"
fi
export PATH="$PATH:~/scripts"
