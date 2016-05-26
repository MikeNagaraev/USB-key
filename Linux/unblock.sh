#! /bin/bash

mousedevice='FocalTechPS/2 FocalTech FocalTech Touchpad'
keydevice='AT Translated Set 2 keyboard'

    #Disable keyboard and mouse
    xinput --enable "$mousedevice"
    xinput --enable "$keydevice"
   
