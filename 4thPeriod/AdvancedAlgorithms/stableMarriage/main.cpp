#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<vector<int>> readPreferences(int N){
    vector<vector<int>> pref;
    
    for(int j = 0; j < N; j++){
        int person, value; 
        cin >> person;
        vector<int> v;
        for(int k = 0; k < N; k++){
            cin >> value;
            v.push_back(value - 1);
        }
        pref.push_back(v);
    }
    return pref;
}

//return true if the woman with preferences q
//prefers m1 more than m2
bool preference(vector<int> pref, int m1, int m2, int N){
    int i = 0;
    for(i = 0; i < N; i++){
        if(pref[i] == m1)
            return true;
        if(pref[i] == m2)
            return false;
    }
    cout << "uai";
    return true;
}

void stableMarriage(vector<vector<int>> mPref, vector<vector<int>> wPref, int N){
    int wPartner[N];
    int mPartner[N];

    bool mFree[N];

    memset(wPartner, -1, sizeof(wPartner));
    memset(mPartner, -1, sizeof(mPartner));

    memset(mFree, false, sizeof(mFree));
    int freeCount = N;
    while(freeCount > 0){
        int m;
        for(m = 0; m < N; m++)
            if(mFree[m] == false)
                break;
        
        for(int i = 0; i < N && mFree[m] == false; i++){
            int w = wPref[m][i];

            if(wPartner[w] == -1){
                wPartner[w] = m;
                mPartner[m] = w;
                mFree[m] = true;
                freeCount--;
            }else{
                int m1 = wPartner[w];
                if(!preference(wPref[w], m, m1, N)){
                    wPartner[w] = m;
                    mPartner[m] = w;
                    mFree[m] = true;
                    mFree[m1] = false;
                }
            }
        }
    }
    for(int i = 0; i < N; i++)
        cout << i+1 << " " << mPartner[i]+1 << endl;
}

int main(){
    int nTestCase = 0;
    int N;
    cin >> nTestCase;
    for(int i = 0; i < nTestCase; i++){
        cin >> N;
        vector<vector<int>> mPref = readPreferences(N);
        vector<vector<int>> wPref = readPreferences(N);
        stableMarriage(mPref, wPref, N);       
    }


    return 0;
}