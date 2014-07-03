#ifndef TOOLS_H 
#define TOOLS_H

#include "thread.h"
#include "led-matrix.h"
#include <string.h>
#include <string>

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
bool *prinTxt(std::string txt);



#endif
