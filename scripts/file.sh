#!/bin/bash

cd $(dirname $0)
/usr/games/fortune -a fr/humoristes | sed -e ':a;N;$!ba;s/\n/ /g' -e 's/é/e/g' -e 's/è/e/g' -e 's/ç/c/g' -e 's/ê/e/g' -e 's/É/e/g' -e 's/\n/ /g' > ../data/file
