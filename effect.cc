#include "effect.h"


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
				CLEARSCR;
				
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
		
		for(int a=0;a<32*16;a++)
		{
			matrix_->SetPixel(a%32,a/32,image[v+u*8].red,image[v+u*8].green,image[v+u*8].blue);

		}

	}

}

void Plasma::Run(){
	const int w = matrix_->width();
	const int h = matrix_->height();
	int off=0;

	int val=rand()%6;
	
	while (running_)
	{
		usleep(1000*50);
		off+=1;
		off%=360;

		for(int x=0;x<w;x++)
			for(int y=0;y<h;y++)
			{
				//		int c=128+128*sin((x+off)*6*3.1415/32);

				int c=(128+128*sin( (sqrt((x-w/2)*(x-w/2)+(y-h/2)*(y-h/2))+off)*2*3*3.1415/32)+
						128+128*sin((y+off/2)*6*3.1415/32)+
						128+128*sin((x+off/2)*6*3.1415/32)+
						128+128*sin( (sqrt(x*x+y*y)*2*5*3.1415/32)))/4; 

			switch(val) {
			case 0: matrix_->SetPixel(x,y,c>>1,c,(c*2)&0xff); break;
			case 1: matrix_->SetPixel(x,y,c>>1,(c*2)&0xff,c); break;
			case 2:	matrix_->SetPixel(x,y,c,(c*2)&0xff,c>>1);break;
			case 3:	matrix_->SetPixel(x,y,c,c>>1,(c*2)&0xff);break;
			case 4: matrix_->SetPixel(x,y,(c*2)&0xff,c>>1,c);break;
			case 5: matrix_->SetPixel(x,y,(c*2)&0xff,c,c>>1);break;
			default: matrix_->SetPixel(32-x,y,c>>1,c,(c*2)&0xff);
				}
			}

	}
}

void Clock::Run(){
	const int width = matrix_->width();
	const int height = matrix_->height();

	//bool tb[3*8];
	bool *txt;
	char buff[20];
	int off=0;

	std::string t1;

	std::ifstream infile("data/file");
	std::string line;


	getline(infile,t1);
	txt=prinTxt(t1);
	Pixel color;
	color.red=(rand()*1000)%0xff;
	color.green=(rand()*1000)%0xff;
	color.blue=(rand()*1000)%0xff;

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
				matrix_->SetPixel(x,y, txt[a]*x<<3,txt[a]*(y<<2),(255-(x<<3))*txt[a]);
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


bool ImageScroller::LoadPPM(std::string filename) {
    if (image_) {
      delete [] image_;
      image_ = NULL;
    }
    FILE *f = fopen((char*)filename.c_str(), "r");
    if (f == NULL) return false;
    char header_buf[256];
    const char *line = ReadLine(f, header_buf, sizeof(header_buf));
#define EXIT_WITH_MSG(m) { fprintf(stderr, "%s: %s |%s", (char*)filename.c_str(), m, line); \
      fclose(f); return false; }
    if (sscanf(line, "P6 ") == EOF)
      EXIT_WITH_MSG("Can only handle P6 as PPM type.");
    line = ReadLine(f, header_buf, sizeof(header_buf));
    if (!line || sscanf(line, "%d %d ", &width_, &height_) != 2)
      EXIT_WITH_MSG("Width/height expected");
    int value;
    line = ReadLine(f, header_buf, sizeof(header_buf));
    if (!line || sscanf(line, "%d ", &value) != 1 || value != 255)
      EXIT_WITH_MSG("Only 255 for maxval allowed.");
    const size_t pixel_count = width_ * height_;
    image_ = new Pixel [ pixel_count ];
    assert(sizeof(Pixel) == 3);   // we make that assumption.
    if (fread(image_, sizeof(Pixel), pixel_count, f) != pixel_count) {
      line = "";
      EXIT_WITH_MSG("Not enough pixels read.");
    }
#undef EXIT_WITH_MSG
    fclose(f);
    //fprintf(stderr, "Read image with %dx%d\n", width_, height_);
    horizontal_position_ = 0;
    return true;
  }

void ImageScroller::Run(){
  //  const int screen_height = matrix_->height();
  //  const int screen_width = matrix_->width();
    while (running_) {
      if (image_ == NULL) {
        usleep(100 * 1000);
        continue;
      }
      usleep(30 * 1000);
      for (int x = 0; x < 32; ++x) {
        for (int y = 0; y < 16; ++y) {
          const Pixel &p = getPixel((horizontal_position_ + x) % width_, y);
          // Display upside down on my desk. Lets flip :)
          int disp_x = /*screen_width -*/ x;
          int disp_y = /*screen_height -*/ y;
          matrix_->SetPixel(disp_x, disp_y, p.red, p.green, p.blue);
        }
      }
      ++horizontal_position_;
    }
  }


