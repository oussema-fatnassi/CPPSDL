# Tile Twister in C++

Tile Twister is a popular puzzle game where you move tiles on a 4x4 grid to try to reach the number 2048.

## Features

3 version of the project: terminal, SDL and SFML

- Selection of grid size between 3x3, 4x4, 5x5, 6x6 and 8x8
- Tile movement in four directions: up, down, left, right.
- Merging of tiles with the same value when they collide.
- Detection of valid moves and addition of new tiles after each valid move.
- Display of the grid in the terminal.

## Installation

- Clone the repository to your local machine:

```bash
git clone https://github.com/oussema-fatnassi/CPPSDL.git
```


###### Steps for Winfows installation
- Open MSYS MINGW64
- Type : pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf
- Verify that everything is installed
- Type : cd /ucrt64/lib
- Type : ls | grep SDL2
- You should see : 
libSDL2.a
libSDL2.dll.a
libSDL2_image.a
libSDL2_image.dll.a
libSDL2_test.a
libSDL2_ttf.a
libSDL2_ttf.dll.a
libSDL2main.a
- If not, type : pacman -S mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-SDL2_image mingw-w64-ucrt-x86_64-SDL2_ttf
- Install everything

In case of error repeat any point necessary



If the following error appears :

Running

   'nmake' '-?'

  failed with:

   no such file or directory

- Close and re-open MSYS MINGW64
- Type echo $MSYSTEM
It should output : MINGW64
- Type : pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc
- Verify that everything is installed
- Navigate to your project : cd /(link to your project)/build
If there is a space " " type "\ " instead
- Type rm -rf * or delete manually everything in the build folder
- Type : cmake -G "MinGW Makefiles" ..
- Type : mingw32-make

## Credits
- Developed by Oussema Fatnassi, Baptiste Appriou, Ali Abakar Issa
