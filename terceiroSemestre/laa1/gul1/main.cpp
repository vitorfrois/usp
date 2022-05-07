#include <iostream>
#include <queue>

using namespace std;

//A function that returns -1 or moneySpent on knight
//acording to Loowater fate
int saveLoowater(
    priority_queue<int, vector<int>, greater<int>> dragonHeadsSize, 
    priority_queue<int, vector<int>, greater<int>> knightsHeight)
    {

    int moneySpent = 0;
    while(!dragonHeadsSize.empty()){
        if(knightsHeight.empty()) return -1;
        if(dragonHeadsSize.top() > knightsHeight.top()){
            knightsHeight.pop();
        }else{
            moneySpent += knightsHeight.top();
            dragonHeadsSize.pop();
            knightsHeight.pop();
        }
    }  
    return moneySpent;  
}

int main(){
    int numDragonHeads, numKnightsHeight, input;
    cin >> numDragonHeads >> numKnightsHeight;
    while(numDragonHeads != 0 && numKnightsHeight != 0){
        priority_queue<int, vector<int>, greater<int>> dragonHeadsSize;
        for(int i = 0; i < numDragonHeads; i++){
            cin >> input;
            dragonHeadsSize.push(input);
        }
        priority_queue<int, vector<int>, greater<int>> knightsHeight;
        for(int i = 0; i < numKnightsHeight; i++){
            cin >> input;
            knightsHeight.push(input);
        }
        int moneySpent = saveLoowater(dragonHeadsSize, knightsHeight);
        if(moneySpent == -1) cout << "Loowater is doomed!" << endl;
        else cout << moneySpent << endl;
        cin >> numDragonHeads >> numKnightsHeight;
    }

    return 0;
}
