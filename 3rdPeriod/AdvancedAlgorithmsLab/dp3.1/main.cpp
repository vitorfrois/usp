#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LENGTH = 2000;
char M[MAX_LENGTH];
char N[MAX_LENGTH];

int letterWeight[26];
int mLenght, nLenght;
int memo[MAX_LENGTH][MAX_LENGTH];

int solve(int mIt, int nIt){
    //se tiver chegado ao final da string, retorna 0
    if(mIt == mLenght || nIt == nLenght)
        return 0;
    
    // cout << mIt << " " << nIt << endl;
    if(memo[mIt][nIt] != -1) return memo[mIt][nIt];

    //caso os caracteres sejam iguais, retorna 1 + chamada recursiva
    else if(M[mIt] == N[nIt])
        memo[mIt][nIt] = (letterWeight[M[mIt]-97] + solve(mIt + 1, nIt + 1));
    //caso contrário retorna o máximo entre andar com um ou outro
    else
        memo[mIt][nIt] = max(solve(mIt + 1, nIt), solve(mIt, nIt + 1));

    return memo[mIt][nIt];
}

int main(){
    cin >> mLenght >> nLenght;
    for(int i = 0; i < 26; i++)
        cin >> letterWeight[i];

    for(int i = 0; i < mLenght; i++)
        cin >> M[i];    

    for(int i = 0; i < nLenght; i++)
        cin >> N[i];

    memset(memo, -1, sizeof(memo));

    cout << solve(0, 0);

    return 0;
}
