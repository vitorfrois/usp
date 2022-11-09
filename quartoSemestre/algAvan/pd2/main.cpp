#include <iostream>
#include <cstring>

using namespace std;

int n;
int days[300];
int x, y, z;

int memo[300];

int travel(int totalDays, int i){
    while(i < n && totalDays > days[i])
        i++;
    
    if(i == n) memo[i] = 0;

    if(memo[i] != -1)
        return memo[i];
    
    totalDays = days[i];

    memo[i] = min(x + travel(totalDays+1, i), y + travel(totalDays+7, i));
    memo[i] = min(memo[i], z + travel(totalDays+30, i));

    return memo[i];
}

int main(){
    cin >> n;
    cin >> x >> y >> z;
    for(int i = 0; i < n; i++)
        cin >> days[i];
    memset(memo, -1, sizeof(memo));
    cout << travel(0, 0);
    return 0;
}

