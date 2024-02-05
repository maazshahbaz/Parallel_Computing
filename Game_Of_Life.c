#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define GENERATIONS 10

void printGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", grid[i][j] ? '#' : ' ');
        }
        printf("\n");
    }
    printf("\n");
}

void copyGrid(int src[SIZE][SIZE], int dest[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int countNeighbors(int grid[SIZE][SIZE], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = (x + i + SIZE) % SIZE;
            int ny = (y + j + SIZE) % SIZE;
            count += grid[nx][ny];
        }
    }
    count -= grid[x][y];
    return count;
}

void updateGrid(int grid[SIZE][SIZE]) {
    int newGrid[SIZE][SIZE];
    copyGrid(grid, newGrid);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int neighbors = countNeighbors(grid, i, j);

            if (grid[i][j] && (neighbors < 2 || neighbors > 3)) {
                newGrid[i][j] = 0;
            } else if (!grid[i][j] && neighbors == 3) {
                newGrid[i][j] = 1;
            }
        }
    }

    copyGrid(newGrid, grid);
}

int main() {
    srand(time(NULL));

    int grid[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = rand() % 2;
        }
    }

    for (int i = 0; i < GENERATIONS; i++) {
        printGrid(grid);
        updateGrid(grid);
    }

    return 0;
}