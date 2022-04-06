#include <iostream>

using namespace std;

int main(){
	int p;	
	cin >> p;
	if(p != 2){
		cout << 1 << endl;
		cout << (p/2)+1 << " " << (p/2);
	}else
		cout << 0;
	return 0;
}
