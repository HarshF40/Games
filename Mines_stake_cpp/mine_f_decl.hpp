#ifndef FUNC_HPP
#define FUNC_HPP
float getmoney(); // Asks the Player to enter initial value to start the game and returns it.
void gen_be_grid(char (*arr_ptr)[5],void (*funcptr)(char (*)[5],int),int num_mines); // Function to generate backend grid. It will generate Diamonds and pass it to other function to generate mines.
void gen_mine(char (*arr_ptr2)[5],int num_of_mines1); // This function will generate random mines by using mersenne twister.
void read_rules();
#endif