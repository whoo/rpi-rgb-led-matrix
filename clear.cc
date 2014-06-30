#include "led-matrix.h"
#include "thread.h"
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


//using std::min;
//using std::max;



int main(int argc, char *argv[]) {
  GPIO io;
  if (!io.Init()) return 1;
  RGBMatrix m(&io);

/*  updater->Start(10);  // high priority
  delete updater; */

  // Final thing before exit: clear screen and update once, so that
  // we don't have random pixels burn
  m.ClearScreen();
  m.UpdateScreen();

  return 0;
}
