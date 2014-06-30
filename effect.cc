#include "effect.h"

#define MAXSTAR 20 

#define CLEARSCR	for (int xe = 0; xe < width; ++xe) for (int ye = 0; ye < height; ++ye) { matrix_->SetPixel(xe,ye, 0,0,0); }

void StarField::Run() {
			const int width = matrix_->width();
			const int height = matrix_->height();
			uint32_t count = 0;
			int x=0;
			int y=0;
			int a=0;

			char star[MAXSTAR*2];
			for (a=0;a<MAXSTAR;a++)
			{
			star[a]=rand()%16;
			star[a+MAXSTAR]=rand()%360;
			}

			while (running_) {
				usleep(50000);
				++count;
				int color = (count >> 9) % 6;
				int value = count & 0xFF;
				if (count & 0x100) value = 255 - value;
				int r, g, b;
				switch (color) {
					case 0: r = value; g = b = 0; break;
					case 1: r = g = value; b = 0; break;
					case 2: g = value; r = b = 0; break;
					case 3: g = b = value; r = 0; break;
					case 4: b = value; r = g = 0; break;
					default: r = g = b = value; break;
				}
				for (int xe = 0; xe < width; ++xe)
					for (int ye = 0; ye < height; ++ye)
					{
						matrix_->SetPixel(xe,ye, 0,0,0);
					}

				for (a=0;a<MAXSTAR;a++)
				{
				x=cos(star[a+MAXSTAR])*star[a]+16;
				y=sin(star[a+MAXSTAR])*star[a]+8;
				matrix_->SetPixel(x,y,r+(star[a]),(g+r)*(star[a]*255/16),b*(star[a]*10));
				star[a]+=1;
				if (x>32 or x<0 or y>16 or y<0) {
					star[a]=1;
					star[a+MAXSTAR]=rand()%360;
					}
				}

			}
		};

void Fire::Run(){
	long int tb[512],buff[512];
	const int width = matrix_->width();
	const int height = matrix_->height();

	memset(tb,0,sizeof(tb));

	/*	for (int a=0;a<32*2;a++)
		{
		tb[a]=rand()&0xff0000;
		} */

	while (running_) {

		usleep(90000);

		tb[rand()%32*2]=rand()&0xff8000;

		memcpy(buff,tb,sizeof(tb));
		for (int a=32;a<512;a++)
		{
			tb[a]=( buff[a-1] + buff[a+1] + buff[a+32]+buff[a-32])/8;
		}


		for(int x=0;x<width;++x)
			for(int y=0;y<height;++y)
			{	
				matrix_->SetPixel(x,y, 
						(tb[x+y*32]&0xFF0000)>>16 ,
						(tb[x+y*32]&0x007000)>>8 ,
						(tb[x+y*32]&0x000000));
				//	fprintf(stderr,"%x %x %x %x\n",tb[x+y*16],(tb[x+y*16]&0xFF0000)>>16,(tb[x+y*16]&0x00FF00)>>8,(tb[x+y*16]&0x0000FF));
			}


	}

}

void BinClock::Run() {
	bool tb[3*8];

	while(running_)
	{
		memset(tb,0,sizeof(tb));	
		time_t result;
		struct tm *ttime;
		int sec,min,hur;

		usleep(1*1000*90);
		time(&result);
		ttime = localtime(&result);

		sec=ttime->tm_sec;
		min=ttime->tm_min;
		hur=(ttime->tm_hour%12);

		for (int a=0;a<8;a++) tb[a]=	sec>>a&0x1;
		for (int a=0;a<8;a++) tb[a+8]=	min>>a&0x1;
		for (int a=0;a<8;a++) tb[a+16]=	hur>>a&0x1;


		for (int a=0;a<(3*8);a++)
		{
			matrix_->SetPixel(15+a/8*3,a%8,0x1f,0x1f*tb[a],0);
			matrix_->SetPixel(15+a/8*3+1,a%8,0x1f,0x1f*tb[a],0);
		}
	}
}

void Table::Run() 
{

	Pixel image[16*8];
	for(int x=0;x<8;++x)
		for(int y=0;y<8;++y)
		{
			image[x+y*8].red=(8-x)*32-1;
			image[x+y*8].green=x*32-1;
			image[x+y*8].blue=(8-y)*32-1;
		}

	int angle=0;
	int v=0,u=0;
	while(running_)
	{
		usleep(1000*50);
		angle+=1;
		angle%=360;
		int xx=sin(angle*2*3.1415/360);
		int yy=cos(angle*2*3.1415/360);
		
		for(int a=0;a<32*16;a++)
		{
			matrix_->SetPixel(a%32,a/32,image[v+u*8].red,image[v+u*8].green,image[v+u*8].blue);

		}

	}

}

