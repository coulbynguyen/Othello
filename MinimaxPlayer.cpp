/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 *      Author: Coulby Nguyen
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;
using namespace std;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

int MinimaxPlayer::utility(OthelloBoard* board){
   //Get the player 1 score

   int scorep1 = board->count_score(board->get_p1_symbol());

   //Get the player 2 score
   int scorep2 = board->count_score(board->get_p2_symbol());
   if(symbol == 'X'){

      //If the symbol is X then return player 1 score minus player 2 score
      return scorep1 - scorep2;
   }
   else{
      //If the symbol is O then return player 2 score minus player 1 score
      return scorep2 - scorep1;
   }
}

vector<OthelloBoard*> MinimaxPlayer::succfn(char c, OthelloBoard* board){
   vector<OthelloBoard*> succBoards;
  
   for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
	 if(board->is_legal_move(i,j,c)){
	    //If the board can has a legal move with coordinates (i,j) and symbol c
	    //Then it is added to the list of successor boards
	    //And its move coordinate (i,j) is saved as row and col
	    succBoards.push_back(new OthelloBoard(* board));
	    succBoards.back()->play_move(i,j,c);
	    succBoards.back()->set_col(i);
	    succBoards.back()->set_row(j);
	 }
      }
   }

   return succBoards;

}

void MinimaxPlayer::menu(OthelloBoard* board, int& col, int& row){

   if(symbol == board->get_p1_symbol()){
      //If the symbol of the minimax player is x then it calls this function with these parameters
      maxMinimax(board,  col, row, 'X');
   }
   else{
      //If the symbol of the minimax player is o then it calls this function with these parameters   
      maxMinimax(board, col, row, 'O');
   }
}

int MinimaxPlayer::maxMinimax(OthelloBoard* board, int& col, int& row, char c){
   //The lowest max can be is int min
   int max = -32767;
   int a = 0;
   int b = 0;

   vector<OthelloBoard*> nextBoards;

   if(c == 'X'){
      //If the char c is x it finds all the posible successor boards from x
      nextBoards = succfn('X', board);
   }
   else if(c == 'O'){
      //If the char c is o it finds all the possible successor boards from x
      nextBoards = succfn('O', board);
   }
   //If there are no possible boards from that move it calls the utility function since there are no possible moves/boards
   if(nextBoards.size() == 0){
      return utility(board); 
   }

   //This for loop goes through each of the possible successor boards and compares the min value to the current max value of the board
   for(int i = 0; i < nextBoards.size(); i++){
      if(max < minMinimax(nextBoards[i], col, row, c)){
	 max = minMinimax(nextBoards[i], col, row, c);
	 a = nextBoards[i]->get_col();
	 b = nextBoards[i]->get_row();
      }
   }
   col = a;
   row = b;
   return max;
}

int MinimaxPlayer::minMinimax(OthelloBoard* board, int& col, int& row, char c){
   //we set the min value to the maxinmum int value
   int min = 32767;
   int a = 0;
   int b = 0;

   vector<OthelloBoard*> nextBoards;

   if(c == 'X'){
      //If the char c is x it finds all the possible successor boards from x
      nextBoards = succfn('X', board);
   }
   else if(c == 'O'){
      //If the char c is o it finds all the possible successor boards from o
      nextBoards = succfn('O', board);
   }

   //If there are no possible boards from that move it calls the utility function since there are no possible moves/boards
   if(nextBoards.size() == 0){
      return utility(board);
   }

   //This loop goes through each of the possible successor boards and compares the min value with the successor board min value
   for(int i = 0; i < nextBoards.size(); i++){
      if(min > minMinimax(nextBoards[i], col, row, c)){
	 min = minMinimax(nextBoards[i], col, row, c);
	 a = nextBoards[i]->get_col();
	 b = nextBoards[i]->get_row();
      }
   }
   col = a;
   row = b;
   return min;
}


void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
   // To be filled in by you
   // this function calls the menu function to determine which symbol to call the minimax fucntion with
   menu(b, col, row);
}

MinimaxPlayer* MinimaxPlayer::clone() {
   MinimaxPlayer* result = new MinimaxPlayer(symbol);
   return result;
}

























