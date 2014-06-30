#include "Getdata.h"


void GetData::Run() {
	char argv[20];
	char cmd[20];

	switch (module)
	{
	case 'm': strcpy(cmd,"./scripts/meteo.py"); strcpy(argv,"meteo.py"); break;
        case 's': strcpy(cmd,"./scripts/song.py"); strcpy(argv,"song.py"); break;
        case 'f': strcpy(cmd,"./scripts/file.sh"); strcpy(argv,"file.sh"); break;
	default:         strcpy(cmd,"./scripts/meteo.py"); strcpy(argv,"meteo.py"); break;
	}

	fprintf(stderr,"GetData %c\n",module);
	if (!fork())
	{
		printf("%d\n",execl(cmd,argv,NULL));
	}
}
