#include <iostream>
#include <queue>

using namespace std;

int main(){
	int nCasos, nJobs, jobIndex;
	cin >> nCasos;
	for(int i = 0; i < nCasos; i++){
		cin >> nJobs >> jobIndex;
		int n, timeElapsed = 0;
		queue<int> q;
		priority_queue<int> pq;
		for(int j = 0; j < nJobs; j++){
			cin >> n;
			q.push(n);
			pq.push(n);
		}
		while(jobIndex != -1){		
			if(q.front() == pq.top()){
				q.pop();
				pq.pop();
				jobIndex--;
				timeElapsed++;
			}else{
				q.push(q.front());
				q.pop();
				if(jobIndex == 0) jobIndex = q.size() - 1;
				else jobIndex--;
			}
		}
		cout << timeElapsed << endl;
	}
	return 0;	
}
