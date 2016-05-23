#!/bin/bash
# Disable keyboard, mouse, in 5 seconds reboot system

mousedevice='FocalTechPS/2 FocalTech FocalTech Touchpad'
keydevice='AT Translated Set 2 keyboard'

    #Disable keyboard and mouse
    xinput --disable "$mousedevice"
    xinput --disable "$keydevice"

