#include <iostream>

using namespaces std;

int main(){
	int nChamber, nSpecimen;
	while(cin >> nChamber >> nSpecimen){
				int weight;
		vector<pair<int,int>> weightVec;
		for(int i = 0; i < nSpecimen; i++){
			cin >> weight;
			weightVec.push_back(make_pair(i, weight));
		}
	}

	return 0;
}
