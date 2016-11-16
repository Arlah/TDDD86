/*
 * Tobias Fellegi, tobfe318
 * Thomas Annerfeldt, thoan578
 *
 * A version of game of life.
 */

#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

void printGrid(const Grid<char>& grid) {
    // Displays current grid on the terminal

    int r = grid.numRows();
    int c = grid.numCols();
    std::string gridrep;

    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
    }
}


int neighbours(const Grid<char>& grid, int row, int col) {
    // Checks the amount of live neighbours for a gridpoint

    int counter = 0;
    char alive = 'X';

    for (int r = row - 1; r < row + 2; r++) {
        for (int c = col-1; c < col+2; c++) {

            if (r != row || c != col) {
                if (grid.inBounds(r, c)) {
                    if (grid[r][c] == alive) {
                        counter++;
                    }
                }
            }
        }
    }

    return counter;
}

void tick(Grid<char>& grid) {
    // Cycles the lfe in the grid

    int counter;
    char alive = 'X';
    Grid<char> temp_grid = grid;
    for (int row = 0; row < grid.numRows(); row++) {
        for (int col = 0; col < grid.numCols(); col++) {
            counter = neighbours(grid, row, col);

            if (counter < 2) {
                temp_grid[row][col] = '-';
            }
            else if (counter == 2) {
                if (grid[row][col] == alive) {
                    temp_grid[row][col] = 'X';
                }
                else {
                    temp_grid[row][col] = '-';
                }
            }
            else if (counter == 3) {
                temp_grid[row][col] = 'X';
            }
            else {
                temp_grid[row][col] = '-';
            }
        }
    }
    grid = temp_grid;
    printGrid(grid);
}


void animate(Grid<char>& grid, int cycles) {
    // Repeats tick

    for (int i = cycles; i > 0; i--) {
        clearConsole();
        tick(grid);
        pause(100);
    }
}

int main() {

    int row;
    int col;
    std::string file;
    Grid<char> game_board;


    std::cout << "Welcome to the TDDD86 Game of Life,\n" <<
                 "a simulation of the lifecycle of a bacteria colony.\n" <<
                 "Cells (X) live and die by the following rules:\n" <<
                 "- A cell with 1 or fewer neighbours dies.\n" <<
                 "- Locations with 2 neighbours remain stable.\n" <<
                 "- Locations with 3 neighbours will create life.\n" <<
                 "- A cell with 4 or more neighbours dies" << std::endl;

    std::cout << "\nGrid input file name? ";

    // Loads file
    std::cin >> file;
    std::cout << std::endl;
    std::ifstream input(file);
    std::string line;

    // Resizes the grid with the first two lines
    getline(input, line);
        row = std::stoi(line);
    getline(input, line);
        col = std::stoi(line);
    game_board.resize(row, col);


    // Fills the grid with the - and X
    for (int y = 0; y < row; y++) {
        getline(input, line);
        for (int x = 0; x < col; x++) {
            game_board[y][x] = line[x];
        }
    }

    input.close();
    printGrid(game_board);

    // Loop for input from the user determining action
    char type;
    bool cont = true;
    while (cont) {
        std::cout << "a)nimate, t)ick, q)uit? ";
        std::cin >> type;
        std::cout << std::endl;

        if (type == 'a') {
            animate(game_board, 6);
        }
        else if (type == 't') {
            tick(game_board);
        }
        else if (type == 'q') {
            cont = false;
        }
    }


    std::cout << "\n" << "Have a nice Life!" << std::endl;
    return 0;
}
