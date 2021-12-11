#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

u_int64_t char_score(char c) {
    switch (c) {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
        default:
            return 0;
    }
}

u_int64_t illegal_score(string &line) {
    u_int64_t score = 0;

    for (char c : line) {
        if (char_score(c) != 0) {
            score += char_score(c);
            break;
        }
    }

    return score;
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    int result = 0;
    const string groups[4] = {"()", "[]", "{}", "<>"};

    for (string &line : input) {

        while (!line.empty()) {
            size_t index;
            bool found = false;

            for (const string &group : groups) {
                if ((index = line.find(group)) != string::npos) {
                    line.replace(index, 2, "");
                    found = true;
                }
            }

            if (!found)
                break;
        }

        result += illegal_score(line);

    }

    cout << result;

    return 0;
}