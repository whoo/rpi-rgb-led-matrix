#include "Tools.h"

std::string utf8toiso(std::string chaine)
{
	iconv_t conv = ::iconv_open("ISO8859-15","UTF-8");

	// CONVERT string to char *
	std::vector<char> in_buf(chaine.begin(), chaine.end());
	char* src_ptr = &in_buf[0];
	size_t src_size = chaine.size();

	std::vector<char> buf(1024);
	std::string dst;

	// point sur le buffer
	char* dst_ptr = &buf[0];
	size_t dst_size = buf.size();


	//	size_t res = ::iconv(conv, &src_ptr, &src_size, &dst_ptr, &dst_size);
	while (0 < src_size )
	{
		std::fill (buf.begin(),buf.end(),0);
		size_t res = ::iconv(conv, &src_ptr, &src_size, &dst_ptr, &dst_size);

		dst.append(&buf[0],buf.size()-dst_size);
		if (res == (size_t)-1)
		{
			printf("Error convert [%s] %ld next string [%s]\n",dst.c_str(),dst.size(),src_ptr);
			src_ptr++;
			src_size--;
			dst_ptr = &buf[0];
			dst_size = buf.size();
			dst.append(" ");
		}

	}
	//	dst.append(&buf[0],dst_size);

	iconv_close(conv);
	return dst;

}

std::string convertirChaineSansAccent(std::string chaine) 
{
	// Déclaration de variables
	std::string accent = utf8toiso("éèêëÉàâÀçôöîïû");
	std::string sansAccent ="EEEEEAAACOOIIU";

	chaine=utf8toiso(chaine);
	for (int a=0;a<chaine.length();a++)
	{
		for (int b=0;accent[b]!=0;b++)
			if (chaine[a]==accent[b]) 
			{
				chaine[a]=sansAccent[b];
				continue;
			} else chaine[a]=toupper(chaine[a]);

	}

	return chaine;
}

std::string majuscule(std::string chaine)
{
	chaine= (convertirChaineSansAccent(chaine));
	return chaine;
}

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream)
{
	          ((std::string*)stream)->append((char*)ptr, 0, size*count);
		              return size*count;
}

std::string getUrl(std::string url)
{
	CURL *curl;
	CURLcode res;

	std::string response;
	curl = curl_easy_init();
	if (curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		return response;
	}

	return "";
}
