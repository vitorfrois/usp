#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const int MAX_LENGTH = 2000;
string M, N;

int mLenght, nLenght;
int memo[MAX_LENGTH][MAX_LENGTH];

string recover(){
    int i = 0, j = 0;
    string ret;
    while(i < mLenght && j < nLenght){
        if(memo[i][j] == memo[i+1][j]){
            i++;
        }else if(memo[i][j] == memo[i][j+1]){
            j++;
        }else{
            ret += M[i];
            i++, j++;
        }
    }
    return ret;
}

int solve(int mIt, int nIt){
    //se tiver chegado ao final da string, retorna 0
    if(mIt == mLenght || nIt == nLenght)
        return 0;
    
    // cout << mIt << " " << nIt << endl;
    if(memo[mIt][nIt] != -1) return memo[mIt][nIt];

    //caso os caracteres sejam iguais, retorna 1 + chamada recursiva
    else if(M[mIt] == N[nIt])
        memo[mIt][nIt] = (1 + solve(mIt + 1, nIt + 1));
    //caso contrário retorna o máximo entre andar com um ou outro
    else
        memo[mIt][nIt] = max(solve(mIt + 1, nIt), solve(mIt, nIt + 1));

    return memo[mIt][nIt];
}

int main(){
    cin >> M;
    cin >> N;
    mLenght = M.size();
    nLenght = N.size();

    memset(memo, -1, sizeof(memo));

    solve(0, 0);
    cout << recover();

    return 0;
}
