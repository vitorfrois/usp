#include <iostream>
#include <vector>

using namespace std;

    int remainder(vector<int> n, int q){
        int mdc = n[0] % q;
        if(mdc < 0)
            mdc += q;
        for(auto i : n){
            int r = i%q;
            if(r < 0)
                r += q;
            //cout << mdc << " " << r << endl;
            if(mdc != r) return false;
            mdc = r;
        }
        return true;
    }

    int maxMod(vector<int> n, int s){
        for(int i = s; i > 1; i--){
            //cout << endl << i << endl;
            if(remainder(n, i))
                return i;
        }
        return 1;
    }

    int main(){
        int a;
        cin >> a;
        while(a != 0){
            vector<int> numbers;
            int smallest = a;
            do{
                if(abs(a) > smallest) smallest = abs(a);
                numbers.push_back(a);
                cin >> a;
            }while(a != 0);
            //cout << smallest << endl;
            cout << maxMod(numbers, smallest*2) << endl;
            cin >> a;
        }



}
