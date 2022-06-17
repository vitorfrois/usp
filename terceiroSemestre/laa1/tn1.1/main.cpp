#include <iostream>

using namespace std;

typedef long long ll;

bool isPrime(ll N){
    if(N == 1) return false;
    if(N > 2 && N % 2 == 0) return false;
    for(ll i = 3; i * i <= N; i += 2)
        if(N % i == 0) return false;
    return true;
}


int main(){
    ll N;
    cin >> N;
    if(isPrime(N)) cout << "YES";
    else cout << "NO";
    return 0;
}