#include "Getdata.h"

int main()
{


GetData *data = new  GetData('f');
data->Start();

while (1)
{
sleep(1);
fprintf(stderr,"ok\n");
}



return 0;
}
