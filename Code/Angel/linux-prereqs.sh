#!/bin/bash

# This script will attempt to install any necessary prerequsites on Linux
#  systems. At the moment it only supports Fedora (13) and Ubuntu (10.4). 

if   [ -f /etc/fedora-release ] ; then
	DIST='Fedora'
elif [ -f /etc/lsb-release ] ; then
	DINFO=`cat /etc/lsb-release | grep DISTRIB_ID | sed s/.*=//`
	if [ $DINFO == 'Ubuntu' ] ; then
		DIST='Ubuntu'
	fi
fi

if   [ $DIST == 'Fedora' ] ; then
	yum -y install gcc-c++ make swig mesa-libGLU-devel DevIL-ILUT-devel\
		readline-devel libXrandr-devel freetype-devel
elif [ $DIST == 'Ubuntu' ] ; then
	apt-get -y install build-essential swig libglu1-mesa-dev\
		libreadline-dev libdevil-dev libxrandr-dev libfreetype6-dev\
		joystick
fi

