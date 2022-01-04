#include <stdio.h>

int main(){

    int vitorias;
    char array[12];

    for (int i = 0; i < 12; i++){

        scanf("%c", &array[i]);
    }

    for (int i = 0; i < 12; i++){

        if(array[i] == 'V'){
            vitorias++;
        }
    }

    if(vitorias > 4){
        printf("1");
    }

    else if(vitorias > 2){
        printf("2");
    }

    else if(vitorias > 0){
        printf("3");
    }

    else{
        printf("-1");
    }

    return 0;
}
