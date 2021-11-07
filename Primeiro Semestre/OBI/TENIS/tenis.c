#include <stdio.h>

int main(){
      int wins = 0;
      char result;
      for(int i = 0; i < 12; i++){
            scanf("%c", &result);
            result == 'V'? wins++ : wins;
      }
      if(wins == 5 || wins == 6){
            printf("1");
      }else if(wins == 3 || wins == 4){
            printf("2");
      }else if(wins == 1 || wins == 2){
            printf("3");
      }else{
            printf("-1");
      }
      return 0;
}
