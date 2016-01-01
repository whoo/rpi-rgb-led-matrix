#ifndef TOOLS_H 
#define TOOLS_H

#include "thread.h"
#include "led-matrix.h"
#include <string.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>

#define CLEARSCR        for (int xe = 0; xe < width; ++xe) for (int ye = 0; ye < height; ++ye) { matrix_->SetPixel(xe,ye, 0,0,0); }


class RGBMatrixManipulator : public Thread {
        public:
                RGBMatrixManipulator(RGBMatrix *m) : running_(true), matrix_(m) {}
                virtual ~RGBMatrixManipulator() { running_ = false; }
        protected:
                volatile bool running_;  // TODO: use mutex, but this is good enough for now.
                RGBMatrix *const matrix_;
};


struct Pixel { uint8_t red; uint8_t green; uint8_t blue; };

void putTxt(RGBMatrix *,int,int,std::string,Pixel);
bool *prinTxt(std::string);
Pixel *LoadPPM(std::string); 
char *ReadLine(FILE *, char *, size_t ) ;
std::string randomfile();

class ImgPPM {

	public:
		ImgPPM(std::string);
		~ImgPPM() { delete image;}
		int width;
		int height;
		Pixel *image;
};

class DisplayUpdater : public RGBMatrixManipulator {
	public:
		DisplayUpdater(RGBMatrix *m) : RGBMatrixManipulator(m) {}

		void Run() {
			while (running_) {
				matrix_->UpdateScreen();
			}
		}
};



#endif
