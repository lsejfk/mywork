#!/bin/bash
#filename:print.sh
echo Welcome to bash
echo "Welcome to bash;"
echo 'Welcome to bash;'
bash=hello
echo 'Welcome to ${bash}'
echo "Welcome to ${bash}"
echo
echo -e "1\t2\t3\n"
echo -e '1\t2\t'
echo -e "\e[1;32m This \e[1;31m is \e[1;33m a \e[1;34m color \e[1;35m text \e[0m"
echo -e "\e[1;41m This \e[1;42m is \e[1;43m a \e[1;44m background \e[1;45m color \e[0m"
