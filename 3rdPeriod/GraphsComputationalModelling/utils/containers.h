#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <stack>

using namespace std;

void printMatrix(int **matrix, int size);
void printList(list<int> const &list);
void printSet(set<int> const &set);
int printStack(stack<int> s, int value);

#endif
