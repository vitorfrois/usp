#include <iostream>
#include <string>

using namespace std;

string play(string s){
    string ns;
    int size = s.size();
    for(int i = 0; i < size; i++){
        if(i % 2 == 0){
            if(s[i] == 'a')
                ns += 'b';
            else
                ns += 'a';
        }else{
            if(s[i] == 'z')
                ns += 'y';
            else
                ns += 'z';
        }
    }

    return ns;
}


int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        cout << play(s) << endl;
    }


    return 0;
}
