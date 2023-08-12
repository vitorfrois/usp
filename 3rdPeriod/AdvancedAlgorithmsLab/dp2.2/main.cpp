#include <iostream>
#include <cstring>

using namespace std;

const int MAX_W = 1e5;
const int MAX_N = 100;

typedef struct KNAPSACK{
    //values can reach up to 1e9, so its important
    //to mark as long long int
    long long int value[MAX_N]; 
    int weight[MAX_W];
}Knapsack;

Knapsack itens;
//memoization matrix
long long int memo[MAX_N][MAX_W];

int n;


long long int solve(int i, int bagWeight){
    if(i == n) return 0;
    if(memo[i][bagWeight] != -1) return memo[i][bagWeight];
    long long int ret = 0;

    //if the itens can hold the weight, computate it
    if(bagWeight >= itens.weight[i]) 
        ret = max<long long int>(ret, itens.value[i] + solve(i+1, bagWeight - itens.weight[i]));
    //then computate the maximum between those two values
    ret = max<long long int>(ret, solve(i+1, bagWeight));
    
    memo[i][bagWeight] = ret;
    return ret;
}

int main(){
    int bagWeight;
    cin >> n >> bagWeight;
    for(int i = 0; i < n; i++)
        cin >> itens.weight[i] >> itens.value[i];

    for(int i = 0; i < MAX_N; i++)
        for(int j = 0; j < MAX_W; j++)
            memo[i][j] = -1;

    cout << solve(0, bagWeight);

    return 0;
}