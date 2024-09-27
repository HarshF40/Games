#include<iostream>
#include<ncurses.h>
#include<chrono>
#include<random>
#include"function.hpp"

  spritePos pos{0,0};
  chaserPos cPos{19,49};

int main(){

game:

  char choice;

  pos.y=0;
  pos.x=0;
  cPos.y=19;
  cPos.x=49;

  initscr();

  GenBase();
  MainGame(); 

  endwin();

  std::cout<<"\nEnter Choice: ";
  std::cin>>choice;

  if(choice == 'p')
    goto game;


  std::cout<<std::endl<<"Program Complete!";

  return 0;
}
