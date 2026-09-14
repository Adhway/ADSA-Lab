//write a program to implement stack using array
#include<stdio.h>
#define MAX 5
int arr[MAX];
int top=-1;

//function of push element into stack
void push(int value){
    if(top==MAX-1)
    printf("Stack overflow\n");
    else{
        top++;
        arr[top]=value;
        printf("%d has been pushed into array\n",value);
    }
}

//function to pop an element into stack 
void pop(){
    if(top==-1)
    printf("Stack Underflow\n");
    else{
        printf("%d has been popped from stack\n",arr[top]);
        top--;
    }
}

//function to peek for an element in stack 
void peek(){
    if(top==-1)
    printf("Empty Stack\n");
    else
    printf("Top element of stack is =%d\n",arr[top]);
}

//function to display the elements of stack
void display(){
    if(top==-1)
    printf("Stack is empty\n");
    else{
        printf("The elements of stack are\n");
        for(int i=top;i>=0;i--)
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(){
    int n,choice;
    printf("Stack Implementation using array\n");
    while(1){
        printf("enter your choices\n");
        printf("1 for push\n");
        printf("2 for pop\n");
        printf("3 for peek\n");
        printf("4 for display\n");
        printf("5 for exit\n");
        scanf("%d",&choice);
    switch(choice){
        case 1:
        printf("enter the element to be pushed\n");
        scanf("%d",&n);
        push(n);
        break;
        case 2:
        pop();
        break;
        case 3:
        peek();
        break;
        case 4:
        display();
        break;
        case 5:
        return 0;
        break;
        default:
        printf("Invalid Choice\n");
        break;
    }}
    return 0;
}