// c) Heap Sort
#include<stdio.h>
void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void heap(int arr[], int n, int i){
    int large=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && arr[left]>large)
    large=left;
    else if(right<n && arr[right]>large)
    large=right;
    if(large!=i){
        swap(&arr[i], &arr[large]);
        heap(arr, n, large);
    }
}
void heapsort(int arr[], int n){
    int i;
    //Building max heap
    for(i=n/2-1;i>=0;i--)
    heap(arr, n, i);
    for(int i=n-1;i>=0;i--){
        swap(&arr[0], &arr[i]);
        heap(arr, i, 0);
    }
}
int main(){
    int arr[100], n;
    printf("enter size of array\n");
    scanf("%d", &n);
    printf("enter the elements\n");
    for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);
    heapsort(arr, n);
    printf("Sorted array\n");
    for(int j=0;j<n;j++)
    printf("%d ",arr[j]);
    return 0;
}