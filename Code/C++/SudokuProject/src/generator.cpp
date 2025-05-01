/**
 * @file generator.cpp
 * @brief Implementation of functions to generate random solvable Sudoku boards.
 *
 * This file contains logic and functions to, in order:
 * - Creates an empty Sudoku board. getEmptyBoard()
 * - Returns a shuffled vector. getShuffledVector()
 * - Randomly fills independent boxes of a Sudoku board to create a solvable Sudoku puzzle. fillBoardWithIndependentBox(int**)
 * - Randomly remove cells to create a solvable Sudoku puzzle. deleteRandomItems(int**, const int&)
 * - Creates Sudoku board and removes cells to create a solvable Sudoku puzzle. generateBoard(const int&)
 * 
 *
 * @authors
 * Antonio Devine, Andrew Voyez, Lizzy Boyd
 *
 * @date
 * April 25nd, 2025
 */

#include "../include/generator.h"
#include "../include/sudoku.h"
#include "../include/sudoku_io.h"
#include <random>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;



// Function to create empty 9x9 Sudoku boards using a matrix
int** getEmptyBoard() {

	//empty board
	int** board = new int*[9];
	
	//initalization of empty board
	for(int i = 0; i < 9; i++){
		board[i] = new int[9] {0, 0, 0, 0, 0, 0, 0, 0, 0};
	}
	
	//returning empty board
	return board;

}


// Function to create and randomly shuffle a vector
std::vector<int> getShuffledVector() {
	
	//initializes the vector
	vector<int> num = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	//gets random numbers to base the shuffle on
	random_device rd;
	mt19937 g(rd());

	//shuffle the vector around using <algorithm>
	shuffle(num.begin(), num.end(), g);

	return num;

}


// Function to randomly fill 3 independent boxes of a 9x9 Sudoku board using vectors
void fillBoardWithIndependentBox(int** BOARD) {
	/*
	* @param BOARD A 9x9 Sudoku board.
	*/
    
	//generate a 1 or a 2 to decide if it is going to generate a right horizontal or left horizontal fill
	random_device rd;
    	mt19937 gen(rd());
    	uniform_int_distribution<> dist(1, 2);
    	int random_number = dist(gen);

    	switch(random_number) {

        	//right horizontal
        	case 1:
            	//for loop to add i to each box
            	//so when accessing a box i will be added to it to move 3 rows/columns over
            	for(int i = 0; i < 9; i += 3) {

                	//index to access vector from 0 - 8
                	int index = 0;

                	//creates vector then shuffles it
                	vector<int> box;
                	box = getShuffledVector();

                	//for loop to access rows
                	for(int j = 0; j < 3; j++) {
                    		//for lopp to access columns
                   		for(int k = 0; k < 3; k++) {
                        		//takes the row and column then assigns a varible from the box vector to it
                        		BOARD[j + i][k + i] = box.at(index);
                        		index++;
                    		}
                	}
            	}
        	break;

        	//left horizontal
        	case 2:
            	//for loop to add i to each box
            	//so when accessing a box i will be added to it to move 3 rows/columns over
            	for(int i = 0; i < 9; i += 3) {

                	//index to access vector from 0 - 8
                	int index = 0;

                	//creates vector then shuffles it
               		vector<int> box;
                	box = getShuffledVector();

                	//for loop to access rows
                	for(int j = 0; j < 3; j++) {
                    		//for lopp to access columns
                    		for(int k = 0; k < 3; k++) {
                        		//takes the row and column then assigns a varible from the box vector to it
                        		BOARD[j + i][k + (6 - i)] = box.at(index);
                        		index++;
                   		}
                	}
            	}
        	break;
    	}//end of switch

}


// Function to randomly delete 'n' items from a 9x9 Sudoku board using bitsets
void deleteRandomItems(int** BOARD, const int& n) {
	/*
	 * @param BOARD A 9x9 Sudoku board.
	 * @param n The number of cells to delete (should be between 1 and 81).
	 */
	
	//conditionals to check if n & board are valid
	if(n < 1 || n > 81) return;
	    
		for(int t = 0; t < 9; t++){
	        	for(int i = 0; i < 9; i++){
	            		if(!BOARD[t][i]) return;
	        	}
	    	}
	
	int index = 0;
	vector<int> UsedNums1, UsedNums2;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 8);
	
	while(index != n) {
		//randomly generate numbers from 0 to 8
		int random_number1 = dist(gen), random_number2 = dist(gen);
	
	        //flag to see if the coordinates have been used
	        bool NumsUsed = false;
	
	        //for loop to check each index of each vector
	        for(int i = 0; i <UsedNums1.size();i++) {
	        	if(UsedNums1.at(i) == random_number1 && UsedNums2.at(i) == random_number2) {
	        	NumsUsed = true;
	                break;
	            	}
	        }
	
	        //if none of the random numbers were used, set the coordinates to 0
	        if(NumsUsed == false) {
	            BOARD[random_number1][random_number2] = 0;
	            UsedNums1.push_back(random_number1);
	            UsedNums2.push_back(random_number2);
	            index++;
	        }
	        else {
	            continue;
	        }
    	}//end of while
	
}


// Function to create an empty 9x9 Sudoku board and randomly delete 'empty_boxes' amount of items
int** generateBoard(const int& empty_boxes){
	/*
     	 * @param empty_boxes The number of cells to delete (should be between 1 and 81).
     	 */
	
	//empty board
	int** mat1 = getEmptyBoard();
	
	//board filled w independent boxes
	fillBoardWithIndependentBox(mat1);
	
	//solve the board after generating random #s
	solve(mat1, false);
	
	//board with deleted elements
	deleteRandomItems(mat1, empty_boxes);
	
	//returning generated board with specified empty slots
	return mat1;

}
