#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN], n;
int memo[MAXN];

int lis(int i){
	if(i >= n)
		return 0;
	if(memo[i] != 0)
		return memo[i];	
	memo[i] = 1;
	for(int j = i+1; j < n; j++)
		if(a[j] > a[i])
			memo[i] = max(memo[i], lis(j) + 1);
	
	lis(i+1);	
	return memo[i];
}

int main(){
	cin >> n;
	for(int i = 0; i < MAXN; i++)
		memo[i] = 0;	
	for(int i = 0; i < n; i++)
		cin >> a[i];
	
	lis(0);

	int maxn = -1;
	for(int i = 0; i < n; i++)
		maxn = max(maxn, memo[i]);
	cout << maxn;
	return 0;
}
