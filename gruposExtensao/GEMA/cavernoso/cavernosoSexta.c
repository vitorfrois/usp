#include <stdio.h>

int main(){
      int n, count = 0, maximumVillagers = 0, dayMaximum = 0;
      char stick = '|';
      scanf("%i", &n);
      int villageHabitants[1000] = {0};
      for (int i = 0; i < n+1; i++){
            while(1){
                  scanf("%c", &stick);
                  if(stick == '|'){
                        count++;
                  }else{
                        break;
                  }
            }
            //printf("%d\n", count);
            villageHabitants[count]++;
	      count = 0;
      }

      //PRINT villageHabitants[frequency] array
      /*
      printf("villageHabitants = { ");
      for(int z = 1; z < 10; z++){
            printf("%d, ", villageHabitants[z]);
      }
      printf("} \n ");
      */

      for(int x = 1; x < 1000; x++){
            if(villageHabitants[x] > maximumVillagers){
                  dayMaximum = x;
                  //printf("O novo máximo é %d, que ocorreu no dia %d\n",
                  //villageHabitants[x], dayMaximum);
                  maximumVillagers = villageHabitants[x];
            }
      }
      printf("%d", dayMaximum);
      return 0;
}
