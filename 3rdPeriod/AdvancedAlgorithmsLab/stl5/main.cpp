#include <iostream>
#include <queue>

using namespace std;
#define VERBOSE false

int main(){
    priority_queue <int, vector<int>, greater<int>> pq;
    int n, entrada;
    cin >> n;
    do{
        for(int j = 0; j < n; j++){
            cin >> entrada;
            pq.push(entrada);
        }
        int cost = 0, a, b;
        do{
            a = pq.top(); pq.pop();
            b = pq.top(); pq.pop();
            if(VERBOSE) cout << "a=" << a << " b=" << b << endl;
            cost += a+b;
            pq.push(a+b);
            if(VERBOSE) cout << "cost: " << cost << endl;
        }while(pq.size() != 1);
        cout << cost << endl;
        pq.pop();
        cin >> n;
    }while(n != 0);

    return 0;
}