// Lab Question 1: Implementation of Fibonacci Heap Operations 

// Aim: 
// Implement a Fibonacci Heap and demonstrate key mergeable heap operations. 

// Tasks: 
// a) Implement the following operations on a Fibonacci Heap: 

// Insert(x) – Insert a new node 

// Find-Min() – Return the minimum key 

// Union(H1, H2) – Merge two Fibonacci Heaps 
// b) Display the heap structure before and after each operation. 

// Expected Output: 

// Display of heap structure after each insert and merge operation. 

// Verification of the minimum key after each step. 
#include <stdio.h>
#include <stdlib.h>

/* Node of Fibonacci Heap */
typedef struct Node {
    int key;
    int degree;

    struct Node *parent;
    struct Node *child;

    struct Node *left;
    struct Node *right;
} Node;

/* Fibonacci Heap */
typedef struct FibonacciHeap {
    Node *min;
    int n;
} FibonacciHeap;


/* Create a new node */
Node* createNode(int key) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->key = key;
    newNode->degree = 0;

    newNode->parent = NULL;
    newNode->child = NULL;

    /* Initially, node points to itself */
    newNode->left = newNode;
    newNode->right = newNode;

    return newNode;
}


/* Create an empty Fibonacci Heap */
FibonacciHeap* createHeap() {
    FibonacciHeap *heap =
        (FibonacciHeap*)malloc(sizeof(FibonacciHeap));

    heap->min = NULL;
    heap->n = 0;

    return heap;
}


/* Insert a node into Fibonacci Heap */
void insert(FibonacciHeap *heap, int key) {

    Node *newNode = createNode(key);

    /* If heap is empty */
    if (heap->min == NULL) {
        heap->min = newNode;
    }

    /* Otherwise add node to root list */
    else {
        newNode->right = heap->min->right;
        newNode->left = heap->min;

        heap->min->right->left = newNode;
        heap->min->right = newNode;

        /* Update minimum */
        if (newNode->key < heap->min->key) {
            heap->min = newNode;
        }
    }

    heap->n++;
}


/* Find minimum */
Node* findMin(FibonacciHeap *heap) {

    if (heap->min == NULL) {
        return NULL;
    }

    return heap->min;
}


/* Union of two Fibonacci Heaps */
FibonacciHeap* unionHeap(FibonacciHeap *H1,
                         FibonacciHeap *H2) {

    FibonacciHeap *H = createHeap();

    /* If H1 is empty */
    if (H1->min == NULL) {
        H->min = H2->min;
        H->n = H2->n;
        return H;
    }

    /* If H2 is empty */
    if (H2->min == NULL) {
        H->min = H1->min;
        H->n = H1->n;
        return H;
    }

    /*
       Join the two circular root lists
    */

    Node *H1Right = H1->min->right;
    Node *H2Left = H2->min->left;

    H1->min->right = H2->min;
    H2->min->left = H1->min;

    H1Right->left = H2Left;
    H2Left->right = H1Right;

    /* Find new minimum */
    if (H1->min->key < H2->min->key) {
        H->min = H1->min;
    }
    else {
        H->min = H2->min;
    }

    /* Total number of nodes */
    H->n = H1->n + H2->n;

    return H;
}


/* Display root list */
void display(FibonacciHeap *heap) {

    if (heap->min == NULL) {
        printf("Heap is empty.\n");
        return;
    }

    Node *temp = heap->min;

    printf("Root List: ");

    do {
        printf("%d ", temp->key);
        temp = temp->right;
    } while (temp != heap->min);

    printf("\n");
}


/* Main function */
int main() {

    FibonacciHeap *H1 = createHeap();
    FibonacciHeap *H2 = createHeap();

    int n, key, i;

    /* Insert into first heap */
    printf("Enter number of elements for Heap 1: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(H1, key);
    }

    printf("\nHeap 1:\n");
    display(H1);

    /* Find minimum of H1 */
    Node *minNode = findMin(H1);

    if (minNode != NULL) {
        printf("Minimum of Heap 1 = %d\n", minNode->key);
    }


    /* Insert into second heap */
    printf("\nEnter number of elements for Heap 2: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(H2, key);
    }

    printf("\nHeap 2:\n");
    display(H2);

    /* Find minimum of H2 */
    minNode = findMin(H2);

    if (minNode != NULL) {
        printf("Minimum of Heap 2 = %d\n", minNode->key);
    }


    /* Union */
    FibonacciHeap *H = unionHeap(H1, H2);

    printf("\nAfter Union:\n");
    display(H);

    /* Find minimum after union */
    minNode = findMin(H);

    if (minNode != NULL) {
        printf("Minimum after Union = %d\n", minNode->key);
    }

    return 0;
}