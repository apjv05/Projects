#!/bin/bash

# Check if project directory is provided
if [[ -z "$1" ]]; then
    echo "Usage: $0 <path_to_project_dir> [program_arguments...]"
    exit 1
fi

PROJECT_DIR="$1"
shift 1  # Remove the project directory argument; the rest (if any) are for the executable

# Check if the provided directory exists
if [[ ! -d "$PROJECT_DIR" ]]; then
    echo "Error: Directory $PROJECT_DIR does not exist."
    exit 1
fi

# Check if the directory contains at least one .cpp file
CPP_FILES=$(find "$PROJECT_DIR" -maxdepth 1 -type f -name "*.cpp")
if [[ -z "$CPP_FILES" ]]; then
    echo "Error: Directory $PROJECT_DIR does not contain any .cpp files."
    exit 1
fi

# Check if the directory contains a CMakeLists.txt file
if [[ ! -f "$PROJECT_DIR/CMakeLists.txt" ]]; then
    echo "Error: Directory $PROJECT_DIR does not contain a CMakeLists.txt file."
    exit 1
fi

# Display some cool ASCII art
echo " ░▒▓██████▓▒░ ░▒▓███████▓▒░      ░▒▓███████▓▒░░▒▓███████▓▒░░▒▓████████▓▒░░▒▓██████▓▒░  "
echo "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░                    ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ "
echo "░▒▓█▓▒░      ░▒▓█▓▒░                    ░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ "
echo "░▒▓█▓▒░       ░▒▓██████▓▒░        ░▒▓██████▓▒░░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░  "
echo "░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ "
echo "░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ "
echo " ░▒▓██████▓▒░░▒▓███████▓▒░       ░▒▓████████▓▒░▒▓███████▓▒░░▒▓████████▓▒░░▒▓██████▓▒░  "

# Remove existing build directory if it exists
[[ -d "$PROJECT_DIR/cmake-build-debug" ]] && rm -rf "$PROJECT_DIR/cmake-build-debug"

# Create build directory and compile the project
mkdir -p "$PROJECT_DIR/cmake-build-debug"
cmake -B "$PROJECT_DIR/cmake-build-debug" -S "$PROJECT_DIR"
cmake --build "$PROJECT_DIR/cmake-build-debug"

echo "----------------------------------------"
echo "------------COMPILATION DONE------------"
echo "----------------------------------------"

# Get the project folder name
PROJECT_NAME=$(basename "$PROJECT_DIR")
echo "Project Name: $PROJECT_NAME"

# Define build path based on environment
BUILD_PATH="$PROJECT_DIR"

# Determine OS and run the executable accordingly, passing any additional arguments
OS="$(uname)"
echo "Build path: $BUILD_PATH"
echo "Files in build path:"
ls -lah "$BUILD_PATH"
echo " ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
echo " ░░░░░░░░░░░░░░░░░░░░░░░░░░░      OUTPUT      ░░░░░░░░░░░░░░░░░░░░░░░░░░░"

if [[ "$OS" == "Linux" || "$OS" == "Darwin" ]]; then
    if [[ -f "$BUILD_PATH/$PROJECT_NAME" ]]; then
        "$BUILD_PATH/$PROJECT_NAME" "$@"
    else
        echo "Error: Executable not found in $BUILD_PATH"
        exit 1
    fi
elif [[ $OS =~ MINGW || $OS =~ CYGWIN || $OS =~ MSYS ]]; then
    if [[ -f "$BUILD_PATH/Debug/$PROJECT_NAME.exe" ]]; then
        "$BUILD_PATH/Debug/$PROJECT_NAME.exe" "$@"
    else
        echo "Error: Executable not found in $BUILD_PATH/Debug"
        exit 1
    fi
else
    echo "Unsupported OS: $OS"
    exit 1
fi
echo " ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
