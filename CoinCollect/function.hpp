#ifndef FUNC_HPP
#define FUNC_HPP

#define UP if(ch == 'w' || ch == 'W') //Up
#define DOWN if(ch == 's' || ch == 'S') //Down
#define LEFT if(ch == 'a' || ch == 'A') //Left
#define RIGHT if(ch == 'd' || ch == 'D') //Right

struct spritePos{
  int y;
  int x;
};

struct chaserPos{
  int y;
  int x;
};

  extern spritePos pos;
  extern chaserPos cPos;
  extern char arr[20][50];
  extern char ch;
  extern int score;

unsigned int genCoinRow();
unsigned int genCoinCol();
void GenBase();
void MainGame();
void update();
void moveChaser();
void displayGrid();

#endif
