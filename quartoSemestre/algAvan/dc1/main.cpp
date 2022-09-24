#include <iostream>
#include <list>

using namespace std;

int main(){
	int nCases;
	cin >> nCases;
	for(int i = 0; i < nCases; i++){
		int lenght, elem; 
		cin >> lenght;
		list<int> numbers;
		list<int>::iterator it;
		int s = 0;
		for(int j = 0; j < lenght; j++){
			int k = 0;
			cin >> elem;
			it = numbers.begin();
			while(it != numbers.end() && elem > *it){
				it++; 
				k++;
			}

			// cout << numbers.size() << ";" << k << " ";
			s += (j - k);
			numbers.insert(it, elem);
			// cout << s << endl;
		}
		cout << s << endl;

	}
	return 0;
}
