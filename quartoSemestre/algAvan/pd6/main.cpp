//edist
//smallest n of op to transform string a to b
//

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string A, B;
int aLength, bLength;

int memo[2000][2000];

int edist(int aIt, int bIt){
    //cout << A[aIt] << " = " << B[bIt] << endl;
    if(memo[aIt][bIt] != -1)
        return memo[aIt][bIt];

    while(A[aIt] == B[bIt] && aIt < aLength && bIt < bLength){ 
        aIt++; 
        bIt++;
    }

    if(aIt == aLength)
        return B.size() - bIt;

    if(bIt == bLength) 
        return A.size() - aIt;
   
    
    int minOp; 
    minOp = min(edist(aIt+1, bIt) + 1, edist(aIt, bIt+1) + 1);
    minOp = min(minOp, edist(aIt+1, bIt+1) + 1);
    memo[aIt][bIt] = minOp;
    return minOp;
        
}

int main(){
    int nTestCases;
    cin >> nTestCases;
    for(int i = 0; i < nTestCases; i++){
        memset(memo, -1, sizeof(memo));
        cin >> A;
        cin >> B;
        aLength = (int) A.length();
        bLength = (int) B.length();
        cout << edist(0, 0) << endl;
    }
    return 0;
}
