/**
 * @file sudoku_io.cpp
 * @brief Implementation of functions to handle input/output stream related operations.
 *
 * This file contains logic and functions to, in order:
 * - Prints a color coded Sudoku board. printBoard(int**, const int&, const int&, int)
 * - Transforms the 2D integer array representing the Sudoku board into a single string format. boardToString(int**, string&)
 * - Persists the current state of a Sudoku board into a text file at the specified location. writeSudokuToFile(int**, const string&)
 * - Modifies a given string by substituting all instances of a particular character with another. replaceCharacter(string&, char, char)
 * - Parses a string to find and collect all numerical digits, storing them as integers in a vector. extractNumbers(const string&, vector<int>&)
 * - Populates a given Sudoku board (2D integer array) with values from a provided integer vector. fillBoard(const vector<int>&, int**)
 * - Loads a Sudoku puzzle from a specified file, interpreting its contents into a 2D integer array. readSudokuFromFile(const string&)
 * - Verifies if the current arrangement of numbers in a Sudoku board adheres to all Sudoku rules. checkIfSolutionIsValid(int**)
 * - Scans a specified directory and returns a list of the full file paths of all regular files found within. getAllSudokuInFolder(const string&)
 * - Generates a specified quantity of Sudoku puzzles with a defined difficulty (number of empty cells) and saves them to a designated directory with a given filename prefix. createAndSaveNPuzzles(const int&, const int&, const string&, const string&)
 * - Shows a visual representation of the progress of a task in the console, customizable by width. displayProgressBar(int, int, int=50) (50 is the default 3rd parameter)
 * - Reads Sudoku puzzles from a source directory, attempts to solve them, and saves the valid solutions to a destination directory with a specified filename prefix. solveAndSaveNPuzzles(const int&, const string&, const string&)
 * - Creates an independent copy of a given Sudoku board in memory, ensuring modifications to the copy do not affect the original. deepCopyBoard(int**)
 * - Conducts a performance comparison between two different Sudoku solving algorithms by running them on a set of generated puzzles and reporting their execution times and success rates. compareSudokuSolvers(const int&, const int&)
 *   
 *
 * @authors
 * Antonio Devine, Andrew Voyez, Lizzy Boyd
 *
 * @date
 * April 25nd, 2025
 */

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <iomanip>  // For formatted output

#include "../include/generator.h"
#include "../include/sudoku_io.h"
#include "../include/utils.h"
#include "../include/sudoku.h"

using namespace std;
using namespace std::chrono;



// Function to check if input value 'k' is valid and print color coded Sudoku board using ANSI
void printBoard(int** BOARD, const int& r, const int& c, int k){
       /*
    	* @param BOARD A 9x9 Sudoku board.
    	* @param r The row value of a Sudoku cell.
    	* @param c The column value of a Sudoku cell.
    	* @param k The input value to try at BOARD[r][c].
	*/
		    
	if(BOARD[r][c]>0) k = 0;

    	for (int i = 0; i < 9; i++){
        	for (int j = 0; j < 9; j++){
			
	            	string board_piece;
	            	if (BOARD[i][j] == 0) board_piece = "\x1B[93m-\x1B[0m"; // Yellow
	                
	            	else board_piece = to_string(BOARD[i][j]); // White

		        //if the for loop is at BOARD[r][c] and the cell is empty
		        if ((i == r && j == c) && k != 0){
		        	//if the chosen int, k, is valid in position BOARD[r][c] then it is green
	                	if (isValid(BOARD, r, c, k)){
					board_piece = "\x1B[32m" + to_string(k) + "\x1B[0m"; // Green
		        	}else{
		               		board_piece = "\x1B[31m" + to_string(k) + "\x1B[0m"; // Red
		        	}
		        }
	            
	            	cout << board_piece;
	            
	            	if (j == 2 || j == 5){ 
	                	cout << " | ";
	            	}else{ 
	                	cout << " ";
	            	}
	        }//end of for
	        if (i == 2 || i == 5){
	            cout << endl;
	            for (int l = 0; l < 21; l++) cout << ".";
	        }
	        cout << endl;
	
	}//end of for 
	
}


