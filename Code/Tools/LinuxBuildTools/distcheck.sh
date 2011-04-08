# returns whether we're on Fedora or Ubuntu

if   [ -f /etc/fedora-release ] ; then
	echo 'Fedora'
elif [ -f /etc/lsb-release ] ; then
	echo `cat /etc/lsb-release | grep DISTRIB_ID | sed s/.*=//`
fi
