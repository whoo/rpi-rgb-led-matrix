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


class Tunnel:public RGBMatrixManipulator {
        public:
                Tunnel(RGBMatrix *m) : RGBMatrixManipulator(m) {}
                void Run();
};



#endif
