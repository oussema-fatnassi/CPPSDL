# Tile Twister in C++

This project is a recreation of the classic 2048 game, developed using two different libraries: SDL (Simple DirectMedia Layer) and SFML (Simple and Fast Multimedia Library). The objective of the game is to slide numbered tiles on a grid to combine them and create a tile with the number 2048.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Libraries Used](#libraries-used)
- [Step for windows installation](#known-issues)
- [Contributing](#contributing)


## Overview

This 2048 game project allows you to experience the popular puzzle game with two different graphical implementations using SDL and SFML. Both versions offer the same gameplay mechanics but showcase the different capabilities and strengths of each library.

## Features
- Two implementations of the 2048 game using SDL and SFML.
- Smooth animations for tile movement and merging.
- Score tracking to keep track of your best performance.
- Restart option to start a new game anytime.
- Undo feature to correct your last move (if implemented).

## Installation

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC recommended).
- CMake for building the project.
- SDL2 and SFML libraries installed on your system.

### Building the Project

1. **Clone the repository:**
   ```bash
   git clone https://github.com/oussema-fatnassi/CPPSDL.git


## How to Play:
  - Start the game using either the SDL or SFML version.
  - When The main SDL version is launched use git clone https://github.com/google/googletest.git to integrate the test.
  - Use the arrow keys to slide the tiles in four possible directions: up, down, left, or right.
  - When two tiles with the same number collide, they merge into one with the sum of their values.
  - The goal is to create a tile with the number 2048.
  - The game ends when no more moves are possible.

## Libraries Used
 - SDL: A cross-platform development library providing low-level access to audio, keyboard, mouse, and graphics hardware.
 - SFML: A simple and fast multimedia library that provides easy-to-use classes for graphics, windowing, and handling inputs.


## Steps for Winfows installation
Open MSYS MINGW64
Type : pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf
Verify that everything is installed
Type : cd /ucrt64/lib
Type : ls | grep SDL2
You should see : libSDL2.a libSDL2.dll.a libSDL2_image.a libSDL2_image.dll.a libSDL2_test.a libSDL2_ttf.a libSDL2_ttf.dll.a libSDL2main.a
If not, type : pacman -S mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-SDL2_image mingw-w64-ucrt-x86_64-SDL2_ttf
Install everything
In case of error repeat any point necessary

If the following error appears :

Running

'nmake' '-?'

failed with:

no such file or directory.

Close and re-open MSYS MINGW64
Type echo $MSYSTEM It should output : MINGW64
Type : pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc
Verify that everything is installed
Navigate to your project : cd /(link to your project)/build If there is a space " " type "\ " instead
Type rm -rf * or delete manually everything in the build folder
Type : cmake -G "MinGW Makefiles" ..
Type : mingw32-make


   
## Credits
- Developed by Oussema Fatnassi, Baptiste Appriou, Ali Abakar Issa
