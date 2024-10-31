#include<iostream>
#include<ncurses.h>
#include<chrono>
#include<random>
#include<cctype>
#include"function.hpp"

#define CYAN "\x1b[36m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

  spritePos pos{0,0};
  chaserPos cPos{19,49};

int main(){

  char val;

  system("clear");
  std::cout<<YELLOW<<"Coin Collect $"<<"\n\n\n   "<<CYAN<<"Play(p)\n   "<<RED<<"Exit(any key)"<<RESET<<"\n\nEnter: ";
  std::cin>>val;

  if(tolower(val)!='p')
    return 0;

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

  std::cout<<"\nEnter Choice(p/any key): ";
  std::cin>>choice;

  if(tolower(choice) == 'p')
    goto game;


  std::cout<<std::endl<<"Program Complete!\n";

  return 0;
}
