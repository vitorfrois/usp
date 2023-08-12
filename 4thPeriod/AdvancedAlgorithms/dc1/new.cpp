#include <iostream>
#include <vector>

using namespace std;

long int merge(int arr[], int temp[], int begin, int mid, int end){
    long int crossings = 0;

    int a1 = begin, a2 = mid, t = begin;
    while(a1 < mid && a2 <= end){
        if(arr[a1] < arr[a2])
            temp[t++] = arr[a1++];
        else{
            temp[t++] = arr[a2++];
            crossings += (mid - a1);
        }
    }

    while(a1 < mid)
        temp[t++] = arr[a1++];

    while(a2 <= end)
        temp[t++] = arr[a2++];

    for(int i = begin; i <= end; i++)
        arr[i] = temp[i];

    return crossings;
}

//We can solve crossings problem by using Merge Sort
long int mergeSort(int arr[], int temp[], int begin, int end){
    long int crossingsCount = 0;
    if(end <= begin)
        return crossingsCount;
    
    int mid = (end+begin)/2;
    crossingsCount += mergeSort(arr, temp, begin, mid);
    crossingsCount += mergeSort(arr, temp, mid+1, end);

    crossingsCount += merge(arr, temp, begin, mid+1, end);
    return crossingsCount;
}

long int crossings(int arr[], int arrLenght){
    int temp[arrLenght];
    return mergeSort(arr, temp, 0, arrLenght-1);
}

int main(){
    int numberTestCases;
    cin >> numberTestCases;
    for(int i = 0; i < numberTestCases; i++){
        int arrLenght;
        cin >> arrLenght;
        int arr[arrLenght];
        for(int j = 0; j < arrLenght; j++)
            cin >> arr[j];

        cout << crossings(arr, arrLenght) << endl;
    }

}
