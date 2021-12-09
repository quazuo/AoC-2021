#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

int bfs(vector<vector<bool>>& basins, vector<vector<bool>>& visited, int x, int y) {
    if (x < 0 || x >= basins.size() || y < 0 || y >= basins[0].size() || visited[x][y] || !basins[x][y])
        return 0;

    visited[x][y] = true;

    return 1 + bfs(basins, visited, x - 1, y) +
        bfs(basins, visited, x + 1, y) +
        bfs(basins, visited, x, y - 1) +
        bfs(basins, visited, x, y + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    int n = input.size(), m = input[0].size();
    vector<vector<bool>> basins(n, vector<bool>(m, true));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            basins[i][j] = (input[i][j] != '9');
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<int> sizes;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visited[i][j])
                continue;

            int size = bfs(basins, visited, i, j);
            if (size > 0) {
                sizes.push_back(size);
            }
        }
    }

    sort(sizes.begin(), sizes.end());
    int x = sizes.size();
    cout << sizes[x - 1] * sizes[x - 2] * sizes[x - 3];

    return 0;
}