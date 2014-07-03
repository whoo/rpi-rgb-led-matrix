#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

int main(int argc,char **argv)
{

chdir("/home/Users/dominique/display16x32/dd");
	pid_t pid=fork();

	if (pid==0)
	{
	char cmd[]="./led-matrix";
	char argv[]="./led-matrix";
	execl(cmd,argv,NULL);

	}
	else 
	{
		std::cout<<"Child started";
	}


}
