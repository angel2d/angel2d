#!/bin/bash

# This script will attempt to install any necessary prerequsites on Unix
#  systems. At the moment it only supports Fedora (13), Ubuntu (10.4) and
#  Mac OS X (10.6). 
# 
# On all systems, it should be run with sudo or root privileges. 

if [[ $EUID -ne 0 ]]; then
	echo "This script requires root privileges to run."
	exit 1
fi

if   [ -f /etc/fedora-release ] ; then
	DIST='Fedora'
elif [ -f /etc/lsb-release ] ; then
	DINFO=`cat /etc/lsb-release | grep DISTRIB_ID | sed s/.*=//`
	if [ $DINFO == 'Ubuntu' ] ; then
		DIST='Ubuntu'
	fi
elif [ "`uname`" == 'Darwin' ] ; then
	DIST='Darwin'
fi

if   [ "$DIST" == 'Fedora' ] ; then
	yum -y install gcc-c++ make swig mesa-libGLU-devel DevIL-ILUT-devel\
		readline-devel libXrandr-devel freetype-devel cmake\
		openal-soft-devel libvorbis-devel libpng-devel
elif [ "$DIST" == 'Ubuntu' ] ; then
	apt-get -y install build-essential cmake swig libglu1-mesa-dev\
		libreadline-dev libdevil-dev libxrandr-dev libfreetype6-dev\
		joystick libopenal-dev libvorbis-dev libpng12-dev
elif [ "$DIST" == 'Darwin' ] ; then
	if [ "`which port`" != "" ] ; then
		if [ "`port installed swig | grep currently`" == "" ] ; then
			port install swig-lua
		fi
	else
		echo "MacPorts is not installed -- please download and install from <http://macports.org>."
		exit 1
	fi
	if [ ! -d /System/Library/Extensions/360Controller.kext ] ; then
		hdiutil attach ../Tools/Mac360/360ControllerInstall.0.09.dmg
		installer -target / -pkg /Volumes/360ControllerInstall.0.09/Install360Controller.pkg
		hdiutil detach /Volumes/360ControllerInstall.0.09
		echo "You should restart your machine to get access to the 360 Controller."
	fi
else
	echo "This is not a recognized Linux or UNIX distribution. Currently we support Fedora, Ubuntu, and OS X."
fi

