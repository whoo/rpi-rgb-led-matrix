#ifndef FONT_H 
#define FONT_H

#include "tools.h"
#include <string>

static bool font_0[15] {
0,1,0,
1,0,1,
1,0,1,
1,0,1,
0,1,0
};

static bool font_1[15] {
0,1,0,
1,1,0,
0,1,0,
0,1,0,
1,1,1
};

static bool font_2[15] {
0,1,0,
1,0,1,
0,0,1,
0,1,0,
1,1,1
};

static bool font_3[15] {
1,1,1,
0,0,1,
0,1,1,
0,0,1,
1,1,1
};

static bool font_4[15] {
1,0,1,
1,0,1,
1,1,1,
0,0,1,
0,0,1
};

static bool font_5[15] {
1,1,1,
1,0,0,
1,1,1,
0,0,1,
1,1,1
};

static bool font_6[15] {
1,1,1,
1,0,0,
1,1,1,
1,0,1,
1,1,1
};

static bool font_7[15] {
1,1,1,
0,0,1,
0,1,0,
0,1,0,
0,1,0
};

static bool font_8[15] {
1,1,1,
1,0,1,
1,1,1,
1,0,1,
1,1,1
};

static bool font_9[15] {
1,1,1,
1,0,1,
1,1,1,
0,0,1,
1,1,1
};

static bool font_2dot[15] {
0,0,0,
0,1,0,
0,0,0,
0,1,0,
0,0,0
};

static bool font_dot[15] {
0,0,0,
0,0,0,
0,0,0,
0,0,0,
0,1,0
};


static bool font_a[15] {
1,1,1,
1,0,1,
1,1,1,
1,0,1,
1,0,1
};

static bool font_b[15] {
1,1,1,
1,0,1,
1,1,0,
1,0,1,
1,1,1
};
static bool font_c[15] {
1,1,1,
1,0,0,
1,0,0,
1,0,0,
1,1,1
};
static bool font_d[15] {
1,1,0,
1,0,1,
1,0,1,
1,0,1,
1,1,0
};
static bool font_e[15] {
1,1,1,
1,0,0,
1,1,0,
1,0,0,
1,1,1
};
static bool font_f[15] {
1,1,1,
1,0,0,
1,1,0,
1,0,0,
1,0,0
};
static bool font_g[15] {
1,1,1,
1,0,0,
1,0,1,
1,0,1,
1,1,1
};
static bool font_h[15] {
1,0,1,
1,0,1,
1,1,1,
1,0,1,
1,0,1
};
static bool font_i[15] {
1,1,1,
0,1,0,
0,1,0,
0,1,0,
1,1,1
};
static bool font_j[15] {
0,0,1,
0,0,1,
0,0,1,
0,0,1,
1,1,0
};
static bool font_k[15] {
1,0,1,
1,0,1,
1,1,0,
1,0,1,
1,0,1
};
static bool font_l[15] {
1,0,0,
1,0,0,
1,0,0,
1,0,0,
1,1,1
};
static bool font_m[15] {
1,0,1,
1,1,1,
1,0,1,
1,0,1,
1,0,1
};
static bool font_n[15] {
0,0,1,
1,0,1,
1,1,1,
1,0,1,
1,0,0
};
static bool font_o[15] {
1,1,1,
1,0,1,
1,0,1,
1,0,1,
1,1,1
};
static bool font_p[15] {
1,1,1,
1,0,1,
1,1,0,
1,0,0,
1,0,0
};
static bool font_q[15] {
1,1,1,
1,0,1,
1,0,1,
1,1,1,
0,0,1
};
static bool font_r[15] {
1,1,0,
1,0,1,
1,1,0,
1,0,1,
1,0,1
};
static bool font_s[15] {
0,1,1,
1,0,0,
0,1,0,
0,0,1,
1,1,0
};
static bool font_t[15] {
1,1,1,
0,1,0,
0,1,0,
0,1,0,
0,1,0
};
static bool font_u[15] {
1,0,1,
1,0,1,
1,0,1,
1,0,1,
1,1,1
};
static bool font_v[15] {
1,0,1,
1,0,1,
1,0,1,
1,0,1,
0,1,0
};
static bool font_w[15] {
1,0,1,
1,0,1,
1,0,1,
1,1,1,
1,0,1
};
static bool font_x[15] {
1,0,1,
1,0,1,
0,1,0,
1,0,1,
1,0,1
};
static bool font_y[15] {
1,0,1,
1,0,1,
0,1,0,
0,1,0,
0,1,0
};

static bool font_z[15] {
1,1,1,
0,0,1,
0,1,0,
1,0,0,
1,1,1
};

static bool font_space[15] {
0,0,0,
0,0,0,
0,0,0,
0,0,0,
0,0,0
};

static bool font_coma[15] {
0,0,0,
0,0,0,
0,0,1,
0,0,1,
0,1,0
};

static bool font_quote[15] {
0,0,1,
0,0,1,
0,1,0,
0,0,0,
0,0,0
};

static bool font_2quote[15] {
1,0,1,
1,0,1,
0,0,0,
0,0,0,
0,0,0
};

static bool font_plus[15] {
0,0,0,
0,1,0,
1,1,1,
0,1,0,
0,0,0
};

static bool font_minus[15] {
0,0,0,
0,0,0,
1,1,1,
0,0,0,
0,0,0
};

static bool font_parA[15] {
0,1,0,
1,0,0,
1,0,0,
1,0,0,
0,1,0
};

static bool font_parB[15] {
0,1,0,
0,0,1,
0,0,1,
0,0,1,
0,1,0
};

static bool font_quest[15] {
0,1,0,
1,0,1,
0,0,1,
0,1,0,
0,1,0
};

static bool font_arobase[15] {
1,1,0,
0,0,1,
0,1,1,
1,0,1,
1,1,1
};

//void putTxt(RGBMatrix *,int,int,std::string,Pixel);
//bool *prinTxt(std::string txt);


#endif
