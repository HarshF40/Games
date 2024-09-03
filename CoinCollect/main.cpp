#include<iostream>
#include<ncurses.h>
#include<chrono>
#include<random>
#include"function.hpp"

int main(){

  char choice;

  do{

  spritePos pos{0,0};
  int score=0;

  GenBase();

  initscr();

  MainGame();

  endwin(); 

  system("clear");
  std::cout<<"\nQuit(q)/Play Again(p): ";
  std::cin>>choice;

  }while(choice != 'q');

  return 0;
}
