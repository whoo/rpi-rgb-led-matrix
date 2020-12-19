#include <stdio.h>
#include <curl/curl.h>
#include <json.h>
#include <string>
#include <iostream>
#include "Tools.h"

#define APPID "NomoreValide"
#define URL   "http://api.openweathermap.org/data/2.5/group?id=6077243,3033123,934154&units=metric&lang=fr&APPID="APPID




int main(int argc,char **argv)
{



	// getCURL
	std::string response=getUrl(URL);	

	// PARSE Json
	if (response.size())
	{
		json_object *new_obj = json_tokener_parse(response.c_str());
		json_object *list  = json_object_object_get(new_obj,"list");

		int max=json_object_get_int(json_object_object_get(new_obj,"cnt"));

		for (int a=0;a<max;a++)
		{
			json_object *ville = json_object_array_get_idx(list,a);
			std::string ville_name= json_object_get_string(json_object_object_get(ville,"name"));

			// list:[ {weather:[ description],name,main{temp,temp_min,temp_max} }  ]
			std::string description= json_object_get_string(
							json_object_object_get( 
								json_object_array_get_idx(json_object_object_get(ville,"weather"),0),"description"));

			int temp = json_object_get_int( json_object_object_get(json_object_object_get(ville,"main"),"temp"));
			int temp_min = json_object_get_int( json_object_object_get(json_object_object_get(ville,"main"),"temp_min"));
			int temp_max = json_object_get_int( json_object_object_get(json_object_object_get(ville,"main"),"temp_max"));

			ville_name=majuscule(ville_name);
			description=majuscule(description);

			printf("%s %s %d (%d %d)\n",ville_name.c_str(),description.c_str(),temp,temp_min,temp_max);
		}
	}
	return 0;
}
