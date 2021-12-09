#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

static const char chars[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

bool contains(string& word, char c) {
    for (char i : word) {
        if (i == c)
            return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    int result = 0;

    for (const string& line : input) {

        vector<string> words = split_str(line);
        char segments[7];
        vector<string> digits(10);

        vector<int> seen(7, 0);

        for (int i = 0; i < 10; i++) {
            for (char c : words[i]) {
                seen[c - 'a']++;
            }
            // find the 1, 4, 7, 8 digits
            switch (words[i].size()) {
                case 2:
                    digits[1] = words[i];
                    break;
                case 3:
                    digits[7] = words[i];
                    break;
                case 4:
                    digits[4] = words[i];
                    break;
                case 7:
                    digits[8] = words[i];
                    break;
            }
        }
        // find the 1 and 4 segments
        for (int i = 0; i < 7; i++) {
            switch (seen[i]) {
                case 4:
                    segments[4] = chars[i];
                    break;
                case 6:
                    segments[1] = chars[i];
                    break;
            }
        }

        for (int i = 0; i < 10; i++) {
            // find the 9 digit
            if (words[i].size() == 6 && !contains(words[i], segments[4])) {
                digits[9] = words[i];
            }
            // find the 5 digit
            if (words[i].size() == 5 && contains(words[i], segments[1])) {
                digits[5] = words[i];
            }
            // find the 2 digit
            if (words[i].size() == 5 && contains(words[i], segments[4])) {
                digits[2] = words[i];
            }
        }
        // find the 3 digit
        for (int i = 0; i < 10; i++) {
            if (words[i].size() == 5 && words[i] != digits[2] && words[i] != digits[5]) {
                digits[3] = words[i];
                break;
            }
        }
        // find the 6 digit
        for (int i = 0; i < 10; i++) {
            if (words[i].size() == 6 &&
            (!contains(words[i], digits[1][0]) || !contains(words[i], digits[1][1]))) {
                digits[6] = words[i];
                break;
            }
        }
        // find the 0 digit
        for (int i = 0; i < 10; i++) {
            if (words[i].size() == 6 && words[i] != digits[6] && words[i] != digits[9]) {
                digits[0] = words[i];
                break;
            }
        }

        // sort each of the array elements for convenience
        for (int i = 0; i < 10; i++) {
            sort(digits[i].begin(), digits[i].end());
        }

        // compute the 4 digit number and add it to the result sum
        int pow10 = 1000;

        for (int i = 11; i < 15; i++) {
            sort(words[i].begin(), words[i].end());
            for (int j = 0; j < 10; j++) {
                if (words[i] == digits[j]) {
                    result += pow10 * j;
                    pow10 /= 10;
                    break;
                }
            }
        }
    }

    cout << result;

    return 0;
}