/**
 * @file sudoku_io.h
 * @brief Input/Output utility functions for handling Sudoku puzzles.
 *
 * This header file declares functions for reading, writing, displaying,
 * and managing Sudoku puzzles. It includes utilities to:
 * - Print Sudoku boards to the console with color-coded hints.
 * - Read and write Sudoku puzzles from/to files.
 * - Parse and extract numbers from text representations.
 * - Generate and solve multiple Sudoku puzzles.
 * - Handle file system operations to read puzzle sets from directories.
 *
 * The functions work with a dynamically allocated 9x9 Sudoku board
 * represented as `int**`, where empty cells are denoted by 0.
 *
 * @authors
 * Antonio Devine, Andrew Voyez, Lizzy Boyd
 *
 * @date
 * April 25nd, 2025
 */

#ifndef SUDOKUPROJECT_SUDOKUIO_H
#define SUDOKUPROJECT_SUDOKUIO_H

#include <vector>
#include <string>
using namespace std;

/**
 * @brief Prints the Sudoku board to the console with highlighting.
 *
 * Displays the Sudoku board with color-coded hints. If a position `(r, c)`
 * and a candidate `k` are provided, the cell will be highlighted:
 * - Green if placing `k` is valid.
 * - Red if placing `k` violates Sudoku rules.
 * - Yellow for empty cells.
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @param r Row index for the candidate (default: 0).
 * @param c Column index for the candidate (default: 0).
 * @param k Candidate number to test (default: 0, no candidate highlighted).
 */
void printBoard(int** BOARD, const int& r=0, const int& c=0, int k=0);

/**
 * @brief Converts the Sudoku board into a string representation.
 *
 * Converts the 9x9 board into a string format, using '-' for empty cells.
 * Includes separators for readability.
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @param content Reference to a string where the board will be stored.
 */
void boardToString(int** BOARD, string& content);

/**
 * @brief Writes the Sudoku board to a file.
 *
 * Serializes the board into a formatted string and writes it to the specified file.
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @param filename Name of the file to write the board to.
 * @return true if writing was successful, false otherwise.
 */
bool writeSudokuToFile(int** BOARD, const string& filename);

/**
 * @brief Replaces all occurrences of a character in a string.
 *
 * Scans the input string and replaces every instance of `oldChar` with `newChar`.
 *
 * @param str The string to perform replacements on.
 * @param oldChar The character to be replaced.
 * @param newChar The character to replace with.
 */
void replaceCharacter(string& str, char oldChar, char newChar);

/**
 * @brief Extracts integers from a string.
 *
 * Parses the input string and extracts all sequences of digits,
 * converting them into integers and storing them in a vector.
 *
 * @param input The input string to parse.
 * @param numbers A vector where extracted integers will be stored.
 */
void extractNumbers(const string& input, vector<int>& numbers);

/**
 * @brief Fills a Sudoku board with numbers from a vector.
 *
 * Populates a 9x9 Sudoku board using numbers from a vector. Assumes the
 * vector has at least 81 integers.
 *
 * @param numbers A vector containing the numbers to fill the board.
 * @param BOARD A pointer to the 2D Sudoku board (int**) to fill.
 */
void fillBoard(const vector<int>& numbers, int** BOARD);

/**
 * @brief Reads a Sudoku board from a file.
 *
 * Parses a file containing a Sudoku puzzle, converts the content into a
 * 9x9 board, and returns a dynamically allocated board.
 *
 * @param filename The path to the file containing the Sudoku puzzle.
 * @return A pointer to a dynamically allocated 2D Sudoku board.
 */
int** readSudokuFromFile(const string& filename);

/**
 * @brief Checks if the provided Sudoku board is a valid solution.
 *
 * Validates the board against standard Sudoku rules:
 * - Each row contains unique numbers from 1 to 9.
 * - Each column contains unique numbers from 1 to 9.
 * - Each 3x3 subgrid contains unique numbers from 1 to 9.
 *
 * @param BOARD A pointer to the 2D Sudoku board (int**).
 * @return true if the solution is valid, false otherwise.
 */
bool checkIfSolutionIsValid(int** BOARD);

/**
 * @brief Retrieves all Sudoku puzzle filenames in a given folder.
 *
 * Scans the specified folder and returns paths to all Sudoku puzzle files.
 *
 * @param folderPath Path to the folder containing Sudoku puzzles.
 * @return A vector of file paths to the Sudoku puzzles.
 */
vector<string> getAllSudokuInFolder(const string& folderPath);

/**
 * @brief Generates and saves multiple Sudoku puzzles.
 *
 * Generates `num_puzzles` new Sudoku boards and saves them as text files
 * in the specified destination folder with filenames prefixed by `prefix`.
 *
 * @param num_puzzles The number of puzzles to generate.
 * @param destination Folder where the puzzles will be saved.
 * @param prefix Filename prefix for the saved puzzles.
 */
void createAndSaveNPuzzles(const int& num_puzzles, const int& complexity_empty_boxes, const string& destination, const string& prefix);

/**
 * @brief Solves and saves multiple Sudoku puzzles from a source folder.
 *
 * Reads unsolved puzzles from `source`, solves them, and saves the
 * solutions to `destination` with filenames prefixed by `prefix`.
 *
 * @param num_puzzles The number of puzzles to solve.
 * @param source Folder containing unsolved puzzles.
 * @param destination Folder where solved puzzles will be saved.
 * @param prefix Filename prefix for the saved solutions.
 */
void solveAndSaveNPuzzles(const int& num_puzzles, const string& source, const string& destination, const string& prefix);

/**
 * @brief Performs a deep copy of a 9x9 Sudoku board.
 *
 * @param original The original 9x9 Sudoku board to copy.
 * @return int** A pointer to the newly allocated deep-copied board.
 */
int** deepCopyBoard(int** original);

/**
 * @brief Compares the performance of solveBoard and efficientSolveBoard.
 *
 * Runs both solvers multiple times on generated Sudoku boards and prints
 * the average runtime for each solver.
 *
 * @param experiment_size Number of experiments to run.
 * @param empty_boxes Number of empty cells in the generated Sudoku board.
 */
void compareSudokuSolvers(const int& experiment_size, const int& empty_boxes);

#endif //SUDOKUPROJECT_SUDOKUIO_H