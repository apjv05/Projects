/**
 * @file utils.cpp
 * @brief Implementation of functions to handle utilities and memory deallocation.
 *
 * This file contains logic and functions to, in order:
 * - Deallocates a Sudoku board. deallocateBoard(int**, const int&)
 * - Creates a directory. createFolder(const string&)
 * - Initalizes project data folders. initDataFolder()
 * - Returns standardized file name. getFileName(const int&, const string&, const string&)
 * 
 *
 * @authors
 * Antonio Devine, Andrew Voyez, Lizzy Boyd
 *
 * @date
 * April 25nd, 2025
 */


#include <iostream>
#include <string>
#include <filesystem>

using namespace std;



// Function to deallocate any Sudoku board from memory
void deallocateBoard(int** BOARD, const int& rows) { 
    /*
     * @param BOARD A 9x9 Sudoku board.
     * @param rows The number of rows in BOARD.
     */
    
    // Check if BOARD is nullptr.
    if(BOARD == nullptr) return;
    
    else {
        // Iterate through each row and deallocate using delete[].
        for(int i=0; i<rows; i++) {
            delete[] BOARD[i];
        }
        
        // Deallocate the array of row pointers using delete[].
        delete[] BOARD;
        
        // Set BOARD to nullptr to avoid dangling pointers.
        BOARD = nullptr;
    }
    
}



// Function to create a directory on clients machine
void createFolder(const std::string& folderPath) {
    /*
     * @param folderPath A direct file path.
     */
    
    //
    if (!filesystem::exists(folderPath)) {
        
        if (filesystem::create_directory(folderPath)) {
            std::cout << "Folder created successfully: " << folderPath << std::endl;
        } else {
            std::cerr << "Failed to create folder: " << folderPath << std::endl;
        }
    
    } else {
        std::cout << "Folder already exists: " << folderPath << std::endl;
    }
}


// Function to initialize 'data/' project files on clients machine
void initDataFolder(){
    createFolder("data/");
    createFolder("data/puzzles/");
    createFolder("data/solutions/");
}


// Function to create and name files in a organized and sequential order using string math
string getFileName(const int& index, const string& destination, const string& prefix){
    /*
     * @param index An int used for file name redundancy.
     * @param destination A direct file path.
     * @param prefix A string file name.
     */
    
    string index_str = to_string(index);
    string index_fill = string(4 - index_str.length(), '0');
    string filename = destination + index_fill + index_str + prefix + ".txt";
    return filename;
}
