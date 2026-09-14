// b) Merge Sort
#include<stdio.h>
void merge(int arr[], int low, int mid, int high){
    int temp[100];
    int i=low;
    int j=mid+1;
    int k=low;
    while (i<=mid && j<high)
    {
        if(arr[i]<arr[j]){
            temp[k]=arr[i];
            i++;
        }
        else{
            temp[k]=arr[j];
            j++;
        }
        k++;
    }
    while (i<=mid)
    {
        temp[k]=arr[i];
        i++;
        k++;
    }
    while(j<=high){
        temp[k]=arr[j];
        j++;
        k++;
    }
    for(int i=low;i<=high;i++)
    arr[i]=temp[i];
}
void mergesort(int arr[], int low, int high){
    if(low<high){
        int mid=(low+high)/2;
        mergesort(arr, low, high);
        mergesort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}
int main(){
    int n, arr[100],i;
    printf("enter the size of array\n");
    scanf("%d", &n);
    printf("enter the elements\n");
    for(i=0;i<n;i++)
    scanf("%d",&arr[i]);
    mergesort(arr, 0, n-1);
    printf("Array Sorted using Merge Sort\n");
    for(int k=0;k<n;k++)
    printf("%d ",arr[k]);
    return 0;
}