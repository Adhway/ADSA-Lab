//write a program to implement stack using Linked List
#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
};
struct Node *top=NULL;

//function to push element into stack
void push(int value){
    struct Node *newNode;
    newNode=(struct Node *)malloc(sizeof(struct Node));
    if(newNode==NULL)
    printf("Stack Underflow\n");
    newNode->data=value;
    newNode->next=top;
    top=newNode;
    printf("%d has been pushed into stack\n",value);
}

//function to pop an element from stack
void pop(){
    struct Node *temp;
    if(top==NULL){
        printf("Stack Underflow\n");
        return;
    }
    temp=top;
    printf("%d has been popped from the stack\n",top->data);
    top=top->next;
    free(temp);
}

//function to peek an elment from stack
void peek(){
    if(top==NULL){
        printf("Stack Underflow\n");
        return;
    }
    printf("The top element of stack is %d\n",top->data);
}

//fucntion to display stack elements
void display(){
    struct Node *temp=top;
    if(top==NULL){
        printf("Stack empty\n");
        return;
    }
    printf("Stack elements are\n");
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

int main(){
    int n,choice;
    printf("Stack Implementation using Linked List\n");
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
        exit(0);
        break;
        default:
        printf("Invalid Choice\n");
        break;
    }}
    return 0;
}