#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 1e5;

int memo[MAXN];
int n;
int height[MAXN];

long int path(int i){
    if(memo[i] != -1) 
        return memo[i];

    if(i+1 >= n){
        memo[i] = 0;
        return memo[i];
    }
    
    memo[i] = min(
            abs(height[i] - height[i+1]) + path(i+1),
            abs(height[i] - height[i+2]) + path(i+2));
    
    return memo[i];
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> height[i];
    
    memset(memo, -1, sizeof(memo));

    cout << path(0);

    return 0;
}
