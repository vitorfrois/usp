#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printVector(vector<int> array){
    for(vector<int>::iterator it = array.begin(); it != array.end(); it++)
        cout << *it << " ";
    cout << endl;
}

int main(){
    int queries;
    cin >> queries;
    
    for(int i = 0; i < queries; i++){
        // cout << "query " << i << endl;
        int n;
        cin >> n;
        vector<int> m0;
        vector<int> m1;
        vector<int> m2;
        for(int j = 0; j < n; j++){
            int elem;
            cin >> elem;
            if(elem % 3 == 0) m0.push_back(elem);
            if(elem % 3 == 1) m1.push_back(elem);
            if(elem % 3 == 2) m2.push_back(elem);
        }
        // sort(array.begin(), array.end());
        
        while((m1.size() != 0 && m2.size() != 0) || m1.size() >= 3 || m2.size() >= 3){
            // cout << "iteration: " << endl;
            
            if(m1.size() != 0 && m2.size() != 0){
                m0.push_back(m1.back() + m2.back());
                m1.pop_back(); m2.pop_back();
            }else if(m2.size() == 0){
                int n = 0;
                for(int i = 0; i < 3; i++){
                    n += m1.back();
                    m1.pop_back();
                }
                m0.push_back(n);
            }else if(m1.size() == 0){
                int n = 0;
                for(int i = 0; i < 3; i++){
                    n += m2.back();
                    m2.pop_back();
                }
                m0.push_back(n);
            }
        }
        cout << m0.size() << endl;
        m0.clear();
        m1.clear();
        m2.clear();
    }



    return 0;
}