#include<iostream>
#include"mine_f_decl.hpp"
#include<random>

float getmoney(){ // Will return money which will be stored in variable throughout the game. Limit to the money in the wallet is 1000.
  
  system("clear");
  
  float money;
  
  do{ // Loop will go on until the value is between 0 and 1001.
  std::cout<<std::endl<<"Enter The Amount of money to start with(1-1000): ";
  std::cin>>money;
  }while(money>1000 || money<0);
  
  return money;
}

void gen_be_grid(char (*arr_ptr)[5],void (*funcptr)(char (*)[5],int),int num_mines){ // Generates grid full of diamonds then passes the array to genmine with pointers to create mines.
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      arr_ptr[i][j]='0';
    }
  }
  funcptr(arr_ptr,num_mines);
}

void read_rules(){
  
  system("clear");
  
  std::cout<<std::endl<<"About: "<<"\n\nThis Game is C++ version of Mines Game from Stake.Player has to bet money and select the tiles with Diamonds,if player opens a mine the match ends and the player loses the money.";
  std::cout<<std::endl<<"\n\n# -> tile\n0 -> Diamond\n* -> mine";
  std::cout<<std::endl<<"\nPosition Map of the Grid: \n";
  
  for(int i=0;i<5;i++){ // Display the position Map.
    std::cout<<"\n";
    for(int j=0;j<5;j++){
      std::cout<<i<<" "<<j<<"   ";
    }
  }
  
  std::cout<<"\n\nWARNING: \n";
  std::cout<<"\nEnter The Row & Column Position of the tile individually!!!\n\n";
  
}