// Function to print Sudoku board (Create string version of Sudoku board)
void boardToString(int** BOARD, string &content){
       /*
	* @param BOARD A 9x9 Sudoku board.
    	* @param content The string used to display the board. 
	*/

    	//
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
	        	string board_piece;
	
	        	if (BOARD[i][j] == 0) content += "-";
	            	else content += to_string(BOARD[i][j]);
	
	            	if (j == 2 || j == 5)  content += " | ";
	            	else content += " ";
	        }//end of for
	        if (i == 2 || i == 5){
	            content += "\n";
	            for (int l = 0; l < 21; l++) content += ".";
	        }
	        content += "\n";
		
    	}//end of for
	
}


// Function to write board condition to a file 
bool writeSudokuToFile(int** BOARD, const string& filename) {
       /*
	* @param BOARD A 9x9 Sudoku board.
 	* @param filename The name of a file to write to.
	*/
	
    	//
    	string content;
	boardToString(BOARD, content);
	ofstream outFile(filename); // Open file for writing
	if (outFile.is_open()) {
		outFile << content; // Write content to file
	        outFile.close(); // Close the file
	        cout << "Content has been written to the file: " << filename << endl;
	        return true;
	}
	cerr << "Unable to open file: " << filename << endl;
	return false;

}


// Function to replace old character in a string with a new character
void replaceCharacter(std::string& str, char oldChar, char newChar) {
       /*
	* @param str An arbitrary string.
	* @param oldChar The old character to replace.
 	* @param newChar The new character to replace with oldChar.
 	*/
	
	//
	for (char &ch: str) {
	        if (ch == oldChar) {
	        ch = newChar;
	}
    }

}


// Function to extract digits from an input string using regex
void extractNumbers(const string& input, vector<int>& numbers) {
       /*
	* @param input An input string.
	* @param numbers A vector for all numbers in the string 'input'.
 	*/

	//regex to identify digits
	regex regex("\\d+");

	//get next instance of a digit (via regex) within the string input
	auto iterator = sregex_iterator(input.begin(), input.end(), regex);
	//end-of-sequence iterator for later comparison
	auto end = sregex_iterator();

	//while there is still an instance of a digit, iterator will not equal end, until then find next instance
	for (; iterator != end; ++iterator) {
		//more on this at the bottom of this file
        	numbers.push_back(stoi(iterator->str()));
    	}

}


// Function to fill Sudoku board up from 1-81 using a vector
void fillBoard(const vector<int>& numbers, int **BOARD){
       /*
	* @param numbers A vector filled with values from 1-81.
	* @param BOARD A 9x9 Sudoku board.
	*/

	//
	for(int i = 0; i < 9; i++) {
        	BOARD[i] = new int[9];
        	for(int j = 0; j < 9; j++){
            		BOARD[i][j] = numbers[i * 9 + j];
        	}
    	}

}


// Function to read a Sudoku puzzle from a file
int** readSudokuFromFile(const string& filename){
       /*
	* @param filename .
	*/

	//
    	int** BOARD = new int*[9];
    	vector<int> numbers;

    	ifstream file(filename);
    	string sudoku = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());

    	replaceCharacter(sudoku, '-', '0');
    	extractNumbers(sudoku, numbers);
    	fillBoard(numbers, BOARD);
    	return BOARD;

}


// Function to check if a given Sudoku board is a valid solution
bool checkIfSolutionIsValid(int** BOARD){
       /*
	* @param BOARD A 9x9 Sudoku board.
	*/

   	//
    	for(int r = 0; r < 9; r++) {
        	for(int c = 0; c < 9; c++) {
	            	int k = BOARD[r][c];
	            	BOARD[r][c] = 0;
	            	if(!isValid(BOARD, r, c, k)){
	                	BOARD[r][c] = k;
	                	// cout << "!!!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!!" << endl;
	                	return false;
	            	}
            		BOARD[r][c] = k;
        	}//end of for
    	}//end of for
    // cout << "--------------- TEST PASSED ---------------" << endl;
    return true;

}