void Clock::Run(){
	const int width = matrix_->width();
	const int height = matrix_->height();

	bool tb[3*8];
	bool *txt;
	int off=0;
	char buff[20];

	std::string t1;

	std::ifstream infile("data/file");
	std::string line;


	getline(infile,t1);
	txt=prinTxt(t1);
	Pixel color;
	color.red=0xff;
	color.green=0x7c;
	color.blue=0x08;

	while (running_)
	{	

		time_t result;
		struct tm *ttime;

		time(&result);
		ttime = localtime(&result);
		strftime(buff,sizeof(buff),"%T",ttime);

		usleep(50000);
		CLEARSCR;
		putTxt(matrix_,0,1,std::string(buff),color);
		for (unsigned int a=0;a<t1.size()*15;a++) 
		{ 
			int x=32+a%3+a/15*4-off;
			int y=(a/3)%5+10;
			if (x>=0 and x<32 and y>=0 and y<16)
			{
				matrix_->SetPixel(x,y, 16*txt[a],txt[a],off*txt[a]);
			}
		}

		off+=1;
		off%=t1.size()*4+32;

		if (off==0)
		{
			getline(infile,t1);
			if (!infile.eof()) txt=prinTxt(t1);
			else { infile.clear(); infile.seekg(0); }
		}


	}
	free(txt);
	infile.close();
}


void putTxt(RGBMatrix *m,int orig_x,int orig_y,std::string txt,Pixel color )
{
	bool *text = prinTxt(txt);
	for (unsigned int a=0;a<txt.size()*15;a++)
	{
		int x=orig_x+a%3+a/15*4;
		int y=orig_y+(a/3)%5;
		if (x>=0 and x<m->width() and y>=0 and y<16)
		{
			m->SetPixel(x,y, color.red*text[a],color.green*text[a],color.blue*text[a]);
		}       
	}
}

bool *prinTxt(std::string txt)
{
	bool *tb;
	tb=(bool*)malloc(3*5*txt.size()*sizeof(bool));
	memset(tb,0,3*5*txt.size()*sizeof(bool));
	int off=0;
	for (unsigned int a=0;a<txt.size();a++)
	{
		off=a*15;
		switch(tolower(txt[a])) {
			case '0': memcpy(tb+off,font_0,15);break;
			case '1': memcpy(tb+off,font_1,15);break;
			case '2': memcpy(tb+off,font_2,15);break;
			case '3': memcpy(tb+off,font_3,15);break;
			case '4': memcpy(tb+off,font_4,15);break;
			case '5': memcpy(tb+off,font_5,15);break;
			case '6': memcpy(tb+off,font_6,15);break;
			case '7': memcpy(tb+off,font_7,15);break;
			case '8': memcpy(tb+off,font_8,15);break;
			case '9': memcpy(tb+off,font_9,15);break;
			case 'a': memcpy(tb+off,font_a,15);break;
			case 'b': memcpy(tb+off,font_b,15);break;
			case 'c': memcpy(tb+off,font_c,15);break;
			case 'd': memcpy(tb+off,font_d,15);break;
			case 'e': memcpy(tb+off,font_e,15);break;
			case 'f': memcpy(tb+off,font_f,15);break;
			case 'g': memcpy(tb+off,font_g,15);break;
			case 'h': memcpy(tb+off,font_h,15);break;
			case 'i': memcpy(tb+off,font_i,15);break;
			case 'j': memcpy(tb+off,font_j,15);break;
			case 'k': memcpy(tb+off,font_k,15);break;
			case 'l': memcpy(tb+off,font_l,15);break;
			case 'm': memcpy(tb+off,font_m,15);break;
			case 'n': memcpy(tb+off,font_n,15);break;
			case 'o': memcpy(tb+off,font_o,15);break;
			case 'p': memcpy(tb+off,font_p,15);break;
			case 'q': memcpy(tb+off,font_q,15);break;
			case 'r': memcpy(tb+off,font_r,15);break;
			case 's': memcpy(tb+off,font_s,15);break;
			case 't': memcpy(tb+off,font_t,15);break;
			case 'u': memcpy(tb+off,font_u,15);break;
			case 'v': memcpy(tb+off,font_v,15);break;
			case 'w': memcpy(tb+off,font_w,15);break;
			case 'x': memcpy(tb+off,font_x,15);break;
			case 'y': memcpy(tb+off,font_y,15);break;
			case 'z': memcpy(tb+off,font_z,15);break;
			case '.': memcpy(tb+off,font_dot,15);break;
			case ',': memcpy(tb+off,font_coma,15);break;
			case '\'': memcpy(tb+off,font_quote,15);break;
			case '"': memcpy(tb+off,font_2quote,15);break;
			case '+': memcpy(tb+off,font_plus,15);break;
			case '-': memcpy(tb+off,font_minus,15);break;
			case ':': memcpy(tb+off,font_2dot,15);break;
			case '(': memcpy(tb+off,font_parA,15);break;
			case ')': memcpy(tb+off,font_parB,15);break;
			default:  memcpy(tb+off,font_space,15);
		}
	}
	return tb;
}
