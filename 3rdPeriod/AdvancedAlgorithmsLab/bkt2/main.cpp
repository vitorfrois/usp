#include <iostream>

using namespace std;

bool recursiveSearch(char **matrix, bool **path, char *word, int wordSize, int index, int i, int j){
    index++;
    path[i][j] = true;
    // cout << matrix[i][j];
    // cout << "estou em " << i << " " << j << endl;
    if(index == wordSize)
        return true;
    bool result = false;
    if(matrix[i+1][j] == word[index] && path[i+1][j] == false)
        result = recursiveSearch(matrix, path, word, wordSize, index, i+1, j);
    if(result) return true;

    if(matrix[i][j+1] == word[index] && path[i][j+1] == false)
        result = recursiveSearch(matrix, path, word, wordSize, index, i, j+1);
    if(result) return true;

    if(matrix[i-1][j] == word[index] && path[i-1][j] == false)
        result = recursiveSearch(matrix, path, word, wordSize, index, i-1, j);
    if(result) return true;

    if(matrix[i][j-1] == word[index] && path[i][j-1] == false)
        result = recursiveSearch(matrix, path, word, wordSize, index, i, j-1);
    if(result) return true;

    path[i][j] = false;
	// cout << endl;

    return false;
}

bool searchWord(char **matrix, bool **path, char *word, int wordSize, int m, int n){
    bool result;
    int index = 0;
    for(int i = 1; i < (m+1); i++){
        for(int j = 1; j < (n+1); j++){
            if(matrix[i][j] == word[index]){
                //recursive call
                result = recursiveSearch(matrix, path, word, wordSize, index, i, j);
                if(result == true) return true;
                else index = 0;
            }
            // for(int x = 0; x < (m+2); x++){
            //     for(int y = 0; y < (n+2); y++){
            //         // cout << ((path[x][y] == true)? 1:0);
            //         // path[x][y] = false;
            //     }
            //     // cout << endl;
            // }
            // cout << endl;
        }
    }
    return false;
}

int main(){
    int m, n, i, j;
    cin >> m >> n;
    //creates and add paddings to a matrix;
    char **matrix = (char**) malloc(sizeof(char*) * (m+2));
    for(i = 0; i < (m+2); i++)
        matrix[i] = (char*) malloc(sizeof(char) * (n+2));

    for(i = 0; i < (m+2); i++)
        for(j = 0; j < (n+2); j++)
            matrix[i][j] = '0';

    //creates a matrix for visited path
    bool **path = (bool**) malloc(sizeof(bool*) * (m+2));
    for(i = 0; i < (m+2); i++)
        path[i] = (bool*) malloc(sizeof(bool) * (n+2));

    for(i = 0; i < (m+2); i++)
        for(j = 0; j < (n+2); j++)
            path[i][j] = false;

    //reads char matrix
    char input;
    for(i = 1; i < (m+1); i++){
        for(j = 1; j < (n+1); j++){
            cin >> input;
            matrix[i][j] = input;
        }
    }

    int wordSize;
    cin >> wordSize;
    char *word = (char*) malloc(sizeof(char) * wordSize);
    // cout << "searching for: ";
    for(i = 0; i < wordSize; i++){
        cin >> input;      
        word[i] = input;
    }
    
    //executes search function
    if(searchWord(matrix, path, word, wordSize, m, n)) cout << "Yes";
    else cout << "No";


    //free
    for(i = 0; i < (m+2); i++)
        free(matrix[i]);
    free(matrix);

    for(i = 0; i < (m+2); i++)
        free(path[i]);
    free(path);

    free(word);

}
