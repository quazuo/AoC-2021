#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

#define CONSIDER_DIAGS true

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    vector<pair<pair<int, int>, pair<int, int>>> lines;
    int max_x = 0, max_y = 0;

    // parse input
    for (const string& line : input) {
        vector<string> words = split_str(line);

        vector<int> first_coords = str_vec_to_int(split_str(words[0], ','));
        vector<int> second_coords = str_vec_to_int(split_str(words[2], ','));

        auto first_pair = make_pair(first_coords[0], first_coords[1]);
        auto second_pair = make_pair(second_coords[0], second_coords[1]);

        max_x = max(max_x, first_pair.first);
        max_x = max(max_x, second_pair.first);
        max_y = max(max_y, first_pair.second);
        max_y = max(max_y, second_pair.second);

        lines.emplace_back(first_pair, second_pair);
    }

    vector<vector<int>> floor(max_x + 1, vector<int>(max_y + 1, 0));

    for (const auto& line : lines) {
        auto begin = line.first, end = line.second;
        int x1 = begin.first, x2 = end.first, y1 = begin.second, y2 = end.second;
        int w = x2 - x1, h = y2 - y1;

        if (w == 0) { // vertical
            h = abs(h);
            int x = x1, y = y1 < y2 ? y1 : y2;

            for (int i = 0; i <= h; i++)
                floor[x][y + i]++;
        }
        else if (h == 0) { // horizontal
            w = abs(w);
            int x = x1 < x2 ? x1 : x2, y = y1;

            for (int i = 0; i <= w; i++)
                floor[x + i][y]++;
        }
        else if (CONSIDER_DIAGS) { // diagonal
            int i_x = w/abs(w), i_y = h/abs(h);
            w = abs(w);

            for (int i = 0; i <= w; i++)
                floor[begin.first + (i_x * i)][begin.second + (i_y * i)]++;
        }
    }

    int count = 0;

    for (int i = 0; i <= max_x; i++) {
        for (int j = 0; j <= max_y; j++) {
            if (floor[i][j] > 1)
                count++;
        }
    }

    vector<pair<string, set<int>>> aaa = {};
    my_print(aaa, true);

    cout << count;

    return 0;
}