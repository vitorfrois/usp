#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define wasteland -1
#define residential 0
#define parks 1

double hermannFunc(double xAxis[], double yAxis[], int i, bool last){
      int a = last == true? 0: i - 1;
      return (
            fabs(xAxis[i] - xAxis[a]) +
            fabs(yAxis[i] - yAxis[a])
      );
}

double euclidesFunc(double xAxis[], double yAxis[], int i, bool last){
      int a = last == true? 0: i - 1;
      return (
            sqrt(
                  pow(xAxis[i] - xAxis[a], 2.0) +
                  pow(yAxis[i] - yAxis[a], 2.0)
            )
      );
}

int main() {
      int numPlaces;
      int wastelandCount = 0;
      int residentialCount = 0;
      int parksCount = 0;
      double distanceDiff = 0;
      bool last = false;
      scanf("%d", &numPlaces);
      if(numPlaces < 1){
            printf("Falha no processamento dos dados. \n");
            return 0;
      }

      double xAxis[numPlaces - 1];
      double yAxis[numPlaces - 1];
      double type[numPlaces - 1];
      for(int i = 0; i < numPlaces; i++){
            scanf("%lf", &xAxis[i]);
            scanf("%lf", &yAxis[i]);
            scanf("%lf", &type[i]);
      }
      if(type[numPlaces - 1] > 1 || type[numPlaces - 1] < -1){
            printf("Falha no processamento dos dados. \n");
            return 0;
      }


      for(int i = 1; i < numPlaces; i++){
            double hermannDist, euclidesDist;
            if(type[i-1] == wasteland){
                  wastelandCount++;
            }else if(type[i-1] == residential){
                  residentialCount++;
            }else{
                  parksCount++;
                  hermannDist = hermannFunc(xAxis, yAxis, i, last);
                  euclidesDist = euclidesFunc(xAxis, yAxis, i, last);
                  distanceDiff += hermannDist - euclidesDist;
            }
      }

      if(type[numPlaces - 1] == wasteland){
            wastelandCount++;
      }else if(type[numPlaces - 1] == residential){
            residentialCount++;
      }else{
            parksCount++;
            last = true;
            int i = numPlaces - 1;
            double hermannDist = hermannFunc(xAxis, yAxis, i, last);
            double euclidesDist = euclidesFunc(xAxis, yAxis, i, last);
            distanceDiff += hermannDist - euclidesDist;
      }

      printf(
            "Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques. \nA diferenca total de distancia percorrida foi de %.2lf metros.",
            wastelandCount, residentialCount, parksCount, distanceDiff
      );

      return 0;
}
