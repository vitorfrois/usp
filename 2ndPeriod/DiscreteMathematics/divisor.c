#include <stdio.h>
#include <math.h>

void divisor(int n){
    printf("Divisores de %d: {", n);
    for(int i = 1; i <= n; i++)
        if(n%i == 0)
            if(i != n)
                printf("%d;", i);
            else
                printf("%d", i);
    printf("}\n");
}


int main(){
    divisor(15);

    return 0;
}
