#include<chrono>
#include<random>
#include<ncurses.h>
#include<chrono>
#include<thread>
#include<mutex>
#include<vector>
#include<utility>
#include"function.hpp"

//vector with std::pair to store the possition of the coins to then compare with the position of the chaser... to block it or not

  char arr[20][50];
  char ch;
  int score=0;
  static bool gameRunning;
  static bool lostByChaser;
  std::vector<std::pair<int,int>> coinsCoord;
  std::mutex g_lock;


unsigned int genCoinRow(){
  std::random_device rd{};
  std::seed_seq ss{static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()),rd(),rd(),rd(),rd(),rd(),rd(),rd()};
  std::mt19937 mt{ss};
  std::uniform_int_distribution<int> genPos{0,19};
  return genPos(mt);
}


unsigned int genCoinCol(){
  std::random_device rd{};
  std::seed_seq ss{static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()),rd(),rd(),rd(),rd(),rd(),rd(),rd()};
  std::mt19937 mt{ss};
  std::uniform_int_distribution<int> genPos{0,49};
  return genPos(mt);
}

void displayGrid(){
  refresh();
 for(int i=0;i<20;i++){
  printw("\n");
    for(int j=0;j<50;j++){
      if(arr[i][j]=='@'){
          attron(COLOR_PAIR(5));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(5));
        } else if(arr[i][j] == '$'){
          attron(COLOR_PAIR(3));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(3));
        } else if(arr[i][j] == '#'){
          attron(COLOR_PAIR(4));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(4));
        } else if(arr[i][j] == '%') {
          attron(COLOR_PAIR(1));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(1));
        } else {
          attron(COLOR_PAIR(2));
          printw("%2c",arr[i][j]);
          attroff(COLOR_PAIR(2));
      }
    }
  } 
}

void MainGame(){

  gameRunning = true;
  lostByChaser = false;
  int score = 0;

  start_color();
  init_pair(1,196,COLOR_BLACK);
  init_pair(2,33,COLOR_BLACK);
  init_pair(3,226,COLOR_BLACK);
  init_pair(4,14,COLOR_BLACK);
  init_pair(5,82,COLOR_BLACK);

  std::thread chaser(update);

  do{

//Generate Barriers
 g_lock.lock();
  int row,column,Bcount=0;                                  
    while(Bcount<60){                                         
      row = genCoinRow(); 
      column = genCoinCol();       
      if((arr[row][column]!='@') && (arr[row][column]!='$') && (arr[row][column]!='%')){ 
        arr[row][column] = '#';                               
        Bcount++;                                             
      } else {                                               
        continue;                                             
      }                                                       
  }
  g_lock.unlock();

ifBlank: 

    clear();
    refresh();

    displayGrid(); 

    printw("\nScore: %d/30\n",score);
    ch = getch();
  
  UP{

    if(((pos.y)>0) && (arr[(pos.y)-1][(pos.x)]!='#')){
      if(arr[(pos.y)-1][pos.x] == '$'){
        score++;
      }
    arr[(pos.y)-1][pos.x] = '@';
    arr[pos.y][pos.x] = ' ';
    (pos.y)--;
    } else {
      goto ifBlank;
    }
  } else DOWN {
    if((pos.y)<19 && (arr[(pos.y)+1][(pos.x)]!='#')){
      if(arr[(pos.y)+1][pos.x] == '$'){
        score++;
      }
    arr[(pos.y)+1][pos.x] = '@';
    arr[pos.y][pos.x] = ' ';
    (pos.y)++;
    } else {
      goto ifBlank;
    }
  } else LEFT {
    if((pos.x)>0 && (arr[(pos.y)][(pos.x)-1]!='#')){
      if(arr[pos.y][(pos.x)-1] == '$'){
        score++;
      }
    arr[pos.y][(pos.x)-1] = '@';
    arr[pos.y][pos.x] = ' ';
    (pos.x)--;
    } else {
      goto ifBlank;
    }
  } else RIGHT {
    if((pos.x)<49 && (arr[(pos.y)][(pos.x)+1]!='#')){
      if(arr[pos.y][(pos.x)+1] == '$'){
        score++;
      }
    arr[pos.y][(pos.x)+1] = '@';
    arr[pos.y][pos.x] = ' ';
    (pos.x)++;
    } else {
      goto ifBlank;
    }
  } else {
    goto ifBlank;
  }

  g_lock.lock();
       //Reset Blank
      for(int i=0;i<20;i++){     
        for(int j=0;j<50;j++){   
          if(arr[i][j] == '#')   
            arr[i][j] = ' ';     
          else                   
            continue;            
          }                        
        }                          
  g_lock.unlock();

}while(score<30 && !lostByChaser);

  gameRunning = false;
  chaser.join();

}


