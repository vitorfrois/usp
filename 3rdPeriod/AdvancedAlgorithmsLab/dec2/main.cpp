#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iterator>

#define VERBOSE false

using namespace std;
bool slice(vector<int> arr, int num, int begin, int end){
	if(VERBOSE) cout << "begin = " << begin << " and end = " << end << endl;
	int soma = 0;
	for(int i = begin; i <= end; i++)
		soma += arr[i];
	if(VERBOSE) {
		for(int i = begin; i <= end; i++)
			cout << arr[i];
		cout << endl;
	}
	if(soma == num) return true;
	if(end - begin < 1) return false;

	int max, min, mean;
	max = arr[end];
	min = arr[begin];
	mean = (max+min)/2;
	int j = begin;
	if(VERBOSE) cout << mean << max << min << endl;
	while(j < end && arr[j+1] <= mean)
		j++;
	if(end == j) return false;
	return (slice(arr, num, begin, j) || slice(arr, num, j+1, end));
}	

int main(){
	int nTestCases;
	cin >> nTestCases;
	int arrLenght, nPrettinessTests;
	int contents;
	for(int i = 0; i < nTestCases; i++){
		cin >> arrLenght >> nPrettinessTests;
		vector<int> arr;
		vector<int> numbers;
		for(int j = 0; j < arrLenght; j++){
			cin >> contents;
			arr.push_back(contents);
		}
		sort(arr.begin(), arr.end());

		for(int j = 0; j < nPrettinessTests; j++){
			cin >> contents;
			if(VERBOSE) cout << "Procurando para " << contents << endl;
			if(slice(arr, contents, 0, arrLenght-1)) cout << "Yes";
			else cout << "No";
			cout << endl;
		}
		
	}
	return 0; 
}
