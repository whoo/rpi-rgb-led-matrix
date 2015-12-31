#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tools.h"
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

int main(int argc,char **argv)
{

	std::string url[]=
	{
		"http://www.france24.com/fr/actualites/rss",
		"http://www.france24.com/fr/europe/rss/",
		"http://rss.lapresse.ca/179.xml",
		"https://news.google.com/news/feeds?pz=1&cf=all&ned=fr&hl=fr&topic=t&output=rss",
		"https://news.google.com/news/feeds?pz=1&cf=all&ned=fr&hl=fr&output=rss"
	};

	srand (time(NULL));
	std::string news=url[(int) (5.0 * (rand() / (RAND_MAX + 1.0)))];
	//std::cout<<news<<std::endl;


	std::string xml = getUrl(news);
	//channel->item->title
	//channel->item->description
//	std::cout<<xml<<std::endl;

	xmlInitParser();
	xmlDocPtr dd= xmlParseMemory(xml.c_str(),xml.size());

	xmlXPathContextPtr xpathCtx = xmlXPathNewContext(dd);
	std::string path="//item/title";
	xmlXPathObjectPtr xpathObj=xmlXPathEvalExpression(BAD_CAST path.c_str(), xpathCtx);

	for (int i=0; i < xpathObj->nodesetval->nodeNr; i++) {
		xmlChar *keyword = xmlNodeListGetString(dd, xpathObj->nodesetval->nodeTab[i]->xmlChildrenNode, 1);

		std::string txt;
		txt.append((const char*)keyword,strlen((const char *)keyword));
		printf("%s\n", majuscule(txt).c_str());
				xmlFree(keyword);

	}


	xmlCleanupParser();
	exit(0);
}
