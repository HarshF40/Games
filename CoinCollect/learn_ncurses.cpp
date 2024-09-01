#include<iostream>
#include<ncurses.h>
#include<chrono>
#include<random>
#include<cstdlib>

#define W if(ch == 'w' || ch == 'W')
#define S if(ch == 's' || ch == 'S')
#define A if(ch == 'a' || ch == 'A')
#define D if(ch == 'd' || ch == 'D')

struct spritePos{
  int y;
  int x;
};

unsigned int genCoin(){
  std::random_device rd{};
  std::seed_seq ss{static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()),rd(),rd(),rd(),rd(),rd(),rd(),rd()};
  std::mt19937 mt{ss};
  std::uniform_int_distribution genPos{0,9};
  return genPos(mt);
}


int main(){

  spritePos pos{0,0};
  char arr[10][10];
  char ch;
  int score=0;

  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      arr[i][j] = '^';
    }
  }
  arr[pos.y][pos.x] = '@';

  int row,column,ten_count=0;
  while(ten_count<10){
    row = genCoin();
    column = genCoin();
    if((arr[row][column]!='@') && (arr[row][column]!='$')){
      arr[row][column] = '$';
      ten_count++;
    } else {
      continue;
    }
  }



  initscr();



  start_color();
  init_pair(1,196,COLOR_BLACK);
  init_pair(2,33,COLOR_BLACK);
  init_pair(3,226,COLOR_BLACK);



  do{

    move(0,0);
    refresh();

    for(int i=0;i<10;i++){
      printw("\n");
      for(int j=0;j<10;j++){
        if(arr[i][j]=='@'){
          attron(COLOR_PAIR(1));
          printw("%c",arr[i][j]);
          attroff(COLOR_PAIR(1));
        } else if(arr[i][j] == '$'){
          attron(COLOR_PAIR(3));
          printw("%c",arr[i][j]);
          attroff(COLOR_PAIR(3));
        } else {
          attron(COLOR_PAIR(2));
          printw("%c",arr[i][j]);
          attroff(COLOR_PAIR(2));
        }
      }
    }

    printw("\n\nEnter: ");
    printw("\nScore: %d/10\n",score);

  ch = getch();
  
  W{

    if((pos.y)>0){
      if(arr[(pos.y)-1][pos.x] == '$'){
        score++;
      }
    arr[(pos.y)-1][pos.x] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.y)--;
    } else {
      continue;
    }
  } else S {
    if((pos.y)<9){
      if(arr[(pos.y)+1][pos.x] == '$'){
        score++;
      }
    arr[(pos.y)+1][pos.x] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.y)++;
    } else {
      continue;
    }
  } else A {
    if((pos.x)>0){
      if(arr[pos.y][(pos.x)-1] == '$'){
        score++;
      }
    arr[pos.y][(pos.x)-1] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.x)--;
    } else {
      continue;
    }
  } else D {
    if((pos.x)<9){
      if(arr[pos.y][(pos.x)+1] == '$'){
        score++;
      }
    arr[pos.y][(pos.x)+1] = '@';
    arr[pos.y][pos.x] = '^';
    (pos.x)++;
    } else {
      continue;
    }
  } else {
    continue;
  }
}while(score<10);


  clear();
  move(0,0);
    refresh();


    for(int i=0;i<10;i++){
      printw("\n");
      for(int j=0;j<10;j++){
        if(arr[i][j]=='@'){
          attron(COLOR_PAIR(1));
          printw("%c",arr[i][j]);
          attroff(COLOR_PAIR(1));
        } else if(arr[i][j] == '$'){
          attron(COLOR_PAIR(3));
          printw("%c",arr[i][j]);
          attroff(COLOR_PAIR(3));
        } else {
          attron(COLOR_PAIR(2));
          printw("%c",arr[i][j]);
          attroff(COLOR_PAIR(2));
        }
      }
    }


  printw("\nYou Won!");
  getch();


  endwin(); 

  return 0;
}
