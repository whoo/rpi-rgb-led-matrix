#!/usr/bin/env python3
# -*- coding: iso8859-1 -*-

from urllib import request
import json,random
from os import chdir

chdir('/home/Users/dominique/display16x32/dd/scripts');
accroche=['du fun avec','le plaisir d\'ecouter','du son dans la maison:','dansons avec','chanton avec']
url='http://wizz/mpd/run.php?cmd=currentsong'

data=request.urlopen(url)
val=json.loads(data.read().decode('utf-8'))



if "Artist" in val.keys():
	artist=val['Artist']
else:
	artist="illustre inconnu";

if "Title" in val.keys():
	titre=val['Title']
else:
	titre='heu ... je sais pas'	



str=accroche[random.randint(0,len(accroche)-1)] + " \"%s\" de %s"%(titre,artist)
str=str.replace('é','e')
str=str.replace('è','e')
str=str.replace('ê','e')
str=str.replace('à','a')

print (str)
f=open('../data/file','w',encoding='ISO-8859-1')
f.write(str)
f.close()


