/**
 * @file sudoku.h
 * @brief Core Sudoku solving and board generation functions.
 *
 * This header file declares functions essential for solving Sudoku puzzles
 * and validating board states. It includes:
 * - A backtracking Sudoku solver.
 * - A cell validation function to ensure valid number placement.
 * - A board generation stub for creating Sudoku puzzles.
 *
 * All functions operate on dynamically allocated 9x9 Sudoku boards
 * represented as `int**`, where empty cells are denoted by 0.
 *
 * @authors
 * Antonio Devine, Andrew Voyez, Lizzy Boyd
 *
 * @date
 * April 25nd, 2025
 */

#ifndef SUDOKUPROJECT_SUDOKU_H
#define SUDOKUPROJECT_SUDOKU_H

#include <iostream>

/**
  * @brief Checks which number can be put into the current selected spot on the board
  *
  * Searches the colum and row of current position of k for numbers 1-9
  * Determines 3x3 box
  * Searches the 3x3 box for numbers 1-9
  * Returns true if a number assigned k is not found in 3x3 box or in the colum and row
  *
  * @param BOARD The sudoku board that k has a position on
  * @param r The row that k is positioned on
  * @param c The colum that k is positioned on
  * @param k The number and position that is being checked for validity
  * @return True if number inputed is valid, otherwise false
  */
bool isValid(int** BOARD, const int& r, const int& c, const int& k);

/**
  * @brief Solves the given sudoku board through recursion
  *
  * Checks if it's at the last row of the board, if not checks if it's at the last colum
  * Recalls function with r+1 for the first position of the next row
  * Checks in all empty spots numbers 1-9, if number is found returns true, if not it backtracks
  *
  * @param BOARD The sudoku board being solved
  * @param r The row number
  * @param c The colum number
  * @retun Returns true if a solution is found or if the board is solved
  */
bool solveBoard(int** BOARD, const int& r=0, const int& c=0);

// ========================= Efficient Solutions ==========================


/**
  * @brief Finds the empty boxes and returns the one with the smallest amount of possinle answeres
  *
  * The function goes through the empty boxes of BOARD and counts how many valid answeres using isValid,
  * then the function returns the box with the least amount of possible answeres
  *
  * @param BOARD The sudoku board that the function is using to find next cell
  * @return Returns where the empty box is and the smallest amount of possible valid number
  */
std::tuple<int, int, int> findNextCell(int** BOARD);


/**
  * @brief Solves the board more efficently using backtracking
  *
  * This function uses a recursive backtracking approach combined with the Minimum Remaining Value (MRV)
  * heuristic to optimize the solving process by always selecting the cell with the fewest valid options.
  *
  * @param BOARD Sudoku board being solved
  * @return True to check solution, false if the placed number is wrong
  */
bool solveBoardEfficient(int** BOARD);

/**
  * @brief
  *
  * If the function is called where efficient is true, then solveBoardEfficient is called with board,
  * otherwise solveBoard is called with board
  *
  * @param board The sudoku board that the function is checking
  * @param efficient Used to decide if the board should be solved efficiently or not
  * @return The solveBoardEfficient function if efficient is true, else solveBoard function
  */
bool solve(int** board, const bool& efficient = false);

#endif //SUDOKUPROJECT_SUDOKU_H