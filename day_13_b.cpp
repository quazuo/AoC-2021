#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    vector<pair<int, int>> points;
    int max_x = 0, max_y = 0;
    size_t first_fold;

    // read points
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i].empty()) {
            first_fold = i + 1;
            break;
        }

        vector<int> coords = str_vec_to_int(split_str(input[i], ','));
        int x = coords[0], y = coords[1];

        max_x = max(max_x, x);
        max_y = max(max_y, y);

        points.emplace_back(x, y);
    }

    // put points on the sheet
    vector<vector<bool>> sheet(max_y + 1, vector<bool>(max_x + 1, false));
    for (const auto& [x, y] : points)
        sheet[y][x] = true;

    // read fold queries
    vector<pair<bool, size_t>> folds;
    for (size_t i = first_fold; i < input.size(); i++) {
        vector<string> fold = split_str(split_str(input[i])[2], '=');
        folds.emplace_back(fold[0] == "x", stoi(fold[1]));
    }

    size_t x_size = sheet[0].size(), y_size = sheet.size();

    // execute fold queries
    for (const auto& [is_x, line] : folds) {

        if (is_x) {

            for (size_t i = line + 1; i < x_size; i++) {
                if (2 * line - i < 0) // too far left
                    break;

                for (size_t j = 0; j < y_size; j++)
                    sheet[j][2 * line - i] = sheet[j][2 * line - i] || sheet[j][i];
            }

            x_size = line;

        } else {

            for (size_t i = line + 1; i < y_size; i++) {
                if (2 * line - i < 0) // too far up
                    break;

                for (size_t j = 0; j < x_size; j++)
                    sheet[2 * line - i][j] = sheet[2 * line - i][j] || sheet[i][j];
            }

            y_size = line;

        }

    }

    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            cout << (sheet[i][j] ? '@' : ' ');
        }
        cout << '\n';
    }
    cout << '\n';

    return 0;
}

