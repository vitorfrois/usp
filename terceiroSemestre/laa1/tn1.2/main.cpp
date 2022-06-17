#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector <int> vi;
typedef set <int> si; 
typedef long long ll;

//This function computates the result of A subsets
//members multiplication 
void subsetsUtil(vi& A, si& res, vi& subset, int index){
    int divisor = 1;
    for(vi::iterator it = subset.begin(); it != subset.end(); it++)
        divisor *= *it;
    res.insert(divisor);
    for (int i = index; i < (int) A.size(); i++) {
        // include the A[i] in subset.
        subset.push_back(A[i]);
        // move onto the next element.
        subsetsUtil(A, res, subset, i + 1);
        // exclude the A[i] from subset and triggers
        // backtracking.
        subset.pop_back();
    }
 
    return;
}

//returns a vector of prime factors of N
vi primeFactors(ll N){
    vi factors;
    ll i = 2;
    while(N != 1 && i * i <= N) {
        while(N % i == 0){
            N /= i;
            factors.push_back(i);
        }
        i++;
    }
    if(N != 1) factors.push_back(N);
    return factors;
}

si divisorsCalc(vi primeFactors){
    si divisors;
    vi subset;
    int index = 0;
    subsetsUtil(primeFactors, divisors, subset, index);
    return divisors;
}

//print vector
void printVector(vi vec){
    for(vi::iterator i = vec.begin(); i != vec.end(); i++)
        cout << *i << ' ';
}

//print set
void printSet(si s){
    for(si::iterator i = s.begin(); i != s.end(); i++)
        cout << *i << ' ';
}

int main(){
    ll N;
    cin >> N;
    vi factors = primeFactors(N);
    si divisors = divisorsCalc(factors);    
    // printSet(divisors);
    
    return 0;
}