#include <iostream>
#include <set>
#include <queue>

using namespace std;
bool verbose = false;

void clear(queue<int> &q){
   queue<int> empty;
   swap(q, empty);
}

int main(){
    int casosTeste, totalFlocos;
    cin >> casosTeste;
    for(int i = 0; i < casosTeste; i++){
        cin >> totalFlocos;
        set<int> pacote;
        queue<int> fila;
        int tamanhoFloco, tamanhoAtualPacote = 0, tamanhoMaxPacote = 1;
        if(totalFlocos == 0) tamanhoMaxPacote = 0;
        for(int j = 0; j < totalFlocos; j++){
            cin >> tamanhoFloco;
            if(verbose) cout << "o floco é de tamanho " << tamanhoFloco << endl;
            if(pacote.find(tamanhoFloco) == pacote.end()){
                pacote.insert(tamanhoFloco);
                fila.push(tamanhoFloco);
                if(verbose) cout << "inseri " << tamanhoFloco << endl;
                tamanhoAtualPacote++;
            }else{
                
                fila.push(tamanhoFloco);
                // tamanhoAtualPacote++;
                while(fila.front() != tamanhoFloco){
                    if(verbose) cout << "retirei " << fila.front() << endl;
                    pacote.erase(fila.front());
                    fila.pop();
                    tamanhoAtualPacote--;
                }
                if(verbose) cout << "retirei " << fila.front() << endl;
                fila.pop();
            }
            if(tamanhoAtualPacote > tamanhoMaxPacote) 
                tamanhoMaxPacote = tamanhoAtualPacote;
        }
        cout << tamanhoMaxPacote << endl;
        if(verbose) cout << endl;
        pacote.clear();
        clear(fila);
    }

    return 0;
}