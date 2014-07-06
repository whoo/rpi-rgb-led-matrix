#include "thread.h"
#include "led-matrix.h"
#include "effect.h"
#include "effect2.h"
#include "Getdata.h"

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
class RotatingBlockGenerator : public RGBMatrixManipulator {
	public:
		RotatingBlockGenerator(RGBMatrix *m) : RGBMatrixManipulator(m) {}

		uint8_t scale_col(int val, int lo, int hi) {
			if (val < lo) return 0;
			if (val > hi) return 255;
			return 255 * (val - lo) / (hi - lo);
		}

		void Run() {
			const int cent_x = matrix_->width() / 2;
			const int cent_y = matrix_->height() / 2;

			// The square to rotate (inner square + black frame) needs to cover the
			// whole area, even if diagnoal.
			const int rotate_square = min(matrix_->width(), matrix_->height()) * 1.41;
			const int min_rotate = cent_x - rotate_square / 2;
			const int max_rotate = cent_x + rotate_square / 2;

			// The square to display is within the visible area.
			const int display_square = min(matrix_->width(), matrix_->height()) * 0.7;
			const int min_display = cent_x - display_square / 2;
			const int max_display = cent_x + display_square / 2;

			const float deg_to_rad = 2 * 3.14159265 / 360;
			int rotation = 0;
			while (running_) {
				++rotation;
				usleep(15 * 1000);
				rotation %= 360;
				for (int x = min_rotate; x < max_rotate; ++x) {
					for (int y = min_rotate; y < max_rotate; ++y) {
						float disp_x, disp_y;
						Rotate(x - cent_x, y - cent_y,
								deg_to_rad * rotation, &disp_x, &disp_y);
						if (x >= min_display && x < max_display &&
								y >= min_display && y < max_display) { // within display square
							matrix_->SetPixel(disp_x + cent_x, disp_y + cent_y,
									scale_col(x, min_display, max_display),
									255 - scale_col(y, min_display, max_display),
									scale_col(y, min_display, max_display));
						} else {
							// black frame.
							matrix_->SetPixel(disp_x + cent_x, disp_y + cent_y, 0, 0, 0);
						}
					}
				}
			}
		}

	private:
		void Rotate(int x, int y, float angle,
				float *new_x, float *new_y) {
			*new_x = x * cosf(angle) - y * sinf(angle);
			*new_y = x * sinf(angle) + y * cosf(angle);
		}
};


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

		GetData *data = new  GetData('s'); data->Start();
		//	image_gen = new ImageScroller(&m,"pixmap/star.ppm"); image_gen->Start(); sleep(30); delete image_gen;
		//	image_gen = new ImageScroller(&m,"pixmap/champ.ppm"); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new RotoStar(&m); image_gen->Start();  sleep(30); delete image_gen;
		image_gen = new Plasma(&m); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		delete data; data = new  GetData('m'); data->Start();
		image_gen=new StarField(&m); image_gen->Start(); sleep(60); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		delete data; data = new  GetData('f'); data->Start();
		image_gen = new ImageScroller(&m,"pixmap/question.ppm"); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		delete data;  data = new  GetData('n'); data->Start();
		image_gen = new RotoZoom(&m,"pixmap/champ.ppm"); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(360); delete image_gen;
		delete data;
		image_gen=new RotatingBlockGenerator(&m); image_gen->Start(); sleep(30); delete image_gen;
		m.ClearScreen(); m.UpdateScreen(); sleep(180);
	}

	delete updater;
	// Final thing before exit: clear screen and update once, so that
	// we don't have random pixels burn
	m.ClearScreen();
	m.UpdateScreen();

	return 0;
}
