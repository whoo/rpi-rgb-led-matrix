#include "font.h"

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
			case '/': memcpy(tb+off,font_slash,15);break;
			case '\\': memcpy(tb+off,font_aslash,15);break;
			case '"': memcpy(tb+off,font_2quote,15);break;
			case '+': memcpy(tb+off,font_plus,15);break;
			case '-': memcpy(tb+off,font_minus,15);break;
			case ':': memcpy(tb+off,font_2dot,15);break;
			case '(': memcpy(tb+off,font_parA,15);break;
			case ')': memcpy(tb+off,font_parB,15);break;
			case '?': memcpy(tb+off,font_quest,15);break;
			case '@': memcpy(tb+off,font_arobase,15);break;
			default:  memcpy(tb+off,font_space,15);
		}
	}
	return tb;
}


