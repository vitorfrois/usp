#include <iostream>
#include <set>

using namespace std;

int main(){
	int nCases;
	cin >> nCases;
	for(int i = 0; i < nCases; i++){
		int lenght, elem; 
		cin >> lenght;
		multiset<int> numbers;
		multiset<int>::iterator it = numbers.begin();
		int s = 0;
		for(int j = 0; j < lenght; j++){
			cin >> elem;
			it = numbers.insert(numbers.lower_bound(elem), elem);
			s += distance(it, numbers.end()) - 1;
			// cout << s << endl;
		}
		cout << s << endl;

	}
	return 0;
}
