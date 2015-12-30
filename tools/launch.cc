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

		setenv("HOME","/root",1);
		setenv("USER","root",1);
		setenv("USERNAME","root",1);
		setenv("LOGNAME","root",1);
	
		char cmd[]="./led-matrix";
		char argv[]="./led-matrix";
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		execl(cmd,argv,NULL);
	}
	else 
	{
		std::cout<<"Content-type: text/plain\n\n";
		std::cout<<"Started\n";
	}

	return 0;
}
