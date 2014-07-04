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
		image[a].blue=(a+a)<<2;
	}


	int off=0;
	int shiftX,shiftY;

	int xx,yy;
	int u,v;
	int a,r;
	int _u,_v;
	while(running_)
	{
		off+=1;
		off%=360;	
		usleep(1000*50);


		u=v=0;

		for(int x = 0; x < w; x++)
		{
			_u=u;
			_v=v;
			for(int y = 0; y < h; y++)
			{
				r= sqrt( (x-16)*(x-16) + (y-8)*(y-8))+off;
				if (x!=16) a=(int)atan( (y-8) / (x-16))*360;
				
				u=(int)(r*cos((a+off)*3.14/360))%8;
				v=(int)(r*sin((a+off)*3.14/360))%8;
				Pixel d;
				d=image[abs((u)%8+(v)*8)%64];
				matrix_->SetPixel(x,y,d.red,d.green,d.blue);
			}
		}

	}
}
