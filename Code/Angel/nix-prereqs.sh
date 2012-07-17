#!/bin/bash

# This script will attempt to install any necessary prerequsites on Unix
#  systems. At the moment it only supports Fedora, Ubuntu, and Mac OS X. 
# 
# On all systems, it needs to be run with sudo or root privileges. 

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
	yum -y install gcc-c++ make cmake swig mesa-libGLU-devel readline-devel\
		DevIL-ILUT-devel libXrandr-devel freetype-devel\
		openal-soft-devel libvorbis-devel libpng-devel
elif [ "$DIST" == 'Ubuntu' ] ; then
	apt-get -y install build-essential cmake swig libglu1-mesa-dev\
		libreadline-dev libdevil-dev libxrandr-dev libfreetype6-dev\
		joystick libopenal-dev libvorbis-dev libpng12-dev ncurses-dev
elif [ "$DIST" == 'Darwin' ] ; then
	if   [ "`which make`" == "" ] ; then
		echo "The Xcode command line tools are not installed -- use the Downloads section of the Xcode preferences to install them."
		exit 1
	elif [ "`which port`" == "" ] ; then
		echo "MacPorts is not installed -- please download and install from <http://macports.org>."
		exit 1
	else
		if [ "`port installed swig-lua | grep currently`" == "" ] ; then
			port install swig-lua
		fi
	fi
	if [ ! -d /System/Library/Extensions/360Controller.kext ] ; then
		hdiutil attach ../Tools/Mac360/360ControllerInstall.0.11.dmg
		installer -target / -pkg /Volumes/360ControllerInstall/Install360Controller.pkg
		hdiutil detach /Volumes/360ControllerInstall
		echo "You should restart your machine to get access to the 360 Controller."
	fi
else
	echo "This is not a recognized Linux or UNIX distribution. Currently we support Fedora, Ubuntu, and OS X."
fi

