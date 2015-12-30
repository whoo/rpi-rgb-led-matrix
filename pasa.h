#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <signal.h>
#include <locale.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <fftw3.h>

class Spectrum:public RGBMatrixManipulator {
        public:
               Spectrum(RGBMatrix *m) : RGBMatrixManipulator(m) {}
                void Run();
//	private:
//		void calculateBars(fftw_complex* fft, int fftSize, int* bars, int numBars);

};
