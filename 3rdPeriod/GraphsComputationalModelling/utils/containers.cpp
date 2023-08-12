#include "containers.h"

void printMatrix(int **matrix, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void printList(list<int> const &list){
	cout << "(";
    for (auto const &i: list) {
        cout << i << ',';
    }
	cout << ")" << endl;
}

void printSet(set<int> const &set){
	cout << "(";
    for (auto const &i: set) {
        cout << i << ',';
    }
	cout << ")" << endl;
}

int printStack(stack<int> s, int value){
    if (s.empty())
        return false;
     
    int x = s.top();
    if(x == value) return true;
	s.pop();
	return printStack(s, value);
}
