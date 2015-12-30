#define _XOPEN_SOURCE_EXTENDED 

#include "pasa.h"



int framesPerSecond = 40;
double upperFrequency = 3520.0; // A7
double gain = 4.0;


// hanning window.
float windowFunction(int n, int N)
{       
        return 0.5f * (1.0f - cosf(2.0f * M_PI * n / (N - 1.0f)));
}

void calculateBars(fftw_complex* fft, int fftSize, int* bars, int numBars)
{                               
        // todo: use the float-point value and implement proper interpolation.
        double barWidthD = upperFrequency / (framesPerSecond * numBars);
        int barWidth = (int)ceil(barWidthD);
                                
        double scale = 2.0 / fftSize * gain;

        // interpolate bars. 
        int i = 0;              
        for(int bar = 0; bar < numBars; bar++)
        {
                // get average.
                double power = 0.0;
                for(int j = 0; j < barWidth && i < fftSize; i++, j++)
                {
                        double re = fft[i][0] * scale;
                        double im = fft[i][1] * scale;
                        power += re * re + im * im; // abs(c)
                } 
                power *= (1.0 / barWidth); // average.
                if(power < 1e-15) power = 1e-15; // prevent overflows.
        
                // compute decibels.
                int dB = 16 + (int)(10.0 * log10(power));
                if(dB > 16) dB = 16;
                if(dB < 0) dB = 0;
        
                // set bar.
                bars[bar] = dB;
        }
}   



void Spectrum::Run()
{
	const int width = matrix_->width();
	const int height = matrix_->height();
	static const pa_sample_spec ss = { PA_SAMPLE_S16LE ,44100,2};
	int error;


	pa_simple *s = pa_simple_new(NULL, "pasa", PA_STREAM_RECORD, NULL , "record",&ss, NULL, NULL, &error);
	if (!s) fprintf(stderr,"Error %s",pa_strerror(error));

	const int size = ss.rate / 40;
	float window[size];
	float buffer[ss.channels * size];

	for(int n = 0; n < size; n++)
                window[n] = windowFunction(n, size);

//        double *in = (double*)fftw_malloc(sizeof(double) * size);
//        fftw_complex *out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * size);
//        fftw_plan plan = fftw_plan_dft_r2c_1d(size, in, out, FFTW_MEASURE);


	while(running_)
	{
		int barsL[32];
		int barsR[16];
		int buff[ss.channels * size];
		int link=0;

		CLEARSCR;
		if ( pa_simple_read(s, buff, sizeof(buff), &error) < 0)
		{
			fprintf(stderr,"started %s\n",pa_strerror(error));
			pa_simple_free(s);
			return;
		}

		int maxval=0;
		int maxval2=0;

		for (int a=0;a<size;a+=2)
		{
			maxval=(fabs(buff[a])>maxval)?fabs(buff[a]):maxval;
			maxval2=(fabs(buff[a+1])>maxval2)?fabs(buff[a+1]):maxval2;

			if ((a/34) > link )
			{
				barsL[link]=maxval%16;
				barsL[32-link]=maxval2%16;		
				link=a/34;
				maxval=maxval2=0;
			}

		}



		for (int a=0;a<32;a++)
		{
//			fprintf(stderr,"%d ",barsL[a]);
			for (int b=0;b<barsL[a];b++)
				matrix_->SetPixel(a,16-b,128,255,0);
		}
//		fprintf(stderr,"\n");

			usleep(1000*90);
	}

	pa_simple_free(s);

	return ;
}
