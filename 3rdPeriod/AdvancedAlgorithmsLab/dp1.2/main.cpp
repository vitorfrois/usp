#include <iostream>
#include <vector>

#define VERBOSE false

using namespace std;

void printVector(vector<int> sequence){
    for(auto i: sequence)
        cout << i << " ";
    cout << endl;
}

int f(vector<int> sequence, int i, int min, vector<vector<int>> &memoize){
    //if(VERBOSE) printVector(memoize);
    if(i == 0) return 1;
    i--;
    if(sequence[i] < min){
        if(memoize[i][min] == -1)
            memoize[i][min] = max(f(sequence, i, min, memoize), 1+f(sequence, i, sequence[i], memoize));
        return memoize[i][min];
    }
    if(memoize[i][min] != -1)
    	memoize[i][min] = f(sequence, i, min, memoize); 
    return memoize[i][min];
}

int main(){
    vector<int> sequence;
    int element, size;
    cin >> size;
    for(int i = 0; i < size; i++){
        cin >> element;
        sequence.push_back(element);
    }
    if(VERBOSE) cout << "vetor = ";
    if(VERBOSE) printVector(sequence);
    vector<vector<int>> memoize(size, vector<int> (10001, -1));
    cout << f(sequence, size, sequence.back(), memoize);
}
