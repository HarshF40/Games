#include<iostream>
#include"mine_f_decl.hpp"
#include<optional>
#include<random>

float money; 

void gen_mine(char (*arr_ptr2)[5],int num_of_mines1){ // Generates mines using mersenne twister random number generator from the device.
  std::random_device rd{};
  std::seed_seq ss{rd(),rd(),rd(),rd(),rd(),rd(),rd(),rd()}; // Seed sequence for generating random number.
  std::mt19937 mt{ss};
  std::uniform_int_distribution genr{0,4}; // Generates random number between 0 to 4.
  int r,c;
  for(int i=0;i<num_of_mines1;i++){
    loop:  // This statement executes only if a mine exists on that position.
    r=genr(mt);
    c=genr(mt);
    if(arr_ptr2[r][c]=='*'){
      goto loop;
    } else {
      arr_ptr2[r][c]='*'; // Assigning a mine to a randomly generated position.
    }
    }
  }
  
int main(){
  
  rule_loop: // This statement is executed only if player reads the about and  wants to play the game.
  
  char rulevar; // Variable to take choice, quit or continue.
  char choice; // Choice whether to start,read about or quit;
  
  system("clear"); // To clear the all other things from screen.
  
  std::cout<<std::endl<<"M!NES"<<std::endl<<std::endl<<std::endl;
  std::cout<<std::endl<<" Play(p)"<<std::endl<<" Read(r)"<<std::endl<<" Quit(q)"<<std::endl; // Main menu.
  
  do{   // Do while loop till user enters a valid  input.
  std::cout<<std::endl<<"Enter your Choice: ";
  std::cin>>choice;
  }while(choice != 'p' && choice != 'P' && choice != 'r' && choice != 'q' && choice != 'R' && choice != 'Q');
  
switch(choice){
  case 'r' :
  case 'R' : read_rules(); // Some info about the Game.
             std::cout<<"Quit or Continue(q/any key): ";
             std::cin>>rulevar;
             if(rulevar=='q' || rulevar=='Q'){
               return 0;
             } else {
               goto rule_loop;
             }
  case 'q':
  case 'Q': return 0; // Quits the Program.
  default : money=getmoney();
 }
 
 std::optional<char> quitch= 'c' ;
 
 while(quitch!=std::nullopt && *quitch!='q' && *quitch!='Q'){ // If money == 0 ;quitch = std::nullopt the while loop ends.
 
   system("clear");
   
   char backend_grid[5][5]; // This grid will contain all the data at backend. Like position of mine and diamond.
   char display_grid[9][9]={'#','|','#','|','#','|','#','|','#','-','|','-','|','-','|','-','|','-','#','|','#','|','#','|','#','|','#','-','|','-','|','-','|','-','|','-','#','|','#','|','#','|','#','|','#','-','|','-','|','-','|','-','|','-','#','|','#','|','#','|','#','|','#','-','|','-','|','-','|','-','|','-','#','|','#','|','#','|','#','|','#'}; //This grid will be used to display the grid and user will be able to interact with the grid;
   float bet_amount;
   int no_of_mines;
   char change; // This will store yes or no from user as y or n to edit the inputs, the loop will go on till user enters n.
   
   do{
   std::cout<<"Amount in Wallet: "<<money;
   std::cout<<std::endl<<"\nEnter the Bet Amount: ";
   std::cin>>bet_amount;
   std::cout<<std::endl<<"Enter No. of Mines: ";
   std::cin>>no_of_mines;
   std::cout<<std::endl<<"Edit the choices?(y/n): ";
   std::cin>>change;
   if(bet_amount>money || no_of_mines<1 || no_of_mines>24)
   change='y';
   }while(change=='y' || change == 'Y');
   
   money-=bet_amount; // Money in the wallet is deducted.
   
   system("clear");
   
   int diamonds_opened=0;
          // Adjust the factors as needed for desired scaling.
   float mine_factor = 0.5f; // Factor to amplify the effect of mines.
   float diamond_factor = 0.1f; // Factor to amplify the effect of diamonds.
   int no_of_diamonds=25 - no_of_mines;
   bool mine_open_flag=0; // Flag to indicate if player opens a mine.
   bool exit_flag=0; // Flag to indicate if player wants to exit.
   float multiplier = 1;
   int winmoney=0;
   int text_continue_or_quit=0; // Will be equal to 1 after 1st round so that the text appears.
   gen_be_grid(backend_grid,gen_mine,no_of_mines); // Will generate backend_grid with mines and diamond.
   
 while(mine_open_flag==0 && exit_flag==0 ){ // Loop will continue until the user opens a mine or want to quit.
   
   multiplier = multiplier * (1 + (mine_factor * no_of_mines / 25.0f) +
   (diamond_factor * diamonds_opened / 25.0f)); // Formula For multiplier used in Game.
   
   system("clear");
   
   int row,column;
   
   std::cout<<"Remaining Money: "<<money<<"\n";
   for(int i=0;i<9;i++){ // Displays the grid in the rounds.
     std::cout<<"\n";
     for(int j=0;j<9;j++){
       std::cout<<display_grid[i][j];
     }
   }
  
   if(diamonds_opened==no_of_diamonds){ // Checks if all ths diamonds are opened or not.
    
     system("clear");
     
     money+=winmoney; // Amount won will be added to main balance.
     
     std::cout<<"\nOpened All The diamonds!";
     std::cout<<"\nMoney Won: "<<winmoney;
     std::cout<<"\nTotal Money: "<<money;
     
     for(int i=0;i<5;i++){ // Copies all the diamonds and mines from backend grid to display grid.
       for(int j=0;j<5;j++){
         display_grid[i*2][j*2]=backend_grid[i][j];
       }
     }
     
     for(int i=0;i<9;i++){ // Displays the display grid with mines and diamonds.
       std::cout<<"\n";
       for(int j=0;j<9;j++){
         std::cout<<display_grid[i][j];
       }
     }
     break;
   }
   
   std::cout<<"\n\nBet Amount: "<<bet_amount;
   std::cout<<"\nMultiplier: "<<multiplier;
   std::cout<<"\nMoney Won: "<<winmoney<<"\n";
   
  if(text_continue_or_quit){ // Asks The user to continue or not after every round(Triggers after 1st round).
     char con_q;
     std::cout<<"\nContinue Or Stop The Round?(c/q): ";
     std::cin>>con_q;
     if(con_q=='q'){
       money+=winmoney;
       break;
     }
   }
   
   do{
     
   std::cout<<std::endl<<"Enter The Position to open the tile: ";
   std::cin>>row>>column;
   
   }while(row>4 && row<0 || column>4 && column <0 || display_grid[row*2][column*2]!='#');
   
   if(backend_grid[row][column]=='*'){ // Checks if Player opened a mine or not.
     
     system("clear");
     
     std::cout<<"You have Opened a mine!\n\n";
     
     for(int i=0;i<5;i++){ // Copies all the diamond from backend grid to display grid.
       for(int j=0;j<5;j++){
         display_grid[i*2][j*2]=backend_grid[i][j];
       }
     }
     
     for(int i=0;i<9;i++){ // Displays the grid with diamonds and mines.
       std::cout<<"\n";
       for(int j=0;j<9;j++){
         std::cout<<display_grid[i][j];
       }
     }
     
     std::cout<<"\n\n\nMoney lost: "<<bet_amount;
     mine_open_flag=1;
     
   } else if (backend_grid[row][column]=='0') {
     
     display_grid[row*2][column*2]=backend_grid[row][column]; // Copies the Diamond from backend grid to display grid.
     winmoney=bet_amount*multiplier;
     diamonds_opened++;
     text_continue_or_quit=1;
     
   }
 }
 
 if(money==0){ // If money is zero the program terminates.
   std::cout<<"Money is Over!";
   quitch=std::nullopt;
 }
 
 std::cout<<std::endl<<"Quit or Stay(q/any key): ";
 char temp_quit_flag;
 std::cin>>temp_quit_flag;
 
 if(temp_quit_flag=='q' || temp_quit_flag=='Q') // Else the loop will continue.
   quitch=std::nullopt;
 }
 
}
