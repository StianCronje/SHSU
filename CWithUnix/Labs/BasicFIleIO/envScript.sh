#!/bin/bash
#The first line, 'shebang #!', indicates to use the bash shell
# means comment

echo "Welcome to COSC2327 executing on $HOSTNAME running $OSTYPE."
echo "Your user id is $USER in home directory $HOME."
echo "Your system is executing vesion $BASH_VERSION."
echo "Your current path is $PATH, present working directory is $PWD."
echo "Your previous working directory was $OLDPWD."
echo "The previous ID of the interpreter $PPID."
sleep 2
echo "After a 2 second nap, you have been running $SECONDS seconds."
exit