#include <iostream>
#include <cmath>

using namespace std;

int printPowerSet(int* set, int set_size){
    
    // Set_size of power set of a set with set_size
    // n is (2^n-1)
    int nSubsets = pow(2, set_size);
    int result = 0, partialResult = 0;
    // Run from i 000..0 to 111..1
    for (int i = 0; i < nSubsets; i++) {
        for (int j = 0; j < set_size; j++) {
            // Check if jth bit in the i is set
            // If set then print jth element from set
            if (i & (1 << j)){
                // cout << set[j] << ",";
                if(partialResult != 0)
                    partialResult = partialResult xor set[j];
                else
                    partialResult = set[j];
            }
        }
        result += partialResult;
        partialResult = 0;
    }
    return result;
}

int main(){
    int setSize;
    cin >> setSize;
    int set[setSize];
    for(int i = 0; i < setSize; i++)
        cin >> set[i];
    
    cout << printPowerSet(set, setSize);
    
    return 0;
}

