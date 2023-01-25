// CELLULAR AUTOMATA, motivated in the class.
//
// AUTHOR: Abhigyan Mehrotra and Vishal Paudel
// DATE: 24 January 2023
//
// NOTE: If you have pass in 3 as state len and 8 as the initial state,
//          the code will misbehave(Why?).

#include <iostream>
#include <stdio.h>                              // for printing and inputs
#include <map>                                  // dictionaries in c plus plus

class Game
{

public:

    int rule_num;                               // the encoding for the rule

    int state_len;                              // the number of cell blocks
    int frame_len;                              // len of frame for the rules

    // CONSTRUCTOR ---------------------------
    Game( int rule_num, int state_len, int frame_len, int init_state );

    void update_state();                        // The main interface
    void print_state();                         // The print interface

private:
    int cur_state;                              // The encoded state of game
    std::map< int, int > rules;                 // The Rules

    // PRIVATE METHODS --------------------------------------------------------
    std::map< int, int >
        gen_rule_book( int rule_num );          // generate rules from rule num

    int get_frame( int index );                 // current frame
    int execute_frame( int frame );             // value from rule on cur_frame
    void update_index( int index, int value );  // update index

    void print_binary( int num, int len );      // helper function

};


// CONSTRUCTOR ----------------------------------------------------------------
Game::Game( int rule_num, int state_len, int frame_len, int init_state )
{
    this->rule_num = rule_num;

    this->state_len = state_len;
    this->frame_len = frame_len;
    this->cur_state = init_state;

    this->rules =
        this->gen_rule_book( rule_num );    // The rule dict
}


// The main interface  --  updates the state once
void Game::update_state()
{
    for( int index = 0; index < this->state_len; index++ )
    {
        int frame = this->get_frame( index );
        int value = this->execute_frame( frame );

        this->update_index( index, value );
    }

    return;
}


// The print interface
void Game::print_state()
{
    this->print_binary( this->cur_state, this->state_len );
    return;
}


// generate rules from rule num  --  return rule dictionary from rule num
std::map<int, int> Game::gen_rule_book( int rule_num )
{

    std::map< int, int > rule;
    for( int i = 0; i < ( 1 << this->frame_len ); i++ )
    {
        rule[ i ] = ( rule_num & 1 );
        rule_num = rule_num >> 1;
    }

    return rules;
}


// current frame  --  returns the frame for the current index
int Game::get_frame( int index )
{
    int shift = ( state_len - ( index + frame_len / 2 + 1 ) );
    int shifted;
    if( shift < 0 )
    {
        shifted = (cur_state << -1 * shift);
    }
    if( shift >= 0 )
    {
        shifted = (cur_state >> shift);
    }
    return shifted & ((1 << frame_len) - 1);
}


// value from rules on cur_frame  --  checks rules; returns value for cur_frame
int Game::execute_frame( int frame )            // NOT IMPLEMENTED ------------
{
    if( this->rules.find( frame ) != rules.end() )
    {
        return this->rules[ frame ];
    }
    else {
        this->print_binary( frame, this->frame_len );
        printf( "\nFRAME NOT FOUND!\n" );
    }
    return 0;
}


// update index  --  updates the index of the state with value
void Game::update_index( int index, int value )
{
    this->cur_state |= ( value << ( this->state_len - ( index + 1 ) ) );
    return;
}


// helper function  --  prints out a binary number to a specified len
void Game::print_binary( int num, int len )
{

    int index = 0;
    while( index < len )
    {
        printf( "%d", num & 1 );
        num >>= 1;
        index++;
    }
    printf( "\n" );

    return;
}


int main()
{
    std::cout << "Here";

    int rule_numb = 30;
    int array_length = 8;
    int frame_size = 3;
    int curr_state = 0b00111010;

    Game rule_30 = Game(array_length,frame_size,rule_numb,curr_state);
    Game *rule_30_ptr = &rule_30;

    int iterations = 0, num_iter = 10;
    while( iterations < num_iter )
    {
        rule_30_ptr->print_state();
        rule_30_ptr->update_state();

        iterations++;
    }

    return 0;
}
