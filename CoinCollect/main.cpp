#include<iostream>
#include<ncurses.h>
#include<chrono>
#include<random>
#include"function.hpp"

int main(){

  char choice;

  do{

  spritePos pos{0,0};
  char arr[20][50];
  char ch;
  int score=0;

///Generate Base and add sprite///
  for(int i=0;i<20;i++){        //
    for(int j=0;j<50;j++){      //
      arr[i][j] = '^';          //
    }                           //
  }                             //
  arr[pos.y][pos.x] = '@';      //
//////////////////////////////////

////Generate Coins////////////////////////////////////////////
  int row,column,Ccount=0;                                  //
  while(Ccount<30){                                         //
    row = genCoinRow();                                     //
    column = genCoinCol();                                  //
    if((arr[row][column]!='@') && (arr[row][column]!='$')){ //
      arr[row][column] = '$';                               //
      Ccount++;                                             //
    } else {                                                //
      continue;                                             //
    }                                                       //
  }                                                         //
//////////////////////////////////////////////////////////////





  initscr();



  start_color();
  init_pair(1,196,COLOR_BLACK);
  init_pair(2,33,COLOR_BLACK);
  init_pair(3,226,COLOR_BLACK);



  do{

////Generate Blank////////////////////////////////////////////
  int row,column,Bcount=0;                                  //
  while(Bcount<60){                                         //
    row = genCoinRow(); //used Random Coin generator        //
    column = genCoinCol();    // "                          //
    if((arr[row][column]!='@') && (arr[row][column]!='$')){ //
      arr[row][column] = ' ';                               //
      Bcount++;                                             //
    } else {                                                //
      continue;                                             //
    }                                                       //
  }                                                         //
//////////////////////////////////////////////////////////////

ifBlank:

    move(0,0);
    refresh();

    for(int i=0;i<20;i++){
      printw("\n");
      for(int j=0;j<50;j++){
        if(arr[i][j]=='@'){
          attron(COLOR_PAIR(1));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(1));
        } else if(arr[i][j] == '$'){
          attron(COLOR_PAIR(3));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(3));
        } else {
          attron(COLOR_PAIR(2));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(2));
        }
      }
    }

    printw("\n\nEnter: ");
    printw("\nScore: %d/30\n",score);

  ch = getch();
  
  R{

    if(((pos.y)>0) && (arr[(pos.y)-1][(pos.x)]!=' ')){
      if(arr[(pos.y)-1][pos.x] == '$'){
        score++;
      }
    arr[(pos.y)-1][pos.x] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.y)--;
    } else {
      goto ifBlank;
    }
  } else N {
    if((pos.y)<19 && (arr[(pos.y)+1][(pos.x)]!=' ')){
      if(arr[(pos.y)+1][pos.x] == '$'){
        score++;
      }
    arr[(pos.y)+1][pos.x] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.y)++;
    } else {
      goto ifBlank;
    }
  } else D {
    if((pos.x)>0 && (arr[(pos.y)][(pos.x)-1]!=' ')){
      if(arr[pos.y][(pos.x)-1] == '$'){
        score++;
      }
    arr[pos.y][(pos.x)-1] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.x)--;
    } else {
      goto ifBlank;
    }
  } else J {
    if((pos.x)<49 && (arr[(pos.y)][(pos.x)+1]!=' ')){
      if(arr[pos.y][(pos.x)+1] == '$'){
        score++;
      }
    arr[pos.y][(pos.x)+1] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.x)++;
    } else {
      goto ifBlank;
    }
  } else {

/////Reset Blank///////////////
//  for(int i=0;i<20;i++){   //
//    for(int j=0;j<50;j++){ //
//    if(arr[i][j] == ' ')   //
//    arr[i][j] = '^';       //
//      els                  //
//        continue;          //
//    }                      //
//  }                        //
///////////////////////////////

    goto ifBlank;

  }
/////Reset Blank///////////////
  for(int i=0;i<20;i++){     //
    for(int j=0;j<50;j++){   //
      if(arr[i][j] == ' ')   //
        arr[i][j] = '^';     //
      else                   //
        continue;            //
    }                        //
  }                          //
///////////////////////////////

}while(score<30);


  clear();
  move(0,0);
    refresh();


    for(int i=0;i<20;i++){
      printw("\n");
      for(int j=0;j<50;j++){
        if(arr[i][j]=='@'){
          attron(COLOR_PAIR(1));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(1));
        } else if(arr[i][j] == '$'){
          attron(COLOR_PAIR(3));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(3));
        } else {
          attron(COLOR_PAIR(2));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(2));
        }
      }
    }


  printw("\nYou Won!");
  getch();


  endwin(); 

  system("clear");
  std::cout<<"\nQuit(q)/Play Again(p): ";
  std::cin>>choice;

  }while(choice != 'q');

  return 0;
}
