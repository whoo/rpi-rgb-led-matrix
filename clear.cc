#include "led-matrix.h"

/// Clear Screen //

int main(int argc, char *argv[]) {
  GPIO io;
  if (!io.Init()) return 1;
  RGBMatrix m(&io);

  m.ClearScreen();
  m.UpdateScreen();
  return 0;
}
