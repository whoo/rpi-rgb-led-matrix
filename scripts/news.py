#!/usr/bin/env python3


from lxml import etree
from urllib import request
from os import chdir

chdir('/home/Users/dominique/display16x32/dd/scripts');


url="http://www.france24.com/fr/actualites/rss/"
url="http://www.france24.com/fr/europe/rss/"
url="http://rss.lapresse.ca/179.xml"
url="https://news.google.com/news/feeds?pz=1&cf=all&ned=fr&hl=fr&topic=t&output=rss"
url="https://news.google.com/news/feeds?pz=1&cf=all&ned=fr&hl=fr&output=rss"
xml=request.urlopen(url).read();
root = etree.fromstring(xml)

str=""
for item in enumerate(root.xpath("//item/title")):
	str+="%s\n"%(item[1].text)
# print(item[1][3].text)
str=str.replace('é','e')
str=str.replace('è','e')
str=str.replace('ê','e')
str=str.replace('à','a')
str=str.replace('ô','o')
str=str.replace('’','\'')

f=open('../data/file','w',encoding='ISO-8859-1')
f.write(str)
f.close()


