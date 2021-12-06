#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"

using namespace std;

#define CYCLE_LEN 7
#define FIRST_CYCLE_DELAY 2
#define FIRST_CYCLE_LEN (CYCLE_LEN + FIRST_CYCLE_DELAY)
#define DAYS_COUNT 256

int main() {
    ios_base::sync_with_stdio(false);
    vector<string> input = read_input();

    vector<int> initial_fish = str_vec_to_int(split_str(input[0], ','));
    vector<u_int64_t> fish(FIRST_CYCLE_LEN, 0);

    for (auto f : initial_fish) {
        fish[f]++;
    }

    for (int i = 0; i < DAYS_COUNT; i++) {

        u_int64_t ready_fish = fish[0];

        for (int j = 0; j < FIRST_CYCLE_LEN - 1; j++) {
            fish[j] = fish[j + 1];
        }

        fish[FIRST_CYCLE_LEN - 1] = ready_fish;
        fish[CYCLE_LEN - 1] += ready_fish;

    }

    u_int64_t result = 0;

    for (int i = 0; i < FIRST_CYCLE_LEN; i++)
        result += fish[i];

    cout << result;

    return 0;
}