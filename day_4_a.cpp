#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

#define BOARD_SIZE 5

bool check_board(vector<vector<bool>> &board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        bool row_flag = true, col_flag = true;

        for (int j = 0; j < BOARD_SIZE; j++) {
            row_flag &= board[i][j];
            col_flag &= board[j][i];
        }

        if (row_flag || col_flag)
            return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();

    vector<int> guesses = str_vec_to_int(split_str(input[0], ','));
    vector<vector<vector<int>>>
        bingo_boards(0, vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE)));
    vector<vector<vector<bool>>>
        crossed_nums(0, vector<vector<bool>>(BOARD_SIZE, vector<bool>(BOARD_SIZE, false)));
    int i = -2, j = 0;

    vector<vector<int>> temp;

    for (const string &str : input) {
        if (str.empty() || str == input[0]) {
            if (i >= 0) {
                bingo_boards.push_back(temp);
                crossed_nums.emplace_back(vector<vector<bool>>(BOARD_SIZE, vector<bool>(BOARD_SIZE, false)));
            }
            temp = vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE));
            i++;
            j = 0;
            continue;
        }

        temp[j] = str_vec_to_int(split_str(str));

        j++;
    }

    bingo_boards.push_back(temp);
    crossed_nums.emplace_back(vector<vector<bool>>(BOARD_SIZE, vector<bool>(BOARD_SIZE, false)));

    bool game_ended = false;
    int answer = 0;

    for (int guess : guesses) {

        for (int bi = 0; bi < bingo_boards.size(); bi++) {

            for (i = 0; i < BOARD_SIZE; i++) {
                for (j = 0; j < BOARD_SIZE; j++) {
                    if (bingo_boards[bi][i][j] == guess) {
                        crossed_nums[bi][i][j] = true;
                    }
                }
            }

            if (check_board(crossed_nums[bi])) {
                for (i = 0; i < BOARD_SIZE; i++) {
                    for (j = 0; j < BOARD_SIZE; j++) {
                        answer += crossed_nums[bi][i][j] ? 0 : bingo_boards[bi][i][j];
                    }
                }

                answer *= guess;
                game_ended = true;
            }
        }

        if (game_ended)
            break;
    }

    cout << answer;

    return 0;
}