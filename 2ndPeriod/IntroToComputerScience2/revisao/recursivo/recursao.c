#include <stdio.h>
#include <stdlib.h>

int f(int *v){
    if (*v == -1){
        return 0;
    }
    return *v + f(v+1);

}

int main(){
        
    int V[5] = {1, 2, 3, 4, -1};
    int soma = f(V);
    printf("soma = %d\n", soma);
    return 0;
}
