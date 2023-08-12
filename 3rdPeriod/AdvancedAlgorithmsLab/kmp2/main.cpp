#include <ios>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief computates longest prefix that is also a suffix
 * 
 * @param padrao 
 * @return int 
 */
int *calcLPS(string padrao){
    //Tamanho do maior lps 
    int len = 0;
    int padraoSize = padrao.size();
    
    int *lps = (int*) malloc(sizeof(int) * padraoSize);
    //lps[0] é sempre 0
    lps[0] = 0;

    int i = 1;
    while(i < padraoSize){
        if(padrao[i] == padrao[len]){
            len++;
            lps[i] = len;
            i++;
        }else{
            if(len != 0){
                len = lps[len-1];
            }else{
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int main(){
    int n;
    cin >> n;
    string nome;
    int nNome;
    for(int i = 0; i < n; i++){
        cin >> nome >> nNome;
        int tNome = nome.size();
        int *lps = calcLPS(nome);
        int resultado = ((tNome-lps[tNome-1])*nNome) + lps[nome.size()-1];
        cout << resultado << endl;
    }

    return 0;
}