#include <iostream>

using namespace std;

int main(){ 
    int x, y, oldX, oldY;
    int n;
    cin >> n;
    if(n < 3){
        cout << 0;
        return 0;
    }
    bool horizontalChange;
    cin >> oldX >> oldY;
    cin >> x >> y;
    if(oldX != x) horizontalChange == true;
    else horizontalChange == false;
    n --;
    int nDangerousPaths = 0;
    for(int i = 0; i < n; i++){
        oldX = x;
        oldY = y;
        cin >> x >> y;
        if(oldX != x && horizontalChange) nDangerousPaths++;
        else if(oldY != y && !horizontalChange) nDangerousPaths++; 
        if(oldX != x) horizontalChange == true;
        else horizontalChange == false;        
        
    }
    cout << nDangerousPaths;


    return 0;
}