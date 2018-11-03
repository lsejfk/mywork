#!/bin/bash
#filename:password.sh
echo -e "Enter password:"
stty -echo
read password
echo
stty echo
echo Password read.
