#!/bin/bash
#filename:remove_duplicates.sh
#usage:find the duplicates and remove them
ls -lS --time-style=long-iso | awk '
