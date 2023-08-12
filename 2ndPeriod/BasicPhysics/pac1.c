#include <stdio.h>

int f(d){
    float dcoelho = d;
    float dt = (d*0.12)/9;
    d -= dt;
    float t = d/9.12;
    dt = t*0.12;
    d -= dt;
    dcoelho += d;
    if(d < 0){
        return dcoelho;  
    }
}

int main(){
    float d = 0.0;
    d += f(80);
    printf("distancia total percorrida = %.2fm", dcoelho);
    return 0;
}
