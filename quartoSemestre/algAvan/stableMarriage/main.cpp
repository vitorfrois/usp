#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N;

int **readPreferences(){
    int **pref = (int **) malloc(sizeof(int*) * (N));
    for(int i = 0; i < (N); i++)
        pref[i] = (int *) malloc(sizeof(int) * N);
    
    
    for(int j = 0; j < N; j++){
        int person, value; 
        cin >> person;
        cout << person << " ";
        for(int k = 0; k < N; k++){
            cin >> value;
            cout << value << " ";
            pref[j][k] = value;
        }
        cout << endl;
    }
    cout << "retornando" << endl;
    return pref;
}

//return true if the woman with preferences q
//prefers m1 more than m2
bool preference(int *pref, int m1, int m2){
    for(int i = 0; i < N; i++){
        if(pref[i] == m1)
            return true;
        if(pref[i] == m2)
            return false;
    }
    return -1;
}

void stableMarriage(int **mPref, int **wPref){
    cout << "penis";
    int wPartner[N];

    bool mFree[N];

    memset(wPartner, -1, sizeof(wPartner));
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
                mFree[m] = true;
                freeCount--;
            }else{
                int m1 = wPartner[w];

                if(!preference(wPref[w], m, m1)){
                    wPartner[w] = m;
                    mFree[m] = true;
                    mFree[m1] = false;
                }
            }
        }
    }
    for(int i = 0; i < N; i++)
        cout << mPref[i] << " ";
    cout << endl;
    for(int i = 0; i < N; i++)
        cout << wPref[i] << " ";
    cout << endl;

}



int main(){
    int nTestCase = 0;
    cin >> nTestCase;
    for(int i = 0; i < nTestCase; i++){
        cin >> N;
        cout << N << endl;
        int **mPref = readPreferences();
        int **wPref = readPreferences();
        stableMarriage(mPref, wPref);       
    }


    return 0;
}