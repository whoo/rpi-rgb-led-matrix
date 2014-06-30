#!/bin/bash

cd /home/Users/dominique/display16x32/dd/scripts
/usr/games/fortune -a fr/humoristes | sed -e 's/é/e/g' -e 's/è/e/g' -e 's/ç/c/g' -e 's/ê/e/g' -e 's/É/e/g' |tee ../data/file
