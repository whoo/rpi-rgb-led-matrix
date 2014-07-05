#include "effect2.h"
#define PI_2 2*3.1415926/360

void RotoZoom::Run() {
//	Pixel *image;
	int w= matrix_->width();
	int h= matrix_->height();

//	image=	LoadPPM("pixmap/champ.ppm");
/*
	for (int a=0;a<64;a++)
	{
		image[a].red=(a%8)<<5;
		image[a].green=(a/8)<<5;
		image[a].blue=(255-(a%8))<<5;
	}
*/

	int off=0;

	float costb[360];
	float sintb[360];

	for (int a=0;a<360;a++)
	{
		costb[a]=cos(a*PI_2);
		sintb[a]=sin(a*PI_2);
	}

	int xx,yy;
	while(running_)
	{
		off+=1;
		off%=360;	
		usleep(1000*10);



		for(int x = 0; x < w; x++)
		{
			for(int y = 0; y < h; y++)
			{
				Pixel d;
				xx=(costb[off]*(x)-sintb[off]*(y-8))*abs(off-180)*4/360;
				yy=(sintb[off]*(x)+costb[off]*(y-8))*abs(off-180)*4/360;
				d=image[((128+xx)%16+((128+yy)%16)*16)%(16*16) ];
				matrix_->SetPixel(x,y,d.red,d.green,d.blue);
			}

		}

	}
}
