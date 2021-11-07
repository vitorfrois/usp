#include <stdio.h>

public int getPopularElement(int[] a);

int main(){
	int array[] = {0,0,0,1,2,3,4,5,6};
	getPopularElement(array);
}

int getPopularElement(int[] a){
  int count = 1, tempCount;
  int popular = a[0];
  int temp = 0;
  for (int i = 0; i < (a.length - 1); i++)
  {
    temp = a[i];
    tempCount = 0;
    for (int j = 1; j < a.length; j++)
    {
      if (temp == a[j])
        tempCount++;
    }
    if (tempCount > count)
    {
      popular = temp;
      count = tempCount;
    }
  }
  return popular;
}
