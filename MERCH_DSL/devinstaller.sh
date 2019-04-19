#!/bin/sh

#Gets current version of java
JAVA_VER=$(java -version 2>&1 | sed -n ';s/.* version "\(.*\)\.\(.*\)\..*"/\1\2/p;'| cut -d' ' -f1)
echo version "$JAVA_VER"

#checks if correct version of java is installed
if [ "$JAVA_VER" -ge 16 ]; then
	echo correct java version 
else
	echo wrong java version
	sudo apt-get --assume-yes install default-jdk
fi

#install python version
sudo apt-get --assume-yes install python2.7 python-pip

#install virtualenv and set it up
if ! [ -x "$(command -v virtualenv)" ]; then
	echo 'Error: virtualenv is not installed.'
	sudo apt-get --assume-yes install virtualenv
fi

#setup virtual enviroment
virtualenv -p /usr/bin/python2.7 --distribute temp-python
. temp-python/bin/activate
pip install antlr4-python2-runtime
deactivate

pip install requests

cd /usr/local/lib

#installs the antlr java pack to /usr/local/lib
if [ "/usr/local/lib" = $PWD ]; then

	echo correct directory
	
	#checks if curl is installed
	if ! [ -x "$(command -v curl)" ]; then
  		echo 'Error: curl is not installed.'
		sudo apt-get --assume-yes install curl
	fi

	sudo curl -O https://www.antlr.org/download/antlr-4.7.1-complete.jar
	
else
	echo current directory is $PWD
fi

#creates permanent alias's 
echo  'export CLASSPATH=".:/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH"' >> ~/.bashrc 

echo  'alias antlr4='\''java -Xmx500M -cp "/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH" org.antlr.v4.Tool'\''' >> ~/.bashrc
 
echo  'alias grun='\''java org.antlr.v4.runtime.misc.TestRig'\''' >> ~/.bashrc 
