#include <iostream>
#include <stack>
#include <string>

#define VERBOSE true
using namespace std;
typedef long long int llint; 

int main(){
    int nEquations;
    cin >> nEquations;
    for(int i = 0; i < nEquations; i++){
        llint num, ubTemp = 0, lbTemp = 0;
        char sign = '1', oldSign = 'f';
        stack<llint> upperBound;
        stack<llint> lowerBound;
        while(sign != '\n' && sign != EOF){
            cin >> num;
            sign = getchar();
            if(oldSign == '+'){
                lowerBound.push(lbTemp);
                lbTemp = num;

                if(ubTemp != 0) ubTemp += num;
                else ubTemp = num;
            }else if(oldSign == '*'){
                upperBound.push(ubTemp);
                ubTemp = num;

                if(lbTemp != 0) lbTemp *= num;
                else lbTemp = num;
            }else if(oldSign == 'f'){ //f stands for first iteration
                ubTemp = num;
                lbTemp = num;
            }
            oldSign = sign;
        }
        upperBound.push(ubTemp);
        lowerBound.push(lbTemp);
        llint ubResult = 1;
        while(!upperBound.empty()){
            ubResult *= upperBound.top();
            upperBound.pop();
        }

        llint lbResult = 0;
        while(!lowerBound.empty()){
            lbResult += lowerBound.top();
            lowerBound.pop();
        }
        cout << "The maximum and minimum are " << ubResult << " and " << lbResult << "." << endl;
    }

    return 0;
}