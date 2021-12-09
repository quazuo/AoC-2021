#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    int n = input.size(), m = input[0].size();
    int result = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i != 0 && input[i - 1][j] <= input[i][j])
                continue;
            if (i != n - 1 && input[i + 1][j] <= input[i][j])
                continue;
            if (j != 0 && input[i][j - 1] <= input[i][j])
                continue;
            if (j != m - 1 && input[i][j + 1] <= input[i][j])
                continue;

            result += input[i][j] - '0' + 1;
        }
    }

    cout << result;

    return 0;
}