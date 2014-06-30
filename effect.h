#include "led-matrix.h"
#include "thread.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <unistd.h>
#include "font.h"
#include <string>
#include <fstream>

class RGBMatrixManipulator : public Thread {
	public:
		RGBMatrixManipulator(RGBMatrix *m) : running_(true), matrix_(m) {}
		virtual ~RGBMatrixManipulator() { running_ = false; }
	protected:
		volatile bool running_;  // TODO: use mutex, but this is good enough for now.
		RGBMatrix *const matrix_;
};


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


/////////// Function 

struct Pixel { uint8_t red; uint8_t green; uint8_t blue; };
void putTxt(RGBMatrix *,int,int,std::string,Pixel );
bool *prinTxt(std::string);


