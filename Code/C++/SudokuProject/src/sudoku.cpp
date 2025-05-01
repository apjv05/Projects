/**
 * @file sudoku.cpp
 * @brief Implementation of functions for core Sudoku board solving and validation.
 *
 * This file contains logic and functions to, in order:
 * - Returns if a value is valid at some cell. isValid(int**, const int&, const int&, const int&)
 * - Solves a Sudoku board recursively. solveBoard(int**, const int&, const int&)
 * - Returns next cell with the lowest potentially valid values. findNextCell(int**)
 * - Solves a Sudoku board efficiently using recursion. solveBoardEfficient(int**)
 * - Decides to solve a Sudoku board efficiently or not. solve(int**, const bool&)
 * 
 *
 * @authors
 * Antonio Devine, Andrew Voyez, Lizzy Boyd
 *
 * @date
 * April 25nd, 2025
*/

#include "../include/sudoku.h"
#include <iostream>
#include <tuple>

using namespace std;



// Function to validate specific numbers in a board cell
bool isValid(int** BOARD, const int& r, const int& c, const int& k){
       /*
	* @param BOARD A 9x9 Sudoku board.
  	* @param r The row of a specific cell.
    	* @param c The column of a specific cell.
      	* @param k The number to check if valid in some cell.
	*/
	
    	// Check if 'k' already exists in the same row or column
    	for (int i = 0; i < 9; i++){
        	if (k == BOARD[r][i] || k == BOARD[i][c])
            		return false;  // Invalid placement
    	}

    	// Determine starting indices for the 3x3 subgrid
    	int startRow = 3 * (r / 3);
    	int startCol = 3 * (c / 3);

    	// Check if 'k' exists in the 3x3 subgrid
    	for (int i = startRow; i < startRow + 3; i++){
        	for (int j = startCol; j < startCol + 3; j++){
            		if (k == BOARD[i][j])
                		return false;  // Invalid placement
        	}
    	}

    	return true;  // Placement is valid
	
}


// Function to recursively fill each cell until a Sudoku board is solved
bool solveBoard(int** BOARD, const int& r, const int& c){
       /*
	* @param BOARD A 9x9 Sudoku board.
  	* @param r The row of a specific cell.
    	* @param c The column of a specific cell.
	*/
	
    	// If we've reached beyond the last row, the board is solved
    	if (r == 9)
        	return true;

    	// Move to the next row if we've reached the end of the current row
    	if (c == 9)
        	return solveBoard(BOARD, r + 1, 0);

    	// Skip already filled cells and move to the next column
    	if (BOARD[r][c] != 0)
        	return solveBoard(BOARD, r, c + 1);

    	// Try placing numbers 1 to 9 in the current empty cell
    	for (int k = 1; k <= 9; k++){
        	if (isValid(BOARD, r, c, k)){
            		BOARD[r][c] = k;  // Place number 'k'

            		// Recursively attempt to solve the rest of the board
            		if (solveBoard(BOARD, r, c + 1))
                		return true;  // Found a valid solution

            		// Backtrack: Remove the number if no solution is found
            		BOARD[r][c] = 0;
        	}
    	}//end of for

    	// Trigger backtracking if no valid number can be placed
    	return false;

}


// Function to find the next cell with the fewest potential valid options using tuples
tuple<int, int, int> findNextCell(int** BOARD) {
       /*
	* @param BOARD A 9x9 Sudoku board.
	*/
	
    	//counter for the current smallest amount of valid options
    	//s_v_i starts at 10 because every number MUST have a lower potential amount of values that can be stored
    	int smallest_valid_index = 10;
    
    	//storage for the cell with the lowest valid options
    	int smallest_row = -1;
    	int smallest_column = -1;
    
    	//* sizeof(BOARD)/sizeof(BOARD[0]) AND sizeof(BOARD[0])/sizeof(BOARD[0][0]) * are not valid just write 9
    	//outer for loop for the iteration of the rows of the matrix
    	for(int i = 0; i < 9; i++){
    
    		//inner for loop for the iteration of the columns of the matrix
    		for(int j = 0; j < 9; j++){
    
    			if(BOARD[i][j] == 0){
    
    				//in-scope counter to tally current # of valid options
    				int enumarator = 0;
    			
    				for(int a = 1; a <= 9; a++){
    				
    					//if the # at the position BOARD[i][j] is valid
    					if(isValid(BOARD, i, j, a)){
    						enumarator++;
    					}
    
    				}
    
    				//redundancy return (If there is only 1 valid option for some cell, return that one option)
    				if(enumarator==1){
    					return {i,j,enumarator};
    				}			
    
    				//if there is a smaller # of valid options, as tracked by enumarator, than the current smallest amount counted
    				if(enumarator < smallest_valid_index){
    					smallest_valid_index = enumarator;
    					smallest_row = i;
    					smallest_column = j;
    				}
    			}
    		}//end of for
    	}//end of for
    
    	return {smallest_row, smallest_column, smallest_valid_index};

}


// Function to recursively backtrack to optimally solve a Sudoku board using the MRV heuristic
bool solveBoardEfficient(int** BOARD){
	/*
	 * @brief Efficiently solves the Sudoku board using backtracking and the MRV heuristic.
	 *
	 * This function uses a recursive backtracking approach combined with the Minimum Remaining Value (MRV)
	 * heuristic to optimize the solving process by always selecting the cell with the fewest valid options.
  	 *
     	 * @param empty_boxes The number of cells to delete (should be between 1 and 81).
     	 */
	
    	//initilization
    	auto [smallest_row, smallest_column, smallest_valid_index] = findNextCell(BOARD);

    	if(smallest_row == -1) return true;

    	for(int i = 1; i < 10; i++) {
        	if(isValid(BOARD, smallest_row, smallest_column, i)) {
            		//if i is valid then we set our target cell to i
            		BOARD[smallest_row][smallest_column] = i;

            		//we then recursively check if i will lead to
            		//a solution with the rest of the board
            		if(solveBoardEfficient(BOARD)) return true;

            		//if the number we placed did not work, then we set it to 0
            		//and try the next number in the for loop
            		BOARD[smallest_row][smallest_column] = 0;
        	}
    	}//end of for loop
	
    	//once the for loop finishes and we conclude that every possible
    	//number did not work in this cell, we return false to change a previous
    	//number thus, repeating the proccess until the whole board is solved
    	return false;

}


// Function to solve board either normally or efficiently
bool solve(int** BOARD, const bool& efficient){
       /*
	* @param BOARD A 9x9 Sudoku board.
 	* @param efficient Option to solve board efficiently.
	*/

	//
	if(efficient){
		return solveBoardEfficient(BOARD);
    	}	
    	return solveBoard(BOARD,0,0);
    
}
