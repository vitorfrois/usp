#include <iostream>
#include <cstring>

#define MAX 1000
#define WALL '#'
#define EMPTY '.'

using namespace std;

int H, W;
char path[MAX+1][MAX+1];
typedef long long int lli;
lli MOD = 1e9+7;
lli count = 0;

lli memo[MAX+1][MAX+1];

lli pathCalc(int x, int y, lli count){
    //cout << "x,y = " << x << " " << y << endl;

    if(memo[x][y] != -1)
        return memo[x][y];

    if(path[x][y] == WALL)
        return count;
    
    if(x > H || y > W)
        return count;

    if(x == H && y == W)
        return count + 1;
    
    lli right = pathCalc(x+1, y, count);
    lli down = pathCalc(x, y+1, count);
    memo[x][y] = (right + down) % MOD;
    return memo[x][y];
}

int main(){
    memset(memo, -1, sizeof(memo));
    cin >> H >> W;
    for(int i = 1; i <= H; i++){
        for(int j = 1; j <= W; j++){
            cin >> path[i][j];
        }
    }
        


    cout << pathCalc(1, 1, 0);
    
    return 0;
}
