<!-- Red Background Warning -->
# Sudoku Solver Project

## Overview

The goal of this project was to, as a group, create an operational Sudoku solver based on a backtracking algorithm, and generator. The fundamental functionality entailed reading an unsolved Sudoku grid, recursively visiting possible placements of numbers, and returning an existing solution when available. The primary result was to implement an effective recursive solver that could successfully solve standard 9x9 Sudoku puzzles. A `DEBUG` mode is available for verifying implementation. When running in non-`DEBUG` mode, the program will output files in the `data` folder, typically found inside the `cmake-build-debug` directory.

> **Important:** This project is **strongly recommended** to be run using **CLion**. If you wish to use **VSCode**, utilize the provided `buildrun.sh` script.

## Project Structure

```
├── CMakeLists.txt
├── main.cpp
├── include/
│   ├── generator.h
│   ├── sudoku.h
│   ├── sudoku_io.h
│   └── utils.h
├── src/
│   ├── generator.cpp
│   ├── sudoku.cpp
│   ├── sudoku_io.cpp
│   └── utils.cpp
├── cmake-build-debug/
│   └── data/ (Only if you run the program in non-debug mode)
│       ├── puzzles/
│       └── solutions/
└── buildrun.sh (for VSCode users)
```

## Running the Project

### Using CLion (Recommended)

1. Open the project in **CLion**.
2. Set the configuration to `DEBUG` mode if you want to verify your implementation.
3. Run the project.
4. In **non-DEBUG** mode, output files will be saved in:
   ```
   cmake-build-debug/data/
   ```

### Using VSCode

1. Open the project in **VSCode**.
2. Use the provided `buildrun.sh` script to compile and run the project:
   ```bash
   ./buildrun.sh full/path/to/your/project/folder
   ```
   or,
   ```bash
   bash buildrun.sh full/path/to/your/project/folder
   ```
   or,
   ```bash
   sh buildrun.sh full/path/to/your/project/folder
   ```

## Debug Mode

- **DEBUG mode** includes a special `main` function for testing and verifying your code.
- This mode helps ensure your solutions work before running in production.

## Output

- In **non-DEBUG** mode, the program will read puzzles from `data/puzzles/` and write solutions to `data/solutions/`.

Happy coding and feel free to ask questions if anything is unclear!
