#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<int> womanPref[500][500];
vector<int> manPref[500][500];
int finalManPref[500];
int N;

int **readPreferences(){
    int **pref = (int **) malloc(sizeof(int*) * N);
    for(int i = 0; i < )
    for(int j = 0; j < N; j++){
        int person, pref; 
        cin >> person;
        for(int k = 0; k < N; k++){
            cin >> pref;
            pref[k].push_back(pref);
        }
    }
}

int checkStable(int n){
    for(int i = 0; i < n; i++){
        if(finalManPref[i] == -1)
            return false;
    }
    return true;
}

//return true if the woman with preferences q
//prefers m1 more than m2
bool preference(vector<int> q, int m1, int m2){
    for(int m : q){
        if(m == m1)
            return true;
        if(m == m2)
            return false;
    }
}



int main(){
    int nTestCase = 0;
    cin >> nTestCase;
    for(int i = 0; i < nTestCase; i++){
        int N;
        cin >> N;
        memset(finalManPref, -1, N);
        
        
        for(int j = 0; j < N; j++){
            int person, pref; 
            cin >> person;
            for(int k = 0; k < N; k++){
                cin >> pref;
                manPref[k].push_back(pref);
            }
        }

        while(!checkStable(N)){
            for(int j = 0; j < N; j++){
                
            }
        }
        
    }


    return 0;
}