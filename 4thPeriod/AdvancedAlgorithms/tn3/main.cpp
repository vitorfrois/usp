#include <iostream>
#include <vector>
using namespace std;

int theNumber = 131071;

int CheckDivisibility(vector<char> bitSequence){
	int remainder = 0;
	for(char bit : bitSequence){
		// Update remainder
		if (bit == '1')
			remainder = (remainder * 2 + 1) % theNumber;
		if (bit == '0')
			remainder = (remainder * 2) % theNumber;
	}
    // If remainder is 0.
    if (remainder % theNumber == 0)
        return true;
    else
        return false;

}

int main(){
    char bit;
    vector<char> bitSequence;
    while(cin >> bit){
        if(bit != '\n' && bit != '#')
            bitSequence.push_back(bit);
        if(bit == '#'){
            // cout << bitSequence << endl;
            if(CheckDivisibility(bitSequence))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            bitSequence.clear();
        }
    }
	return 0;
}
