#!/bin/bash

dpkg -l | grep zlib1g-dev > /dev/null
if [ $? -ne 0 ];then
	sudo apt-get install zlib1g-dev
fi

dpkg -l | grep xtightvncviewer > /dev/null
if [ $? -ne 0 ];then
	sudo apt-get install xtightvncviewer
fi

./x86_64-softmmu/qemu-system-x86_64 -hda hd10m.img -vnc 0:0
