#include <iostream>

using namespace std;

#define MAX 1e4
int plans[MAX][3];
int n;

int happinessCalc(int i){
	if(i == n) return 0;
	int ret = max(
		plans[i][0],
		plans[i][1],
		plans[i][0]);
	return max + happinessCalc(i+1);
	


}

int main(){
	cin << n;
	int a, b, c;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 3; j++){
			cin << plans[i][j];
		}	
	}
	
	cout << happinessCalc(0);	
	

	return 0;
}