// Function to retrieve all Sudoku puzzle file paths from a specified folder
vector<string> getAllSudokuInFolder(const string& folderPath){
       /*
	* @param folderPath .
	*/

    	//
    	vector<std::string> sudokus;
    	for (const auto& entry : filesystem::directory_iterator(folderPath)) {
        	if (filesystem::is_regular_file(entry)) {
            		sudokus.push_back(entry.path().string());
        	}
    	}
    	cout << sudokus.size() << " Sudoku Puzzle found @ " << folderPath << endl;
    	cout << setfill('-') << setw(55)<< "" << setfill(' ') <<endl;
    	cout << setw(5) << "Index" << setw(50) << "File Name" << endl;
    	cout << setfill('-') << setw(55)<< "" << setfill(' ') <<endl;
    	for(int i = 0; i < sudokus.size(); i++)
        	cout << setw(5) << i << setw(50) << sudokus[i] << endl;
    	cout << setfill('-') << setw(55)<< "" << setfill(' ') <<endl;
    	return sudokus;

}


// Function to generate and save a specified number of Sudoku puzzles
void createAndSaveNPuzzles(const int& num_puzzles, const int& complexity_empty_boxes, const string& destination, const string& prefix){
       /*
	* @param num_puzzles .
 	* @param complexity_empty_boxes .
	* @param destination .
 	* @param prefix .
	*/

    	//
    	int total_success = 0;
    	for(int i=0; i < num_puzzles; i++){
        	int** BOARD = generateBoard(complexity_empty_boxes);
        	string filename = getFileName(i, destination, prefix);
		
        	if(writeSudokuToFile(BOARD, filename)){
            		total_success++;
            		cout << "Successfully written(" << filename << ") "<< total_success << "of " << num_puzzles << endl;
        	}else{
            		cout << "!! Failed to write(" << filename << ") "<< total_success << "of " << num_puzzles << endl;
        	}
        	deallocateBoard(BOARD);
        	BOARD = nullptr;
    	}//end of for
    	cout << total_success << " files written out of " << num_puzzles <<endl;

}


// Function to display a progress bar in the console
void displayProgressBar(int current, int total, int barWidth = 50) {
       /*
	* @param current .
 	* @param total .
  	* @param barWidth .
	*/

    	//
    	float progress = static_cast<float>(current) / total;
    	int pos = static_cast<int>(barWidth * progress);

    	cout << "\r[";
    	for (int i = 0; i < barWidth; ++i) {
        	if (i < pos) cout << "=";
        	else if (i == pos) cout << ">";
        	else cout << " ";
    	}
    	cout << "] " << setw(3) << int(progress * 100.0) << "%";
    	cout.flush();

}


// Function to solve and save a specified number of Sudoku puzzles from a source folder
void solveAndSaveNPuzzles(const int &num_puzzles, const string& source, const string& destination, const string& prefix){
       /*
	* @param num_puzzles .
 	* @param source .
	* @param destination .
 	* @param prefix .
	*/

    	//
    	int total_success_solve = 0;
    	int total_success_write = 0;
    	vector<string> path_to_sudokus = getAllSudokuInFolder(source);

    	cout << "Number of loaded puzzles:" << path_to_sudokus.size() << "/" << num_puzzles << endl;
    	for(int i = 0; i < path_to_sudokus.size(); i++){
        	int** sudoku = readSudokuFromFile(path_to_sudokus[i]);
        	if(solve(sudoku)){
            		if(checkIfSolutionIsValid(sudoku)){
                		total_success_solve++;
                		string filename = getFileName(i, destination, prefix);
                		cout << "Puzzle Solved(over available): " << total_success_solve << "/" << path_to_sudokus.size() << " | ";
                		cout << "Puzzle Solved(over total): " << total_success_solve << "/" << num_puzzles << endl;
                		if(writeSudokuToFile(sudoku, filename)){
                    			total_success_write++;
                		}
                		cout << "Puzzle Solved Written(over available): " << total_success_write << "/" << path_to_sudokus.size() << " | ";
                		cout << "Puzzle Solved Written(over total): " << total_success_write << "/" << num_puzzles << endl;
            		}
        	}
    	}//end of for

}


// Function to perform a deep copy of a 9x9 Sudoku board
int** deepCopyBoard(int** original) {
       /*
	* @param original The original 9x9 Sudoku board to copy.
	*/
	
    	// Allocate memory for the new board
    	int** newBoard = new int*[9];
    	for (int i = 0; i < 9; i++) {
        	newBoard[i] = new int[9];  // Allocate each row

        	// Copy each element from the original board
        	for (int j = 0; j < 9; j++) {
            		newBoard[i][j] = original[i][j];
        	}
    	}
    	return newBoard;

}


