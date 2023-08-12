#include <stdio.h>
#include <stdlib.h>

#define crivoSize 10000

int main(){
    int nPrimos = 0;
    int n = 2;
    int primos[crivoSize];
    primos[0] = 2;
    int primeChance;
    while(nPrimos < crivoSize){
        primeChance = 0;
        for(int i = 0; i < nPrimos; i++){
            //printf("primos[%d] = %d\n", i, primos[i]);
            if(n % primos[i] == 0){
                primeChance++;
                i = nPrimos;
            }
        }
        if(primeChance < 1){
            nPrimos++;
            primos[nPrimos-1] = n;
        }
        primeChance = 0;
        n++;
    }

    for(int i = 0; i < crivoSize; i++){
        printf("%d\n", primos[i]);
    }

    // int nInput;
    // scanf("%d\n\n", &nInput);
    // int toBePrintedIndex[nInput];
    // for(int i = 0; i < nInput; i++){
    //     scanf("%d", &toBePrintedIndex[i]);
    // }

    // for(int i = 0; i < nInput; i++){
    //     printf("%d ", primos[toBePrintedIndex[i]]);
    // }

    return 0;
}