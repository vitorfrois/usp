#include <iostream>

using namespace std;



int main(){
    int testCases;
    cin >> testCases;
    for(int i = 0; i < testCases; i++){
        int n, value;
        cin >> n;
        int series_result = 0;
        for(int j = 0; j < n; j++){
            cin >> value;
            series_result = series_result ^ value;
        }

        if(series_result == 0)
            cout << 1;
        else
            cout << 0;
        cout << endl;
    }
    return 0;
}
