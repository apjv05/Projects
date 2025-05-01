cmake_minimum_required(VERSION 3.30)
project(SudokuProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(SudokuProject main.cpp
        include/sudoku.h
        include/sudoku_io.h
        src/sudoku.cpp
        src/sudoku_io.cpp
        src/generator.cpp
        include/generator.h
        src/utils.cpp
        include/utils.h
)
