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

vector<int> KMPSearch(string texto, string padrao){
    int nPadrao = padrao.size();
    int nTexto = texto.size();

    int *lps = calcLPS(padrao);
    int i = 0; //Iterador para texto
    int j = 0; //Iterador para padrao

    //O vetor resposta armazena indices de onde o padrao se repete
    vector<int> resposta;

    //Itera por todo o texto
    while(i < nTexto){
        if(padrao[j] == texto[i]){
            i++;
            j++;
        }
        if(j == nPadrao){
            resposta.push_back(i-j+1);
            j = lps[j-1];
        }else if(i < nTexto && padrao[j] != texto[i]){
            if(j != 0)
                j = lps[j - 1];
            else 
                i++;
        }
    }
    return resposta;
}

int main(){
    int n;
    cin >> n;
    string texto, padrao;
    for(int i = 0; i < n; i++){
        cin >> texto >> padrao;
        vector<int> resposta = KMPSearch(texto, padrao);
        if (resposta.empty()) 
            cout << "Not Found\n"; 
        else{ 
            cout << resposta.size() << "\n"; 
            for (int indice : resposta) 
                cout << indice << " "; 
            cout << "\n"; 
        }
        cout << "\n";
    }

    return 0;
}