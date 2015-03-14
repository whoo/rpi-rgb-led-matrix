#ifndef EFFECT2_H
#define EFFECT2_H


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


class RotoZoom:public RGBMatrixManipulator {
        public:
                RotoZoom(RGBMatrix *m,std::string filename) : RGBMatrixManipulator(m) { image=LoadPPM(filename); }
                void Run();
		
	private:
		Pixel *image;
};


class RotoStar:public RGBMatrixManipulator {
	public:
		RotoStar(RGBMatrix *m) : RGBMatrixManipulator(m) {}
		void Run();

};

class RotoZoom2:public RGBMatrixManipulator {
	public:
		RotoZoom2(RGBMatrix *m,std::string filename) : RGBMatrixManipulator(m) { image=LoadPPM(filename); }
		void Run();
	private:
		Pixel *image;
};

#endif
