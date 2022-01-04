#include <stdio.h>
#define HLT 0
#define ADD 1
#define MUL 2
#define CLT 3
#define CEQ 4
#define JMP 5
#define JEQ 6
#define CPY 7
#define PUT 8
#define PTN 9



//function def
int addFunction(int n, int* valuesTape){ //1
      valuesTape[valuesTape[n+3]] = (valuesTape[valuesTape[n+1]] + valuesTape[valuesTape[n+2]]);
      return n + 4;
}

int multiply(int n){ //2
      valuesTape[valuesTape[n+3]] = valuesTape[valuesTape[n+1]] * valuesTape[valuesTape[n+2]];
      return n + 4;
}

int compareLessThan(int n){ //3
      a = valuesTape[valuesTape[n+1]];
      b = valuesTape[valuesTape[n+2]];
      if(a < b)
            {c = 1;}
      else
            {c = 0;}
      valuesTape[valuesTape[n+3]] = c;
      return n + 4;
}

int compareEquals(int n){ //4
      a = valuesTape[valuesTape[n+1]];
      b = valuesTape[valuesTape[n+2]];
      if(a == b)
            {c = 1;}
      else
            {c = 0;}
      valuesTape[valuesTape[n+3]] = c;
      return n + 4;
}

int jump(int n){ //5
      return valuesTape[valuesTape[n+1]];
}

int jumpIfEqual(int n){ //6
      a = valuesTape[valuesTape[n+1]];
      b = valuesTape[valuesTape[n+2]];
      if(a != 0){
            return b;
      }else{
            return n + 3;
      }
}

int copy(int n){ //7
      valuesTape[valuesTape[n+2]] = valuesTape[valuesTape[n+1]];
      return n + 3;
}

int putFunction(int n){ //8
      a = valuesTape[valuesTape[n+1]];
      printf("%c", a);
      return n + 2;
}

int putNum(int n){ //9
      a = valuesTape[valuesTape[n+1]];
      printf("%i", a);
      return n + 2;
}

int main(){
      //define global variables
      int valuesTape[511];
      int a, b, c;

      //read the values tape
      for (int i = 0; i < 512; i++){
            scanf("%i", &valuesTape[i]);
      }

      int n = 0;

      printf("Saida do programa:\n");
      while(n < 512){
            switch (valuesTape[n]){
                  case HLT:
                        n = 512;
                        break;
                  case ADD:
                        n = addFunction(n, valuesTape);
                        break;
                  case MUL:
                        n = multiply(n);
                        break;
                  case CLT:
                        n = compareLessThan(n);
                        break;
                  case CEQ:
                        n = compareEquals(n);
                        break;
                  case JMP:
                        n = jump(n);
                        break;
                  case JEQ:
                        n = jumpIfEqual(n);
                        break;
                  case CPY:
                        n = copy(n);
                        break;
                  case PUT:
                        n = putFunction(n);
                        break;
                  case PTN:
                        n = putNum(n);
                        break;
            }
      }

      printf("\nEstado final da fita:\n");
      for (int i = 0; i < 512; i++){
            printf("%i\n", valuesTape[i]);
      }

}
