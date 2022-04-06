#include <iostream>

using namespace std;

int main(){
	int area, n, m;
	cin >> n >> m;
	area = n * m;
	if(area % 2 == 0) cout << area/2;
	else cout << (area/2)+1;
	return 0;
}
