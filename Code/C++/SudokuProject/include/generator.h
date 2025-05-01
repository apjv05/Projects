/**
* @file generator.h
 * @brief Function prototypes for generating random solvable Sudoku boards.
 *
 * This header defines functions to:
 * - Create empty Sudoku boards.
 * - Fill independent diagonal boxes.
 * - Solve and generate a complete Sudoku board.
 * - Randomly delete cells to create a solvable puzzle.
 * - Generate a complete Sudoku puzzle with a specific number of empty cells.
 *
 * Detailed function descriptions and parameters are provided below.
 *
 * @authors
 * Antonio Devine, Andrew Voyez, Lizzy Boyd
 *
 * @date
 * April 25nd, 2025
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

 /**
  * @brief Creates an empty 9x9 sudoku board
  *
  * Creates a 2d 9x9 array and fills it with 0s
  *
  * @return Returns the empty board
  */
int** getEmptyBoard();

/**
  * @brief Creates and shuffles a vector
  *
  * Creates a vector with number 1-9, then shuffles the vector using <algorithm>
  *
  * @return Returns shuffled vector
  */
std::vector<int> getShuffledVector();

/**
  * @brief Fills 3 random boxes of an empty 9x9 board
  *
  * Randomly decided to do left or right horizontal, then fills out empty portions
  * with a shuffled vector
  *
  * @param BOARD Empty 9x9 sudoku board that gets some positions filled
  */
void fillBoardWithIndependentBox(int** BOARD);

/**
  * @brief Randomly deletes a number of filled positions in a board
  *
  * First, function checks validity for board and n
  * Then, while random numbers aren't used, it deletes a cell
  *
  * @param BOARD 9x9 sudoku board
  * @param n Number of positions to delete (between 1 & 81)
  */
void deleteRandomItems(int** BOARD, const int& n);

/**
  * @brief Creates an empy 9x9 board, fills it, and deletes a certain number
  * of boxes/positions on the board
  *
  * Function calls getEmptyBoard to create a board, call a function to fill it,
  * then deletes a number of elements
  *
  * @param empty_boxes Number of positions to delete
  * @return Returs a 9x9 board with a number of empty spots
  */
int** generateBoard(const int& empty_boxes);

#endif // GENERATOR_H
