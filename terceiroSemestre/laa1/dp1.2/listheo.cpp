/**
 * @file main.cpp
 * @author Théo Riffel (theobfriffel@usp.br)
 * @brief Longest Increasing Subsequence - cpp file
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int lis(int i, vector <int> vec, vector <int> &memo){

    if (i >= (int) vec.size())
        return 0;
    if (memo[i] != 0)
        return memo[i];


    memo[i] = 1;
    for (ulong j = i + 1; j < vec.size(); j++)
        if (vec[j] > vec[i])
            memo[i] = max(memo[i], lis(j, vec, memo) + 1);
    
    lis(i + 1, vec, memo);

    return memo[i];
}

int main(){

    vector <int> vec, memo;
    int qnt_nums, num;
    cin >> qnt_nums;

    for (int i = 0; i < qnt_nums; i++){
        cin >> num;
        vec.push_back(num);
        memo.push_back(0);
    }

    lis(0, vec, memo);    

    int max_num = -1;
    for (int i = 0; i < qnt_nums; i++)
        max_num = max(max_num, memo[i]);

    cout << max_num << endl;

    return 0;
}
