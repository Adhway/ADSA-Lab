// Write a program to implement following sorting algorithms
// a) Quick sort
#include<stdio.h>
void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
int partition(int arr[], int low, int high){
    int mid=arr[high];
    int i=low-1;
    int j;
    for(j=low; j<high;j++){
        if(arr[j]<mid){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return i+1;
}
void quicksort(int arr[],int low, int high){
    if(low<high){
        int mid1=partition(arr, low, high);
        quicksort(arr, low, mid1-1);
        quicksort(arr, mid1+1, high);
    }
}
int main(){
    int n,arr[100];
    printf("enter the size of array\n");
    scanf("%d",&n);
    printf("enter the elements\n");
    for(int i=0;i<n;i++)
    scanf("%d ",&arr[i]);
    quicksort(arr,0,n-1);
    printf("Array Sorted using Quick Sort\n");
    for(int k=0;k<n;k++)
    printf("%d ",arr[k]);
    return 0;
}