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
elif [ -f /etc/debian_version ] ; then
	DIST='Debian'
elif [ "`uname`" == 'Darwin' ] ; then
	DIST='Darwin'
fi

if   [ "$DIST" == 'Fedora' ] ; then
	yum -y install gcc-c++ make cmake swig mesa-libGLU-devel readline-devel\
		DevIL-ILUT-devel libXrandr-devel freetype-devel\
		openal-soft-devel libvorbis-devel libpng-devel libXi-devel
elif [ "$DIST" == 'Ubuntu' ] ; then
	apt-get -y install build-essential cmake swig libglu1-mesa-dev\
		libreadline-dev libdevil-dev libxrandr-dev libfreetype6-dev\
		joystick libopenal-dev libvorbis-dev libpng12-dev ncurses-dev\
		libxi-dev
elif [ "$DIST" == 'Debian' ] ; then
	apt-get -y install build-essential cmake swig libglu1-mesa-dev\
		libreadline-dev libdevil-dev libxrandr-dev libfreetype6-dev\
		joystick libopenal-dev libvorbis-dev libpng12-dev\
		libncurses5-dev libxi-dev xorg-dev libglu1-mesa-dev
elif [ "$DIST" == 'Darwin' ] ; then
	if [ "`which make`" == "" ] ; then
		echo "The Xcode command line tools are not installed."
		echo "Use the Downloads section of the Xcode preferences to install them."
		exit 1
	fi

	SWIG_INSTALLED=false
	if [ "`which brew`" != "" ] ; then
		if [ "`brew list | grep swig`" == "" ] ; then
			su $SUDO_USER -c "brew install swig"
		fi
		SWIG_INSTALLED=true
	elif [ "`which port`" != "" ] ; then
		if [ "`port installed swig-lua | grep currently`" == "" ] ; then
			port install swig-lua
		fi
		SWIG_INSTALLED=true
	fi
	if [ $SWIG_INSTALLED != true ] ; then
		echo "Couldn't install swig because neither Homebrew nor MacPorts was available."
		echo "Please either download and install from:"
		echo "	<http://mxcl.github.com/homebrew/>"
		echo "		or"
		echo "	<http://macports.org>"
		exit 1
	fi

	if [ ! -d /System/Library/Extensions/360Controller.kext ] ; then
		hdiutil attach ../Tools/Mac360/360ControllerInstall.0.11.dmg
		installer -target / -pkg /Volumes/360ControllerInstall/Install360Controller.pkg
		hdiutil detach /Volumes/360ControllerInstall
		echo "You should restart your machine to get access to the 360 Controller."
	fi
else
	echo "This is not a recognized Linux or UNIX distribution."
	echo "Currently we support Fedora, Ubuntu, Debian, and OS X."
fi

