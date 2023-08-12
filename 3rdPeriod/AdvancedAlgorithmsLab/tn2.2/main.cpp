#include <iostream>

using namespace std;

int gcd(int a, int b){
	if(a == -1) return b;
	return b == 0? a : gcd(b, a % b);

}


int main(){
	int N;
	cin >> N;
	int cord[2];
	int distance, totalGCD = -1;
	int distances[N-1];
	cin >> cord[1];			
	for(int i = 0; i < N; i++){
		cord[0] = cord[1];
		cin >> cord[1];
		distance = abs(cord[0] - cord[1]);
		distances[i] = distance;
		totalGCD = gcd(totalGCD, distance);
	}

	int result = 0;
	for(int i = 0; i < N-1; i++){
		result += (distances[i]-1)/totalGCD;
	}

	cout << result;

	return 0;
}
