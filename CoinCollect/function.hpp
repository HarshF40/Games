#ifndef FUNC_HPP
#define FUNC_HPP

#define R if(ch == 'r' || ch == 'R') //Up
#define N if(ch == 'n' || ch == 'N') //Down
#define D if(ch == 'd' || ch == 'D') //Left
#define J if(ch == 'j' || ch == 'J') //Right

struct spritePos{
  int y;
  int x;
};

unsigned int genCoinRow();
unsigned int genCoinCol();

#endif
