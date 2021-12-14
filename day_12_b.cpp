#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

// using globals cuz i'm lazy and also this algorithm sucks it's slow af ugh

map<int, vector<int>> graph;
map<string, int> node_ids;
vector<bool> lowercase;
int result = 0;

bool contains(vector<int>& vec, int n) {
    for (int el : vec) {
        if (el == n)
            return true;
    }
    return false;
}

bool is_lowercase(string& str) {
    for (char c : str) {
        if (c < 'a' || c > 'z')
            return false;
    }
    return true;
}

bool has_two_same_small(vector<int> path) {
    sort(path.begin(), path.end());

    for (int i = 1; i < path.size(); i++) {
        if (path[i] == path[i - 1] && lowercase[path[i]])
            return true;
    }

    return false;
}

void find_paths(vector<int>& path, int v) {
    if (v == node_ids["end"]) {
        result++;
        return;
    }

    for (int adj : graph[v]) {
        if (lowercase[adj] && contains(path, adj) && has_two_same_small(path))
            continue;

        vector<int> new_path = path;
        new_path.push_back(adj);
        find_paths(new_path, adj);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    int first_free_id = 0;

    for (const string& line : input) {
        vector<string> edge = split_str(line, '-');

        for (int i = 0; i < 2; i++) {
            if (!node_ids.contains(edge[i])) {
                lowercase.push_back(is_lowercase(edge[i]));
                node_ids.emplace(edge[i], first_free_id++);
            }

            if (!graph.contains(node_ids[edge[i]]))
                graph.emplace(node_ids[edge[i]], vector<int>());
        }

        int id1 = node_ids[edge[0]];
        int id2 = node_ids[edge[1]];

        if (edge[1] != "start")
            graph[id1].push_back(id2);
        if (edge[0] != "start")
            graph[id2].push_back(id1);
    }

    int begin = node_ids["start"];
    vector<int> init_path = { begin };
    find_paths(init_path, begin);

    cout << result;

    return 0;
}
