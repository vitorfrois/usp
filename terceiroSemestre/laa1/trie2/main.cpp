#include <cstddef>
#include <cstdio>
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

void removeKey(struct TrieNode *root, string key){
    struct TrieNode *aux = root;

    for(int i = 0; i < (int) key.length(); i++){
        int index = key[i] - 'a';
        //consider that every key exists
        aux->n--;
        aux = aux->children[index];
    }
    aux->n--;
    aux->endOfWord = false;
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
    
    return aux->n;
}


int main(){
    int N, option;
    string word;
    struct TrieNode *root = getNode();
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> option;
        cin >> word;
        if(option == 1)
            insert(root, word);
        if(option == 2)
            removeKey(root, word);
        if(option == 3)
            cout << searchPrefix(root, word) << endl;
    }

    return 0;
}
