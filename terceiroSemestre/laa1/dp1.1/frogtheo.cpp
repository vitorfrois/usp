/**
 * @file main.cpp
 * @author Théo Riffel (theobfriffel@usp.br)
 * @brief dinamic programming frog
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <climits>

using namespace std;

vector <int> heigths;
int qnt_rocks;

int dp(int i, int memo[]) {

    if (i >= qnt_rocks - 1) return 0;
    if (memo[i] != -1) return memo[i];

    int ret = INT_MAX;

    ret = min(ret, abs(heigths[i] - heigths[i+1]) + dp(i + 1, memo));
    if (i + 2 < qnt_rocks)
        ret = min(ret, abs(heigths[i] - heigths[i+2]) + dp(i + 2, memo));

    memo[i] = ret;

    return ret;
}

int main(){

    int height, cost;
    cin >> qnt_rocks;

    int memo[qnt_rocks];
    memset(memo, -1, sizeof(memo));

    for (int i = 0; i < qnt_rocks; i++){
        cin >> height;
        heigths.push_back(height);
    }

    cost = dp(0, memo);

    cout << cost << endl;

    return 0;
}
