#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from urllib import request
import json
from os import chdir

chdir('/home/Users/dominique/display16x32/dd/scripts');
url='http://api.openweathermap.org/data/2.5/weather?q=Montreal,ca&lang=fr&units=metric';


def  getweather(url):
		data=request.Request(url)
		data.add_header('User-Agent','Mozilla/4.0')
		data=request.urlopen(data,timeout=60)
		valall=json.loads(data.read().decode('utf-8'))
		str=""
		for val in valall['list']:
			ville=val['name']
			temp=val['main']['temp']
			hum=val['main']['humidity']
			weather=val['weather'][0]['description']
			temp_min=val['main']['temp_min']
			temp_max=val['main']['temp_max']
	
			str=str+"%s: %dC %s (min %d max %d)\n"%(ville,temp,weather,temp_min,temp_max)

		str=str.replace('é','e')
		str=str.replace('è','e')
		str=str.replace('ê','e')
		str=str.replace('à','a')
		return str


str={}
#str[0]=getweather("http://api.openweathermap.org/data/2.5/weather?q=Montreal,ca&lang=fr&units=metric")
#str[1]=getweather("http://api.openweathermap.org/data/2.5/weather?q=Besancon,fr&lang=fr&units=metric")
#str[2]=getweather("http://api.openweathermap.org/data/2.5/weather?q=Port+Louis,mu&lang=fr&units=metric")

str[0]=getweather("http://api.openweathermap.org/data/2.5/group?id=6077243,3033123,934154&units=metric&lang=fr")



f=open('../data/file','w',encoding='ISO-8859-1')
f.write(str[0]);
#f.write(str[1]);
#f.write(str[2]);
f.close()


