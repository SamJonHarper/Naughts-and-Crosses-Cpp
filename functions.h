//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// functions.h
// 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef FUNCTIONS_H  //necessary for multiple inclusion of this file in a source file
#define FUNCTIONS_H
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// #includes
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Constant Definitions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

const char X_CHAR = 'X'; // The character to use for X
const char O_CHAR = 'O'; // The character to use for O
const char JUNK_CHAR = '_'; // The character to use during calculation for blocking moves
const char BLANK_CHAR = ' '; // The character used for empty spaces

const unsigned PLACE_COUNT = 9;   // The number of spaces on the field 3x3
const unsigned ROW_LENGTH = 3;   // The number of spaces on each row
const unsigned COL_LENGTH = 3;   // The number of spaces in each column

const unsigned CORNER_COUNT = 4;  // The number of corners on the field
const unsigned SIDE_COUNT = 4;  // The number of sides on the field

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Game_Status{}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

enum Game_status
{
    GAME_ONGOING = 0,  // Status code that means the game is still active
    GAME_DRAW ,        // Status code that means the game was a draw
    GAME_X_WON,        // Status code that means the player using the X won
    GAME_O_WON         // Status code that means the player using the O won
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Place{}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

enum Place
{
    TOP_LEFT = 0,      //A1 in board
    TOP_MIDDLE,        //A2 in board
    TOP_RIGHT,         //A3 in board
    LEFT_MIDDLE,       //B1 in board
    CENTER,            //B2 in board
    RIGHT_MIDDLE,      //B3 in board
    BOTTOM_LEFT,       //C1 in board
    BOTTOM_MIDDLE,     //C2 in board
    BOTTOM_RIGHT       //C3 in board
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// declarations
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void print_field(std::vector<char>& field);
void play_game(const unsigned human_no);
void copy_field(std::vector<char>& field, std::vector<char>& duplicate, const char piece);
void human_move(std::vector<char>& field, const char human_char);
void copy_field_exact(std::vector<char>& field, std::vector<char>& duplicate);
void make_move(std::vector<char>& field, const unsigned row, const unsigned col, const char piece);
void pc_move(std::vector<char>& field, const char pc_char, const char human_char);

Game_status game_status(std::vector<char>& field);
int opposite_corner(std::vector<char>& field, const char piece);
int choose_side(std::vector<char>& field);
int choose_corner(std::vector<char>& field);
int get_forker(std::vector<char>& field, const char pc_char);
int get_finisher(std::vector<char>& field, const char pc_char);

bool is_open_place(std::vector<char>& field, const unsigned row, const unsigned col);
bool is_field_clear(std::vector<char>& field);
bool is_open_index(std::vector<char>& field, const unsigned index);
bool has_fork(std::vector<char>& field, const char piece);
bool has_player_won(std::vector<char>& field, const char piece);
bool has_drawn(std::vector<char>& field);

std::string read_response(const std::string& option1, const std::string& option2);
std::string read_move(std::vector<char>& field);

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// END OF functions.hpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
