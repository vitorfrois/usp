#include <iostream>
#include <vector>

#define VERBOSE true

using namespace std;

int maxValue;

typedef struct square{
	int column;
	int row;
	int value;
}Square;

void printBoard(vector<Square> queens){
	vector<vector<char>> board(8, vector<char>(8, 'x'));
	for(auto queen : queens)
		board[queen.column][queen.row] = 'o';

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

bool queensCollide(vector<Square> queens, Square s){
	bool collide = false;
	//check rows
	for(auto queen : queens){
		//checking rows and columns
		if(queen.row == s.row) collide = true;
		if(queen.column == s.column) collide = true;
		//checking diagonals
		if(abs(queen.row - s.row) == abs(queen.column - s.column)) collide = true;
	}
	return collide;
}

bool solveTheQueen(vector<Square> queens, vector<vector<int>> board, int queensSum, int nQueens){
	// printBoard(queens);
	if(nQueens == 8){
		if(queensSum > maxValue)
			maxValue = queensSum;
		return false;
	} 
	for(int i = 0; i < 8; i++){
		Square s;
		s.column = nQueens; s.row = i;
		s.value = board[s.column][s.row];
		if(!queensCollide(queens, s)){
			queens.push_back(s);
			queensSum += s.value;
			if(solveTheQueen(queens, board, queensSum, nQueens+1))
				return true;
			queensSum -= s.value;
			queens.pop_back();
		}			
	}
	return false;
}

int main(){
	int nBoards;
	cin >> nBoards;
	for(int i = 0; i < nBoards; i++){
		//read the board
		int squareValue;
		vector<vector<int>> board(8, vector<int>(8,0));
		for(int c = 0; c < 8; c++){
		for(int r = 0; r < 8; r++){
			cin >> squareValue;
			board[c][r] = squareValue;
			}
		}
		vector<Square> queens;
		int queensSum = 0;
		solveTheQueen(queens, board, queensSum, 0);
		printf("%5d\n", maxValue);
		maxValue = 0;		
	}
	return 0;
}
