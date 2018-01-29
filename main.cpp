//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// 1422827, main.cpp
// This C++ program plays a game of naughyts and crosses
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "functions.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// main()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main()
{
    std::string response;
    unsigned human_no;
    
    // Seed the random number generator (used to make random picks)
    srand((unsigned)time(NULL));
    
    // Show the welcome screen and ask the player if they want to continue
    std::cout << "Welcome to Tic Tac Toe! " <<std::endl<< std::endl;
    std::cout << "Would you like to play? Enter y for yes or n for no: " << std::endl;
    
    // Get the response, if no end the program
    response = read_response("y","n");
    if(response == "n")
        return 0;
    
    do
    {
        // Get the the user player number
        std::cout <<std::endl<< "Do you want to be player 1 or 2 (Player 1 goes first)?" << std::endl ;
        
        response = read_response("1","2");
        human_no = response == "1" ? 1 : 2;
        
        // Start a new game
        play_game(human_no);
        
        // Ask the player if they want to play again
        std::cout << "Do you want to play again? Enter y or n (y for yes / n for no): " << std::endl;
        response = read_response("y","n");
    }
    while(response == "y");
    
    return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// END OF main.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
