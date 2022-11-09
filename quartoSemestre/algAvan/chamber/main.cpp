#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct chamberStruct{
    int index;
    int animals[2];
    int size;
    int totalWeight;
}Chamber;

Chamber initChamber(int index){
    Chamber c;
    c.index = index;
    c.size = 0;
    c.totalWeight = 0;
    return c;
}

Chamber increaseWeight(Chamber c, int weight){
    c.totalWeight += weight;
    c.animals[c.size] = weight;
    c.size++;
    return c;
}

bool sortChamberWeight(const Chamber &a, const Chamber &b){
    if(a.size != b.size)
        return (a.size < b.size);
    return (a.totalWeight < b.totalWeight);
}

bool sortChamberIndex(const Chamber &a, const Chamber &b){
    return (a.index < b.index);
}

int main(){
    int nChambers, nSpecies, nSets = 1;
    while(cin >> nChambers >> nSpecies){
        //aqui dentro serao realizadas as operações para cada caso
        vector<int> species;
        int weight;
        for(int i = 0; i < nSpecies; i++){
           cin >> weight;
           species.push_back(weight);
        }
        //ordena o vetor de pesos de espécies
        sort(species.begin(), species.end(), greater<>());
        
        //-- gaiolas --
        //cria e inicializa
        vector<Chamber> chambers;
        for(int i = 0; i < nChambers; i++)
            chambers.push_back(initChamber(i));

        //coloca os animais nas gaiolas
        for(auto weight : species){
            Chamber elem = chambers.front();
            chambers.at(0) = increaseWeight(elem, weight);
            sort(chambers.begin(), chambers.end(), sortChamberWeight);
        }

        //calcula a média de peso das gaiolas
        float average = 0;
        for(auto elem : chambers)
            average += elem.totalWeight;
        average /= (float) nChambers;

        //calcula imbalance
        float imbalance = 0;
        for(auto elem : chambers)
            imbalance += (float) abs(average - (float) elem.totalWeight);

        //ordena para printar
        sort(chambers.begin(), chambers.end(), sortChamberIndex);

        //print
        printf("Set #%d\n", nSets++);
        for(auto elem : chambers){
            printf(" %d:", elem.index);
            for(int i = 0; i < elem.size; i++)
                printf(" %d", elem.animals[i]);
            cout << endl;
        }
        printf("IMBALANCE = %.5f", imbalance);
    }

    return 0;
}