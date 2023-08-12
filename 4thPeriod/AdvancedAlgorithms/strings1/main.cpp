#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    bool endOfWord;
    int n;
};

struct TrieNode *getNode(){
    struct TrieNode *newNode = new TrieNode;
    newNode->endOfWord = false;
    newNode->n = 0;   

    for(int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;

    return newNode;
}

void insert(struct TrieNode *root, string key){
    struct TrieNode *aux = root;

    for(int i = 0; i < (int) key.length(); i++){
        int index = key[i] - 'a';
        if(!aux->children[index])
            aux->children[index] = getNode();
        
        aux->n++;
        aux = aux->children[index];
    }
    aux->n++;
    aux->endOfWord = true;
}

bool search(struct TrieNode *root, string key){
    struct TrieNode *aux = root;

    for(int i = 0; i < (int) key.length(); i++){
        int index = key[i] - 'a';
        if(!aux->children[index])
            return false;

        aux = aux->children[index];
    }

    return aux->endOfWord;
}

int searchPrefix(struct TrieNode *root, string key){
    struct TrieNode *aux = root;

    for(int i = 0; i < (int) key.length(); i++){
        int index = key[i] - 'a';
        if(!aux->children[index])
            return 0;

        aux = aux->children[index];
    }
    if(aux->endOfWord == true)
        return aux->n;
    return 0;
}

void remove(struct TrieNode *root, string key){
    struct TrieNode *aux = root;

    for(int i = 0; i < (int) key.length(); i++){
        int index = key[i] - 'a';
        if(!aux->children[index])
            return; //word doesnt exist in list

        aux->n--;
        aux = aux->children[index];
    }
    aux->n--;
    aux->endOfWord = false;
}

int main(){
    int N, Q;
    string word;
    cin >> N;
    for(int i = 0; i < N; i++){
        struct TrieNode *root = getNode();
        cin >> word;
        insert(root, word);
    }
    for(int i = 0; i < Q; i++){
        cin >> word;
        cout << searchPrefix(root, word) << endl; 
    }

    return 0;
}