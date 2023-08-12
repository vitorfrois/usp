#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 1e6;
int plans[MAX+1][3];
long int memo[MAX+1][3];
int n;
const long int INF = 1e6;

long int max3(long int a, long int b, long int c){
	long int ret = max(a, b);
	return max(ret, c);
}

long int happinessCalc(int i, int yesterday){
	if(i == n) return 0;
	if(yesterday != -1 && memo[i][yesterday] != -1)
		return memo[i][yesterday];

	long int res = 0;
	for(int j = 0; j < 3; j++)
		if(j != yesterday)
				res = max(res, plans[i][j] + happinessCalc(i+1, j));
	if(yesterday != -1) memo[i][yesterday] = res;
	return res;
}

int main(){
	cin >> n;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < 3; j++)
			cin >> plans[i][j];
	
	memset(memo, -1, sizeof(memo));
	cout << happinessCalc(0, -1);	
	

	return 0;
}
