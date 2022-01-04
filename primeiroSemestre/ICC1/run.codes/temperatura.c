//Vítor Fróis
//BCC - 021
//Conversor de Temperatura

#include <stdio.h>

int main(){
  float fahrenheit;
  float celsius;
  scanf("%f", &fahrenheit);
  //(°C × 9/5) + 32 = °F
  celsius = (fahrenheit - 32) * 5/9;
  printf("%.2f\n", celsius);
}
