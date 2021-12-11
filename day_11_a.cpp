#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

#define GRID_SIZE 10
#define STEP_COUNT 100

void flash(vector<vector<int>>& octopuses, vector<vector<bool>>& flashed, int x, int y) {
    flashed[x][y] = true;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            if (x + i < 0 || x + i >= GRID_SIZE || y + j < 0 || y + j >= GRID_SIZE || (i == 0 && j == 0))
                continue;

            octopuses[x + i][y + j]++;
            if (!flashed[x + i][y + j] && octopuses[x + i][y + j] > 9)
                flash(octopuses, flashed, x + i, y + j);

        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    vector<vector<int>> octopuses(GRID_SIZE, vector<int>(GRID_SIZE));
    int flash_count = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            octopuses[i][j] = input[i][j] - '0';
        }
    }

    for (int i = 0; i < STEP_COUNT; i++) {

        vector<vector<bool>> flashed(GRID_SIZE, vector<bool>(GRID_SIZE, false));
        bool any_flashed;

//        cout << endl;
//        my_print(octopuses, true);
//        cout << endl;

        // increase all energy levels
        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                octopuses[x][y]++;
            }
        }

        // flashing occurs
        do {
            any_flashed = false;

            for (int x = 0; x < GRID_SIZE; x++) {
                for (int y = 0; y < GRID_SIZE; y++) {
                    if (!flashed[x][y] && octopuses[x][y] > 9) {
                        any_flashed = true;
                        flash(octopuses, flashed, x, y);
                    }
                }
            }
        } while (any_flashed);

        // drain all flashed
        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                if (flashed[x][y]) {
                    octopuses[x][y] = 0;
                    flash_count++;
                }
            }
        }

    }

    cout << flash_count;

    return 0;
}
