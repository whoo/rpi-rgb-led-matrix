#!/bin/bash 


function DDisHere {

	IP=192.168.2.31
	ping -c2 -i1 $IP  2>&1 | grep  "ttl" &>/dev/null
	res=$?
	echo $res
}


while /bin/true
do


pid=`pgrep led-matrix`x
a=$(DDisHere)
date=$(date +%-H)

if [ $a = 0 ]
then
a=$(DDisHere)
fi

if [ $a = 1 -a $pid != "x" ]
then
pkill -2 led-matrix
fi

if [ $a = 0 -a $pid = "x" -a $date -gt 7 ] 
then
echo "Start"
./led-matrix &
fi

sleep 5;
done

