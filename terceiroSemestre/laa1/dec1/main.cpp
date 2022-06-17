#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int Tn, n;
	cin >> Tn;	
	n = (int)(-1+sqrt(1+8*Tn))/2; 
 	cout << n;		
	return 0;
}
