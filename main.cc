#include "thread.h"
#include "led-matrix.h"
#include "effect.h"
#include "Getdata.h"

#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


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

class ImageScroller : public RGBMatrixManipulator {
public:
  ImageScroller(RGBMatrix *m,std::string filename)
    : RGBMatrixManipulator(m), image_(NULL), horizontal_position_(0) {
	LoadPPM(filename);
  }

  // _very_ simplified. Can only read binary P6 PPM. Expects newlines in headers
  // Not really robust. Use at your own risk :)
  bool LoadPPM(std::string filename) {
    if (image_) {
      delete [] image_;
      image_ = NULL;
    }
    FILE *f = fopen((char*)filename.c_str(), "r");
    if (f == NULL) return false;
    char header_buf[256];
    const char *line = ReadLine(f, header_buf, sizeof(header_buf));
#define EXIT_WITH_MSG(m) { fprintf(stderr, "%s: %s |%s", (char*)filename.c_str(), m, line); \
      fclose(f); return false; }
    if (sscanf(line, "P6 ") == EOF)
      EXIT_WITH_MSG("Can only handle P6 as PPM type.");
    line = ReadLine(f, header_buf, sizeof(header_buf));
    if (!line || sscanf(line, "%d %d ", &width_, &height_) != 2)
      EXIT_WITH_MSG("Width/height expected");
    int value;
    line = ReadLine(f, header_buf, sizeof(header_buf));
    if (!line || sscanf(line, "%d ", &value) != 1 || value != 255)
      EXIT_WITH_MSG("Only 255 for maxval allowed.");
    const size_t pixel_count = width_ * height_;
    image_ = new Pixel [ pixel_count ];
    assert(sizeof(Pixel) == 3);   // we make that assumption.
    if (fread(image_, sizeof(Pixel), pixel_count, f) != pixel_count) {
      line = "";
      EXIT_WITH_MSG("Not enough pixels read.");
    }
#undef EXIT_WITH_MSG
    fclose(f);
    //fprintf(stderr, "Read image with %dx%d\n", width_, height_);
    horizontal_position_ = 0;
    return true;
  }

  void Run() {
  //  const int screen_height = matrix_->height();
  //  const int screen_width = matrix_->width();
    while (running_) {
      if (image_ == NULL) {
        usleep(100 * 1000);
        continue;
      }
      usleep(30 * 1000);
      for (int x = 0; x < 32; ++x) {
        for (int y = 0; y < 16; ++y) {
          const Pixel &p = getPixel((horizontal_position_ + x) % width_, y);
          // Display upside down on my desk. Lets flip :)
          int disp_x = /*screen_width -*/ x;
          int disp_y = /*screen_height -*/ y;
          matrix_->SetPixel(disp_x, disp_y, p.red, p.green, p.blue);
        }
      }
      ++horizontal_position_;
    }
  }

private:
  struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
  };

  // Read line, skip comments.
  char *ReadLine(FILE *f, char *buffer, size_t len) {
    char *result;
    do {
      result = fgets(buffer, len, f);
    } while (result != NULL && result[0] == '#');
    return result;
  }

  const Pixel &getPixel(int x, int y) {
    static Pixel dummy;
    if (x < 0 || x > width_ || y < 0 || y > height_) return dummy;
    return image_[x + width_ * y];
  }

  int width_;
  int height_;
  Pixel *image_;
  uint32_t horizontal_position_;
};

int main(int argc, char *argv[]) {
	int demo = 0;
	if (argc > 1) {
		demo = atoi(argv[1]);
	}
	//fprintf(stderr, "Using demo %d\n", demo);

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
//		image_gen = new ImageScroller(&m,"pixmap/star.ppm"); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Plasma(&m); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		delete data; data = new  GetData('m'); data->Start();
		image_gen=new StarField(&m); image_gen->Start(); sleep(60); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		delete data; data = new  GetData('f'); data->Start();
		image_gen = new ImageScroller(&m,"pixmap/question.ppm"); image_gen->Start(); sleep(30); delete image_gen;
		image_gen = new Clock(&m); image_gen->Start(); sleep(60); delete image_gen;
		image_gen = new ImageScroller(&m,"pixmap/champ.ppm"); image_gen->Start(); sleep(30); delete image_gen;
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
