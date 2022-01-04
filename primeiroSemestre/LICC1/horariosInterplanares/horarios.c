#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct planetTimeFormat{
      unsigned long long int days;
      unsigned long long int hours;
      unsigned long long int minutes;
      unsigned long long int seconds;
};
typedef struct planetTimeFormat time;

char* readString(){
      char *string = malloc(sizeof(char));
      char character = ' ';
      int nCharsString = 0;
      do {
            character = getchar();
            string = realloc(string, (nCharsString + 1) * sizeof(char));
            string[nCharsString] = character;
            nCharsString++;
      } while(character != '\n' && character != EOF);
      string[nCharsString - 1] = '\0';
      return string;
}

struct planetTimeFormat timeCalculator(char* planetName, unsigned long long int timeCalculingSeconds){
      unsigned long long int daysDivider, hourDivider, minutesDivider;
      if(strcmp(planetName, "Terra") == 0){
            daysDivider = 86400;
            hourDivider = 3600;
            minutesDivider = 60;
      }else if(strcmp(planetName, "Venus") == 0){
            daysDivider = 20995200;
            hourDivider = 3600;
            minutesDivider = 60;
      }else if(strcmp(planetName, "Mercurio") == 0){
            daysDivider = 5068800;
            hourDivider = 3600;
            minutesDivider = 60;
      }else if(strcmp(planetName, "Jupiter") == 0){
            daysDivider = 35760;
            hourDivider = 3600;
            minutesDivider = 60;
      }else{
            printf("Planeta não identificado! Sera impresso o horario da Terra.\n");
            daysDivider = 86400;
            hourDivider = 3600;
            minutesDivider = 60;
      }
      time planet;
      planet.days = timeCalculingSeconds/daysDivider;
      timeCalculingSeconds -= planet.days * daysDivider;
      planet.hours = timeCalculingSeconds/hourDivider;
      timeCalculingSeconds -= planet.hours * hourDivider;
      planet.minutes = timeCalculingSeconds/minutesDivider;
      timeCalculingSeconds -= planet.minutes * minutesDivider;
      planet.seconds = timeCalculingSeconds;
      return planet;
}

int main (){
      unsigned long long int secondsInput;
      scanf("%llu ", &secondsInput);
      char* planetName = readString();
      time planet = timeCalculator(planetName, secondsInput);
      printf("%llu segundos no planeta %s equivalem a:\n", secondsInput, planetName);
      printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n",
            planet.days,
            planet.hours,
            planet.minutes,
            planet.seconds
      );
      return 0;
}
