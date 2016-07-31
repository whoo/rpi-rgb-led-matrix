#include <string>
#include <iconv.h>
#include <vector>
#include <curl/curl.h>
///////////////////////////////////////////////////////////
std::string utf8toiso(std::string );
std::string convertirChaineSansAccent(std::string ) ;
std::string majuscule(std::string );
size_t write_to_string(void *, size_t , size_t , void *);
std::string getUrl(std::string);
	
