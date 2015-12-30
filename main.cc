#include "thread.h"
#include "led-matrix.h"
#include "effect.h"
#include "effect2.h"
#include "Getdata.h"
#include "pasa.h"

#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fcntl.h>
#include <sys/file.h>


using std::min;
using std::max;


class DisplayUpdater : public RGBMatrixManipulator {
	public:
		DisplayUpdater(RGBMatrix *m) : RGBMatrixManipulator(m) {}

		void Run() {
			while (running_) {
				matrix_->UpdateScreen();
			}
		}
};

// -- The following are demo image generators.



// Simple class that generates a rotating block on the screen.

int main(int argc, char *argv[]) {
	srand (time(NULL));

	int fd = open("/tmp/led", 'a');
	int ret = flock(fd,LOCK_EX|LOCK_NB);
	pid_t pid=getpid();

	dprintf(fd,"%d",pid);

	if (ret!=0) 
	{
		fprintf(stderr,"Error: already running");
		exit(1);
	}


	GPIO io;
	if (!io.Init())
		return 1;

	RGBMatrix m(&io);
	RGBMatrixManipulator *image_gen = NULL;

	/*  if (image_gen == NULL) return 1; */

	RGBMatrixManipulator *updater = new DisplayUpdater(&m);
	updater->Start(10);  // high priority

	while (1)
	{

		image_gen = new Spectrum(&m); image_gen->Start(); sleep(60); delete image_gen;

		GetData *data = new  GetData('s'); data->Start();


		image_gen = new RotoZoom2(&m,randomfile()); image_gen->Start(); sleep(30); delete image_gen;


		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		image_gen = new Plasma(&m); image_gen->Start(); sleep(30); delete image_gen;



		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		image_gen=new RotoStar(&m); image_gen->Start(); sleep(30); delete image_gen;

		delete data; data = new  GetData('m'); data->Start();
		image_gen=new StarField(&m); image_gen->Start(); sleep(60); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;

		delete data; data = new  GetData('f'); data->Start();
		image_gen = new RotoZoom(&m,randomfile()); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;

		delete data;  data = new  GetData('n'); data->Start();
		image_gen = new RotoZoom2(&m,randomfile()); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(360); delete image_gen;

		delete data; data = new  GetData('t'); data->Start();
		image_gen=new RotoStar(&m); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(360); delete image_gen;

		delete data;
		m.ClearScreen(); m.UpdateScreen(); sleep(180);
	}

	delete updater;
	// Final thing before exit: clear screen and update once, so that
	// we don't have random pixels burn
	m.ClearScreen();
	m.UpdateScreen();

	return 0;
}
