//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// functions.cpp
// This functions.cpp file will cover all function implementation
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "functions.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// has_player_won()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool has_player_won(std::vector<char>& field, const char piece) // Check if a specific player has won the game.
{
    bool chain;
    unsigned offset;
    
    // Check horizontal chains
    for(int row = 0; row < ROW_LENGTH; row++)
    {
        chain  = true;
        offset = row * COL_LENGTH;
        for(int col = 0; col < COL_LENGTH; col++)
            if(field[offset + col] != piece)
            {
                chain = false;
                break;
            }
        
        // If unbroken chain was found, the player has won
        if(chain)
            return true;
    }
    
    // Check vertical chains
    for(int col = 0; col < COL_LENGTH; col++)
    {
        chain  = true;
        for(int row = 0; row < ROW_LENGTH; row++)
        {
            offset = row * COL_LENGTH;
            
            if(field[offset + col] != piece)
            {
                chain = false;
                break;
            }
        }
        
        // If unbroken chain was found, the player has won
        if(chain)
            return true;
    }
    
    // Check top-left to bottom-right chain
    chain = true;
    for(int row = 0; row < ROW_LENGTH; row++)
    {
        offset = row * COL_LENGTH;
        
        if(field[offset + row] != piece)
        {
            chain = false;
            break;
        }
    }
    
    if(chain) // If unbroken chain was found, the player has won
        return true;
    
    // Check top-right to bottom-left chain
    chain = true;
    for(int row = 0; row < ROW_LENGTH; row++)
    {
        offset = row * COL_LENGTH;
        
        if(field[offset + (COL_LENGTH - (row + 1))] != piece)
        {
            chain = false;
            break;
        }
    }
    
    return chain;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// has_fork()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool has_fork(std::vector<char>& field, const char piece) // Check if a specific player has a fork on the field.
{
    std::vector<char> duplicate(PLACE_COUNT);
    
    copy_field_exact(field, duplicate);
    
    // Find a fork by verifying that there are two
    // finishing moves for the given piece on the field.
    int index = get_finisher(duplicate, piece);
    if(index == -1)
        return false;
    
    // If first was found, replace its location with junk
    // and get a finisher again
    duplicate[index] = JUNK_CHAR;
    index            = get_finisher(duplicate, piece);
    
    return index != -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// is_open_index()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool is_open_index(std::vector<char>& field, unsigned index) // Check if a space in the field is empty.
{
    return field[index] == BLANK_CHAR;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// is_field_clear()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool is_field_clear(std::vector<char>& field) // Check if the entire field is clear.
{
    for(int i = 0; i < PLACE_COUNT; i++)
        if(field[i] != BLANK_CHAR)
            return false;
    
    return true;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// copy_field_exact()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void copy_field_exact(std::vector<char>& field, std::vector<char>& duplicate) // Copy the field.
{
    for(int i = 0; i < PLACE_COUNT; i++)
        duplicate[i] = field[i];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// get_finisher()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int get_finisher(std::vector<char>& field, const char pc_char) // Determine if there is a finishing move, and return it if there is.
{
    std::vector<char> duplicate(PLACE_COUNT);
    
    // Replace empty fields with pc_char, one at a time and see which
    // replacement creates a winning situation.
    
    copy_field_exact(field, duplicate);
    for(int i = 0; i < PLACE_COUNT; i++)
        if(is_open_index(field, i))
        {
            duplicate[i] = pc_char;
            if(has_player_won(duplicate, pc_char)) // A winning move has been found
                return i;
            
            duplicate[i] = BLANK_CHAR;
        }
    
    return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// get_forker()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int get_forker(std::vector<char>& field, const char pc_char) // Determine if there is a forking move, and return it if there is.
{
    std::vector<char> duplicate(PLACE_COUNT);
    
    // Replace empty fields with pc_char, one at a time and see which
    // replacement creates a fork situation.
    
    copy_field_exact(field, duplicate);
    for(int i = 0; i < PLACE_COUNT; i++)
        if(is_open_index(field, i))
        {
            duplicate[i] = pc_char;
            if(has_fork(duplicate, pc_char)) // A forking move has been found
                return i;
            
            duplicate[i] = BLANK_CHAR;
        }
    
    return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// choose_corner()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int choose_corner(std::vector<char>& field) // Randomly select one of the corners.
{
    unsigned list[CORNER_COUNT];
    unsigned count =0;
    
    // Add all blank corners to the list
    if(is_open_index(field, TOP_LEFT))
        list[count++] = TOP_LEFT;
    
    if(is_open_index(field, TOP_RIGHT))
        list[count++] = TOP_RIGHT;
    
    if(is_open_index(field, BOTTOM_LEFT))
        list[count++] = BOTTOM_LEFT;
    
    if(is_open_index(field, BOTTOM_RIGHT))
        list[count++] = BOTTOM_RIGHT;
    
    // If all corners are occupied, quit
    if(count == 0)
        return -1;
    
    // Generate a random selection
    unsigned selection = rand() % count;
    return list[selection];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// choose_side()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int choose_side(std::vector<char>& field) // Randomly select one of the middle side places.
{
    unsigned list[SIDE_COUNT];
    unsigned count = 0;
    
    // Add all blank side middles to the list
    if(is_open_index(field, LEFT_MIDDLE))
        list[count++] = LEFT_MIDDLE;
    
    if(is_open_index(field, RIGHT_MIDDLE))
        list[count++] = RIGHT_MIDDLE;
    
    if(is_open_index(field, TOP_MIDDLE))
        list[count++] = TOP_MIDDLE;
    
    if(is_open_index(field, BOTTOM_MIDDLE))
        list[count++] = BOTTOM_MIDDLE;
    
    // If all corners are occupied, quit
    if(count == 0)
        return -1;
    
    // Generate a random selection
    unsigned selection = rand() % count;
    return list[selection];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// opposite_corner()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int opposite_corner(std::vector<char>& field, const char piece) // Select a corner opposite to one occupied by the given piece.
{
    if(field[TOP_LEFT] == piece && is_open_index(field, BOTTOM_RIGHT))
        return BOTTOM_RIGHT;
    
    else if(field[TOP_RIGHT] == piece && is_open_index(field, BOTTOM_LEFT))
        return BOTTOM_LEFT;
    
    else if(field[BOTTOM_LEFT] == piece && is_open_index(field, TOP_RIGHT))
        return TOP_RIGHT;
    
    else if(field[BOTTOM_RIGHT] == piece && is_open_index(field, TOP_LEFT))
        return TOP_LEFT;
    
    else
        return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// pc_move()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void pc_move(std::vector<char>& field, const char pc_char, const char human_char) // Let the PC make a move.
{
    int index;
    
    // 1) Make the winning move if possible
    index = get_finisher(field, pc_char);
    if(index != -1)
    {
        field[index] = pc_char;
        return;
    }
    
    // 2) Block any impending winning move
    index = get_finisher(field, human_char);
    if(index != -1)
    {
        field[index] = pc_char;
        return;
    }
    
    // 3) Create a fork
    index = get_forker(field, pc_char);
    if (index != -1)
    {
        field[index] = pc_char;
        return;
    }
    
    // 4 - Option 2) Block any impending forking move
    index = get_forker(field, human_char);
    if(index != -1)
    {
        field[index] = pc_char;
        
        int index_0 = get_finisher(field, pc_char);  // check if this move can create a finishing move, forcing human to block it
        if (index_0 != -1)   // this move is ok since it forces the human to block PC's finishing move
        {
            field[index_0] = human_char;
            
            int index_1 = get_finisher(field, human_char); // check if the human has a move to win
            
            if (index_1 == -1)   // this move is ok since it does not create possibilities to win for human
            {
                // Undo the human move to block finishing move
                field[index_0] = BLANK_CHAR;
                return;
            }
            else
            {
                field[index_1] = pc_char;
                int index_2 = get_finisher(field, human_char); // check if the human has another move to win
                
                field[index_0] = BLANK_CHAR;
                field[index_1] = BLANK_CHAR;
                if (index_2 == -1)  // this move is ok since the user cannot win
                    return;
            }
            
        }
        
        // 4 - Option 1) If blocking a fork creates an opportunity for another fork, find
        //               one of the second fork's finishing moves and block it.
        
        int index2 = get_forker(field, human_char);
        if(index2 != -1) // Second fork found
        {
            field[index2] = human_char;                      // Create the second fork
            int index3        = get_finisher(field, human_char); // Get that fork's first finisher
            field[index3] = pc_char;                         // Block that finisher
            
            // Undo first fork block and second fork creation.
            field[index]  = BLANK_CHAR;
            field[index2] = BLANK_CHAR;
        }
        return;
    }
    
    // 5) If first move, choose a corner. Otherwise, play center if it is open.
    if(is_field_clear(field)) // This is the first move of the game
    {
        index        = choose_corner(field);
        field[index] = pc_char;
        return;
    }
    
    else if(is_open_index(field, CENTER)) // The center is open
    {
        field[CENTER] = pc_char;
        return;
    }
    
    // 6) Play the opposite corner
    index = opposite_corner(field, human_char);
    if(index != -1)
    {
        field[index] = pc_char;
        return;
    }
    
    // 7) Play any corner
    index = choose_corner(field);
    if(index != -1)
    {
        field[index] = pc_char;
        return;
    }
    
    // 8) Play any empty middle of a side
    index        = choose_side(field);
    field[index] = pc_char;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// make_move()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void make_move(std::vector<char>& field, const unsigned row, const unsigned col, const char piece) // Perform the given move using the specified character.
{
    field[row * COL_LENGTH + col] = piece;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// is_open_place()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool is_open_place(std::vector<char>& field, const unsigned row, const unsigned col) // Check if a space in the field is empty.
{
    return field[row * COL_LENGTH + col] == BLANK_CHAR;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// read_move()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

std::string read_move(std::vector<char>& field) // Get a valid move from the player.
{
    std::string move;
    bool valid_move;
    
    std::cout<<std::endl <<" Enter your next move: " << std::endl;
    valid_move = false;
    
    do
    {
        // Get the move
        
        std::cin >> move;
        
        // Change all characters to upper case
        for(int i = 0; i < move.size(); i++)
            move[i] = toupper(move[i]);
        
        // Make sure the move is valid
        
        if(move.size() != 2)
            std::cout <<std::endl<< " The move is invalid. Enter exactly two charactes: " << std::endl;
        else if(move[0] < 'A' || 'C' < move[0])
            std::cout <<std::endl<< " The move is invalid. First character must be A-C: " << std::endl;
        else if(move[1] < '1' || '3' < move[1])
            std::cout <<std::endl<< " The move is invalid. Second character must be 1-3: " << std::endl;
        else if(!is_open_place(field, move[0] - 'A', move[1] - '1'))
            std::cout <<std::endl<< " The move is invalid. The position is not open: " << std::endl;
        else
            valid_move = true;
        
    }while(!valid_move);
    
    return move;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// human_move()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void human_move(std::vector<char>& field, const char human_char) // Let the human move.
{
    
    // Read the next player move
    std::string move = read_move(field);
    unsigned row  = move[0] - 'A';
    unsigned col  = move[1] - '1';
    
    // Place the marker
    make_move(field, row, col, human_char);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// copy_field()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void copy_field(std::vector<char>& field, std::vector<char>& duplicate, const char piece) // Copy the field and make all empty spaces the specified piece.
{
    for(int i = 0; i < PLACE_COUNT; i++)
        if(field[i] == BLANK_CHAR)
            duplicate[i] = piece;
        else
            duplicate[i] = field[i];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// has_drawn()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool has_drawn(std::vector<char>& field) // Check if a draw has occurred. A draw occurs when all chains have become impossible.
{
    std::vector<char> duplicate(PLACE_COUNT);
    
    // Check if X can still win
    copy_field(field, duplicate, X_CHAR);
    if(has_player_won(duplicate, X_CHAR))
        return false;
    
    // Check if O can still win
    copy_field(field, duplicate, O_CHAR);
    if(has_player_won(duplicate, O_CHAR))
        return false;
    
    return true;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// game_status()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Game_status game_status(std::vector<char>& field) // Determine the status of the game.
{
    if(has_player_won(field, X_CHAR))
        return GAME_X_WON;
    else if(has_player_won(field, O_CHAR))
        return GAME_O_WON;
    else if(has_drawn(field))
        return GAME_DRAW;
    else
        return GAME_ONGOING;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// print_field()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void print_field(std::vector<char>& field)
{
    unsigned offset;
    char row_label;
    
    std::cout<<std::endl;
    
    row_label = 'A';
    for(int row = 0; row < ROW_LENGTH; row++)
    {
        offset = row * COL_LENGTH;
        
        std::cout<<" "<<row_label<<"   "<<field[offset + 0]<<" | "<< field[offset + 1]<<" | "<<field[offset + 2]<<std::endl;
        
        // If last row, show digits. Otherwise, print a horizontal divider
        if(row+1 == ROW_LENGTH)
            std::cout<<std::endl<<"     1   2   3 "<<std::endl;
        else
            std::cout<<"    -----------"<<std::endl;
        
        // Change the row label to the next letter
        row_label += 1;
    }
    
    std::cout<<std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// plau_game()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void play_game(const unsigned human_no)
{
    std::vector<char> field(PLACE_COUNT);
    bool is_pc_next;
    char human_char;
    char pc_char;
    unsigned status;
    
    // Set the player and the pc pieces
    if(human_no == 1)
    {
        human_char = X_CHAR;
        pc_char    = O_CHAR;
        is_pc_next = false;
    }
    else
    {
        human_char = O_CHAR;
        pc_char    = X_CHAR;
        is_pc_next = true;
    }
    
    // Initialize the field of place
    for(int i = 0; i < PLACE_COUNT; i++)
        field[i] = BLANK_CHAR;
    
    // If the PC goes first, let it move before printing the field
    if(is_pc_next)
    {
        pc_move(field, pc_char, human_char);
        is_pc_next = false;
    }
    
    // Print the field of play
    print_field(field);
    
    do
    {
        // Get the next move
        if(is_pc_next)
            pc_move(field, pc_char, human_char);
        else
            human_move(field, human_char);
        
        // Print the field of play
        print_field(field);
        
        // Flip the indicater of who is next
        
        is_pc_next = !is_pc_next;
        
        // Get the game status
        status = game_status(field);
        
    }while(status == GAME_ONGOING);
    
    // Print the final status of the game
    
    if(status == GAME_DRAW)
        std::cout<<" The game ended in a draw."<<std::endl;
    else if(status == GAME_X_WON)
    {
        if(pc_char == X_CHAR)
            std::cout<<"  The PC won the game."<<std::endl;
        else
            std::cout<<" You won the game."<<std::endl;
    }
    else
    {
        if(pc_char == O_CHAR)
            std::cout<<" The PC won the game."<<std::endl;
        else
            std::cout<<" You won the game."<<std::endl;
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// read_response()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

std::string read_response(const std::string& option1, const std::string& option2)
{
    std::string response;
    
    std::cin >> response;
    while(response != option1 && response != option2)
    {
        std::cout<<" Enter only "<<option1.c_str()<<" or "<<option2.c_str()<<": ";
        std::cin >> response;
    }
    
    return response;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// END OF functions.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
