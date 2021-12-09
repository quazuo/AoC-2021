#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

#define PART 2

int cost(int dist) {
    return PART == 1 ? dist : dist * (dist + 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();
    vector<int> crabs = str_vec_to_int(split_str(input[0], ','));
    int leftmost = *(min_element(crabs.begin(), crabs.end()));
    int rightmost = *(max_element(crabs.begin(), crabs.end()));
    int best_cost = INT32_MAX;

    for (int pos = leftmost; pos <= rightmost; pos++) {

        int fuel_cost = 0;

        for (int crab : crabs) {
            fuel_cost += cost(abs(pos - crab));
        }

        best_cost = min(fuel_cost, best_cost);

    }

    cout << best_cost;

    return 0;
}