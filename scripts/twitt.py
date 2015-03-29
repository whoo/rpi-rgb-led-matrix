#!/usr/bin/env python3
# -*- coding: utf-8 -*-



import json
import urllib
from urllib import request
from urllib import parse
from os import chdir

chdir('/home/Users/dominique/display16x32/dd/scripts');


KEY="TGxnMDBYRWdRVzVFTEdzWlRBNjJ0R0h0djpCa1ZLN1RpWmpQQjVCdmlrZjNIYmwwVlNhdnpkdUZ2OGhhakMyZjJaWkc2NkZZSmdwaw=="


req= request.Request("https://api.twitter.com/oauth2/token")
req.add_header("Content-Type","application/x-www-form-urlencoded;charset=utf-8")
req.add_header("Authorization","Basic %s"%(KEY))
data= urllib.parse.urlencode({"grant_type":"client_credentials"}).encode('utf-8')
val=json.loads(urllib.request.urlopen(req,data).read().decode('utf-8'))

#print(val['access_token']);

req=request.Request("https://api.twitter.com//1.1/statuses/user_timeline.json?count=10&screen_name=clicdemoins");
req.add_header("Content-Type","application/x-www-form-urlencoded;charset=utf-8")
req.add_header("Authorization","Bearer %s"%(val['access_token']))
val=json.loads(urllib.request.urlopen(req).read().decode('utf-8'))



str=""
for v,a in enumerate(val):
	str+="%s\n"%(a['text'])




# print(item[1][3].text)
str=str.replace('é','e')
str=str.replace('è','e')
str=str.replace('ê','e')
str=str.replace('à','a')
str=str.replace('ô','o')
str=str.replace('’','\'')

f=open('../data/file','w')
f.write(str)
f.close()