// Function to compare the performance of two Sudoku solving algorithms
void compareSudokuSolvers(const int& experiment_size, const int& empty_boxes) {
       /*
	* @param experiment_size .
	* @param empty_boxes .
	*/
	
    	double totalTimeSolveBoard = 0.0;
    	double totalTimeEfficientSolveBoard = 0.0;

    	int validSolutionsSolveBoard = 0;
    	int validSolutionsEfficientSolveBoard = 0;

    	int** board1 = nullptr;
    	int** board2 = nullptr;
    	bool solved = false;

    	cout << "Running Sudoku Solver Comparisons...\n";

    	for (int i = 1; i <= experiment_size; ++i) {
        	// Generate a single board and deep copy
        	board1 = generateBoard(empty_boxes);  // Fresh board for efficient solver
        	if (!board1) {
            		cerr << "Failed to generate board.\n";
            		continue;
        	}
        	board2 = deepCopyBoard(board1);       // Deep copy for regular solver

        	// -------------------- Testing solveBoardEfficient --------------------
        	auto startEfficient = high_resolution_clock::now();
        	solved = solve(board1, true);  // Solve using efficient solver
        	auto endEfficient = high_resolution_clock::now();

        	double elapsedEfficient = duration<double>(endEfficient - startEfficient).count();
        	totalTimeEfficientSolveBoard += elapsedEfficient;

        	// Validate solution
        	if (solved && checkIfSolutionIsValid(board1)) {
            		validSolutionsEfficientSolveBoard++;
        	} else {
            		cerr << "solveBoardEfficient produced an invalid solution.\n";
        	}
        	deallocateBoard(board1);
            	board1 = nullptr;

        	// -------------------- Testing solveBoard --------------------
        	auto startSolve = high_resolution_clock::now();
        	solved = solve(board2);  // Solve using basic solver
        	auto endSolve = high_resolution_clock::now();

        	double elapsedSolve = duration<double>(endSolve - startSolve).count();
        	totalTimeSolveBoard += elapsedSolve;

        	// Validate solution
        	if (solved && checkIfSolutionIsValid(board2)) {
            		validSolutionsSolveBoard++;
        	} else {
            		cerr << "solveBoard produced an invalid solution.\n";
        	}
        	deallocateBoard(board2);
        	board2 = nullptr;

        	// -------------------- Progress Bar Update --------------------
        	displayProgressBar(i, experiment_size);
    	}//end of for

    	cout << endl;  // Move to the next line after progress bar is done.

    	// -------------------- Summary --------------------
    	cout << "====================== Performance Summary (Empty Boxes: " << empty_boxes << ") ======================" << endl;
    	cout << "Total Experiments: " << experiment_size << endl;
    	cout << "-------------------------------------------------------------" << endl;

    	cout << "solveBoard average time: " << fixed << setprecision(4)
         	<< 1000 * (totalTimeSolveBoard / experiment_size) << " milliseconds" << endl;
    	cout << "solveBoard valid solutions: " << validSolutionsSolveBoard << "/" << experiment_size << endl;

    	cout << "-------------------------------------------------------------" << endl;

   	cout << "efficientSolveBoard average time: " << fixed << setprecision(4)
         	<< 1000 * (totalTimeEfficientSolveBoard / experiment_size) << " milliseconds" << endl;
    	cout << "efficientSolveBoard valid solutions: " << validSolutionsEfficientSolveBoard << "/" << experiment_size << endl;

    	cout << "===========================================================================" << endl;

}



/*

numbers.push_back(stoi(iterator->str())), broken down:

iterator->str() returns a string containing the matches sequence of digits
stoi(..) converts a string to an int
numbers.push_back(..) adds the converted string to the end of the vector

So.. numbers.push_back(stoi(iterator->str())) is pretty much
add the next instance of a digit in the given string to the end of a vector after converting it to an int from a string

It should be important to note that 'iterator' is a string object of the next digit found by using a goated regex utility

*/
