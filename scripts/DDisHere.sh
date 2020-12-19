#!/bin/bash

IP=192.168.2.31
timeout 0.5s ping -c1 -i1 $IP  >&1 | grep icmp &>/dev/null
res=$?

echo $res

