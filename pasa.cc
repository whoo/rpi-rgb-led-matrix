#define _XOPEN_SOURCE_EXTENDED 

#include "pasa.h"



int framesPerSecond = 40;
double upperFrequency = 3520.0; // A7
double gain = 4.0;


// hanning window.
float windowFunction(int n, int N)
{       
        return (float) 0.5f * (1.0f - cosf(2.0f * M_PI * n / (N - 1.0f)));
}

void calculateBars(fftw_complex* fft, int fftSize, int* bars, int numBars)
{                               
        // todo: use the float-point value and implement proper interpolation.
        double barWidthD = upperFrequency / (framesPerSecond * numBars);
        int barWidth = (int)ceil(barWidthD);
                                
        double scale = 3.0 / fftSize * 50;

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
	static const pa_sample_spec ss = { PA_SAMPLE_FLOAT32LE ,44100,2};
	int error;


	pa_simple *s = pa_simple_new(NULL, "pasa", PA_STREAM_RECORD, NULL , "record",&ss, NULL, NULL, &error);
	if (!s) fprintf(stderr,"Error %s",pa_strerror(error));

	const int size = ss.rate / 40;
	float window[size];
	float buffer[ss.channels * size];

	for(int n = 0; n < size; n++)
                window[n] = windowFunction(n, size);

        double *in = (double*)fftw_malloc(sizeof(double) * size);
        fftw_complex *out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * size);
        fftw_plan plan = fftw_plan_dft_r2c_1d(size, in, out, FFTW_MEASURE);


	while(running_)
	{
		int barsL[32];
		int barsR[16];
		int buff[ss.channels * size];
		int link=0;


		pa_simple_drain(s,&error);
		CLEARSCR;
		if ( pa_simple_read(s, buffer, sizeof(buffer), &error) < 0)
		{
			fprintf(stderr,"started %s\n",pa_strerror(error));
			pa_simple_free(s);
			return;
		}

		

		//fprintf(stderr,"sample %f\n ",buffer[2*2]);
		for(int i = 0; i < size; i++) in[i] = (double)(window[i] * buffer[i * 2]);
		//fprintf(stderr,"sample %f\n ",in[2]);
                fftw_execute(plan);
		calculateBars(out,size,barsL,16);
		//fprintf(stderr,"sample %f\n ",buffer[2*2]);
		for(int i = 0; i < size; i++) in[i] = (double)(window[i] * buffer[i * 2+1]);
		//fprintf(stderr,"sample %f\n ",in[2]);
                fftw_execute(plan);
		calculateBars(out,size,barsR,16);





		for (int a=0;a<16;a++)
		{
//			fprintf(stderr,"%d ",barsL[a]);
			for (int b=0;b<barsL[a];b++) matrix_->SetPixel(a,16-b,128, (b<5)?255:0,0);
			for (int b=0;b<barsR[a];b++) matrix_->SetPixel(31-a,16-b,128,(b<5)?255:0,0);
		}
//		fprintf(stderr,"\n");

		usleep(1000*40);
	}

	pa_simple_free(s);

	return ;
}
