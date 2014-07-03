#include "Getdata.h"
#include <stdlib.h>
#include <sys/wait.h>

void GetData::Run() {
	char argv[20];
	char cmd[20];


	switch (module)
	{
		case 'm': strcpy(cmd,"./scripts/meteo.py"); strcpy(argv,"meteo.py"); break;
		case 's': strcpy(cmd,"./scripts/song.py"); strcpy(argv,"song.py"); break;
		case 'f': strcpy(cmd,"./scripts/file.sh"); strcpy(argv,"file.sh"); break;
		case 'n': strcpy(cmd,"./scripts/news.py"); strcpy(argv,"news.py"); break;
		default:         strcpy(cmd,"./scripts/meteo.py"); strcpy(argv,"meteo.py"); break;
	}


	pid_t child_pid = fork();

	if (child_pid == 0 )
	{
		execl(cmd,argv,NULL);	
	}

	int ret;
	waitpid(-1,&ret,0);
//	system(cmd);
}
