#ifndef EFFECT_H
#define EFFECT_H


#include "led-matrix.h"
#include "thread.h"
#include "tools.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <assert.h>

#define MAXSTAR 20



class StarField:public RGBMatrixManipulator {
	public:
		StarField(RGBMatrix *m) : RGBMatrixManipulator(m) {}
		void Run();
};

class Fire:public RGBMatrixManipulator {
	public:
		Fire(RGBMatrix *m) : RGBMatrixManipulator(m) {}
		void Run();
};

class BinClock:public RGBMatrixManipulator {
        public:
                BinClock(RGBMatrix *m) : RGBMatrixManipulator(m) {}
                void Run();
};

class Clock:public RGBMatrixManipulator {
	public:
		Clock(RGBMatrix *m) : RGBMatrixManipulator(m) {}
                void Run();

};

class Table:public RGBMatrixManipulator {
        public:
                Table(RGBMatrix *m) : RGBMatrixManipulator(m) {}
                void Run();

};

class Plasma:public RGBMatrixManipulator {
        public:
                Plasma(RGBMatrix *m) : RGBMatrixManipulator(m) {}
                void Run();

};

class ImageScroller : public RGBMatrixManipulator {
	public:
		ImageScroller(RGBMatrix *m,std::string filename) : RGBMatrixManipulator(m), image_(NULL), horizontal_position_(0) 
		{ LoadPPM(filename); }
		void Run();
		bool LoadPPM(std::string);
	private:
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


#endif
