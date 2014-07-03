#include "effect2.h"

void Tunnel::Run() {
	Pixel image[64];
	int w= matrix_->width();
	int h= matrix_->height();


	int angle[16*32];
	int distance[16*32];

	for (int a=0;a<64;a++)
	{
		image[a].red=(a%8)<<5;
		image[a].green=(a/8)<<5;
		image[a].blue=(a/8)<<5;
	}


	int off=0;
	int shiftX,shiftY;

	while(running_)
	{
		off+=1;
		off%=360;	
		usleep(1000*50);

		for(int x = 0; x < w; x++)
			for(int y = 0; y < h; y++)
			{
				Pixel d;
				d=image[((int)(10+x+5*sin(off*10*3.1415/360))%8+(int)(y+15*cos(off*10*3.1415/360))*8+64*3)%64 ];
				matrix_->SetPixel(x,y,d.red,d.green,d.blue);

			}

	}
}
