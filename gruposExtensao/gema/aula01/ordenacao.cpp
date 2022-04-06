#include <iostream>
#include <queue>

using namespace std;

int main(){
	priority_queue<int> pq;
	int n;
	for(int i = 0; i < 3; i++){
		cin >> n;
		pq.push(n);
	}
	while(!pq.empty()){
		cout << pq.top() << endl;
		pq.pop();
	}
	return 0;
}


