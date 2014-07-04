#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <iostream>

int main(int argc,char **argv)
{

	char pid[6];
	FILE *file =fopen("/tmp/led","r");

if (file)
	{
	chdir("/home/Users/dominique/display16x32/dd");

	std::cout<<"Content-type: text/plain\n\n";
	std::cout<<"kill\n"<<atoi(pid);

	fgets(pid,sizeof(pid),file);
	fprintf(stderr,"%d",atoi(pid));
	kill(atoi(pid),9);
	system("./clear");
	unlink("/tmp/led");
}
	
	return 0;
}
