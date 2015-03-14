#include "effect2.h"
#define PI_2 2*3.1415926/360
#define MAXSTAR 20
#include "assert.h"

void RotoZoom::Run() {
	int w= matrix_->width();
	int h= matrix_->height();
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

void RotoZoom2::Run() {
	int w= matrix_->width();
	int h= matrix_->height();
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

		for(int x = 0; x < w/2; x++)
		{
			for(int y = 0; y < h; y++)
			{
				Pixel d;
				xx=(costb[off]*(x)-sintb[off]*(y-8))*abs(off-180)*4/360;
				yy=(sintb[off]*(x)+costb[off]*(y-8))*abs(off-180)*4/360;
				d=image[((128+xx)%16+((128+yy)%16)*16)%(16*16) ];
				matrix_->SetPixel(x,y,d.red,d.green,d.blue);
				matrix_->SetPixel(32-x,16-y,d.red,d.green,d.blue);
			}

		}

	}
}



void RotoStar::Run() {
	const int width = matrix_->width();
	const int height = matrix_->height();
	uint32_t count = 0;
	int x=0;
	int y=0;
	int a=0;

	int star[MAXSTAR*2];
	int off=0;

	for (a=0;a<MAXSTAR;a++)
	{
		star[a]=rand()%16;
		star[a+MAXSTAR]=rand()%360;
	}

	while (running_) {
		usleep(50000);
		CLEARSCR;
		off=(off+1)%255;
		for (a=0;a<MAXSTAR;a++)
		{
			x=16+cos(star[a+MAXSTAR]*PI_2)*star[a];
			y=8+sin(star[a+MAXSTAR]*PI_2)*star[a];

			star[a+MAXSTAR]=(star[a+MAXSTAR]+10)%360;
			star[a]+=1;
			if (x>width or x<0 or y>height or y<0) {
				star[a]=0;
				star[a+MAXSTAR]=rand()%360;
			}
			else
			{
				matrix_->SetPixel(x,y,star[a]<<4,(star[a]+off)<<3,255-(star[a]<<2));
			}
		}

	}

};