void GenBase(){
//Generate Base and add sprite
  for(int i=0;i<20;i++){        
    for(int j=0;j<50;j++){      
      arr[i][j] = ' ';          
    }                           
  }                             
  arr[pos.y][pos.x] = '@';      
  arr[cPos.y][cPos.x] = '%';    

//Generate Coins
  int row,column,Ccount=0;                                  
  while(Ccount<30){                                         
    row = genCoinRow();                                     
    column = genCoinCol(); 
    //y,x ==> pair
    coinsCoord.push_back(std::make_pair(row,column));                                 
    if((arr[row][column]!='@') && (arr[row][column]!='$') && (arr[row][column]!='%')){
      arr[row][column] = '$';                               
      Ccount++;                                             
    } else {                                                
      continue;                                             
    }                                                       
  }                                                         
}


void moveChaser(){ 
  //princple diagonal 
  if(cPos.x >= 0 && cPos.y >= 0 && cPos.y<=19 && cPos.x<=49){
  if((pos.y - pos.x == cPos.y - cPos.x)){
    if(pos.y>cPos.y && checkCoin(cPos.y+1,cPos.x+1)){
      arr[++cPos.y][++cPos.x] = '%';
      arr[cPos.y-1][cPos.x-1] = ' ';
    } else if(checkCoin(cPos.y-1,cPos.x-1)){
      arr[--cPos.y][--cPos.x] = '%';
      arr[cPos.y+1][cPos.x+1] = ' ';
    }//other diagonal
  } else if(pos.y + pos.x == cPos.y + cPos.x){
    if(pos.y>cPos.y && checkCoin(cPos.y+1,cPos.x-1)){
      arr[++cPos.y][--cPos.x] = '%';
      arr[cPos.y-1][cPos.x+1] = ' ';
    } else if(checkCoin(cPos.y-1,cPos.x+1)){
      arr[--cPos.y][++cPos.x] = '%';
      arr[cPos.y+1][cPos.x-1] = ' ';
    }//up(--) & down(++)
  } else if(pos.x==cPos.x){
    if(pos.y<cPos.y && checkCoin(cPos.y-1,cPos.x)){
      arr[--cPos.y][cPos.x] = '%';
      arr[cPos.y+1][cPos.x] = ' ';
    } else if(checkCoin(cPos.y+1,cPos.x)){
      arr[++cPos.y][cPos.x] = '%';
      arr[cPos.y-1][cPos.x] = ' ';
    }//right(++) & left(--)
  } else if(pos.y == cPos.y) {
    if(pos.x > cPos.x && checkCoin(cPos.y,cPos.x+1)){
      arr[cPos.y][++cPos.x] = '%';
      arr[cPos.y][cPos.x-1] = ' ';
    } else if(checkCoin(cPos.y,cPos.x-1)){
      arr[cPos.y][--cPos.x] = '%';
      arr[cPos.y][cPos.x+1] = ' ';
    } 
  } else if(pos.y<cPos.y) {
    if(pos.x<cPos.x && checkCoin(cPos.y-1,cPos.x-1)){
      arr[--cPos.y][--cPos.x] = '%';
      arr[cPos.y+1][cPos.x+1] = ' ';
    } else if(checkCoin(cPos.y-1,cPos.x+1)){
      arr[--cPos.y][++cPos.x] = '%';
      arr[cPos.y+1][cPos.x-1] = ' ';
    }
  } else if(pos.y > cPos.y) {
    if(pos.x<cPos.x && checkCoin(cPos.y+1,cPos.x-1)){
        arr[++cPos.y][--cPos.x] = '%';
        arr[cPos.y-1][cPos.x+1] = ' ';
     } else if(checkCoin(cPos.y+1,cPos.x+1)){
       arr[++cPos.y][++cPos.x] = '%';
       arr[cPos.y-1][cPos.x-1] = ' ';
      }
    }
  }
} 


void update(){
  while(gameRunning){
    
    std::this_thread::sleep_for(std::chrono::milliseconds(350));
    moveChaser();

    move(0,0);
    refresh();

    displayGrid();

      if(pos.x == cPos.x && pos.y == cPos.y){
        lostByChaser = true;
        clear();
        refresh();
        displayGrid();
        break;
    }
  }
}

bool checkCoin(int yCoord, int xCoord){
  std::pair<int,int> coords(yCoord,xCoord);
  for(const auto& pair : coinsCoord){
    if(pair == coords)
      return false;
  }
  return true;
}