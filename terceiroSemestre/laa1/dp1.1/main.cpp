#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 1e6;
int height[MAXN], n;
int memo[MAXN];

void printSpace(int n){
	cout << n;
	for(int i = 0; i < n; i++)
		cout << " ";
}

int frogPath(int height[], int N, int i){
	if(i+1 >= N) return 0;
	if(memo[i] != -1) return memo[i];

	int retorno = INT_MAX;
	retorno = min(retorno, abs(height[i] - height[i+1]) + frogPath(height, N, i+1));
	retorno = i+2 > N? 0 : min(retorno, abs(height[i] - height[i+2]) + frogPath(height, N, i+2));
	// int b = INT_MAX;
	// cout << "a & b = " << a << " " << b << endl;
	memo[i] = retorno;
	return retorno;
	// cout << "returning " << minValue << endl;

}

int main(){
	int N;		
	cin >> N;
   	int height[N];
	for(int i = 0; i < N; i++)
		cin >> height[i];

	memset(memo, -1, sizeof(memo));

	cout << frogPath(height, N, 0);	
	return 0;
}
