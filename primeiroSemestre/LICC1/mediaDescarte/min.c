#include <stdio.h>

double minFunction(double a, double b, double c, double d);

int main(){
      double a, b, c, d, min;
      scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
      min = minFunction(a, b, c, d);

      double m;
      m = (a + b + c + d - min)/3;
      printf("%.4lf\n", m);
}

double minFunction(double a, double b, double c, double d){
      double min, min_1, min_2;
      if(a < b)
            {min_1 = a;}
      else
            {min_1 = b;}

      if(c < d)
            {min_2 = c;}
      else
            {min_2 = d;}

      if(min_1 < min_2)
            {min = min_1;}
      else
            {min = min_2;}

      return min;
}
