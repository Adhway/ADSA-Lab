// Lab Question 2: Key Decrease and Node Deletion in Fibonacci Heap 

// Aim: 
// Demonstrate decrease-key and delete-node operations in a Fibonacci Heap. 

// Tasks: 
// a) Construct a Fibonacci Heap with at least 10 nodes. 
// b) Perform the following operations sequentially: 

// Decrease a key (use cascading cuts if required). 

// Delete a node by decreasing its key to -∞ and performing Extract-Min(). 
// c) Print the heap structure after each step. 

// Expected Output: 

// Intermediate states of the heap showing cascading cuts. 

// Final heap after deletion. 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ---------------- NODE STRUCTURE ---------------- */

typedef struct Node {
    int key;
    int degree;
    int mark;

    struct Node *parent;
    struct Node *child;

    struct Node *left;
    struct Node *right;
} Node;


/* ---------------- FIBONACCI HEAP ---------------- */

typedef struct FibonacciHeap {
    Node *min;
    int n;
} FibonacciHeap;


/* ---------------- CREATE NODE ---------------- */

Node* createNode(int key) {

    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->key = key;
    newNode->degree = 0;
    newNode->mark = 0;

    newNode->parent = NULL;
    newNode->child = NULL;

    newNode->left = newNode;
    newNode->right = newNode;

    return newNode;
}


/* ---------------- CREATE HEAP ---------------- */

FibonacciHeap* createHeap() {

    FibonacciHeap *heap =
        (FibonacciHeap*)malloc(sizeof(FibonacciHeap));

    heap->min = NULL;
    heap->n = 0;

    return heap;
}


/* ---------------- INSERT ---------------- */

void insert(FibonacciHeap *heap, int key) {

    Node *newNode = createNode(key);

    if (heap->min == NULL) {

        heap->min = newNode;

    } else {

        newNode->right = heap->min->right;
        newNode->left = heap->min;

        heap->min->right->left = newNode;
        heap->min->right = newNode;

        if (newNode->key < heap->min->key) {
            heap->min = newNode;
        }
    }

    heap->n++;
}


/* ---------------- REMOVE NODE FROM LIST ---------------- */

void removeFromList(Node *x) {

    x->left->right = x->right;
    x->right->left = x->left;

    x->left = x;
    x->right = x;
}


/* ---------------- ADD NODE TO ROOT LIST ---------------- */

void addToRootList(FibonacciHeap *heap, Node *x) {

    x->parent = NULL;
    x->mark = 0;

    x->right = heap->min->right;
    x->left = heap->min;

    heap->min->right->left = x;
    heap->min->right = x;
}


/* ---------------- CUT ---------------- */

void cut(FibonacciHeap *heap, Node *x, Node *y) {

    /* Remove x from y's child list */

    if (x->right == x) {

        y->child = NULL;

    } else {

        if (y->child == x) {
            y->child = x->right;
        }

        x->left->right = x->right;
        x->right->left = x->left;
    }

    y->degree--;

    /* Add x to root list */

    x->left = x;
    x->right = x;

    addToRootList(heap, x);
}


/* ---------------- CASCADING CUT ---------------- */

void cascadingCut(FibonacciHeap *heap, Node *y) {

    Node *z = y->parent;

    if (z != NULL) {

        if (y->mark == 0) {

            /* First child loss */
            y->mark = 1;

        } else {

            /* Second child loss */
            cut(heap, y, z);

            cascadingCut(heap, z);
        }
    }
}


/* ---------------- DECREASE KEY ---------------- */

void decreaseKey(FibonacciHeap *heap,
                 Node *x,
                 int newKey) {

    if (newKey > x->key) {

        printf("Error: New key is greater than old key.\n");
        return;
    }

    x->key = newKey;

    Node *y = x->parent;

    /*
       If x violates heap order,
       cut x from its parent.
    */

    if (y != NULL && x->key < y->key) {

        cut(heap, x, y);

        cascadingCut(heap, y);
    }

    /* Update minimum */

    if (x->key < heap->min->key) {
        heap->min = x;
    }
}


/* ---------------- LINK TREES ---------------- */

void link(FibonacciHeap *heap,
          Node *y,
          Node *x) {

    /*
       Remove y from root list
    */

    removeFromList(y);

    /*
       Make y a child of x
    */

    y->parent = x;
    y->mark = 0;

    if (x->child == NULL) {

        x->child = y;

        y->left = y;
        y->right = y;

    } else {

        y->right = x->child->right;
        y->left = x->child;

        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
}


/* ---------------- CONSOLIDATE ---------------- */

void consolidate(FibonacciHeap *heap) {

    int maxDegree = 100;

    Node *A[100];

    int i;

    for (i = 0; i < maxDegree; i++) {
        A[i] = NULL;
    }

    /*
       Store all roots temporarily
    */

    int rootCount = 0;

    Node *w = heap->min;

    if (w == NULL)
        return;

    Node *temp = w;

    do {
        rootCount++;
        temp = temp->right;
    } while (temp != w);


    /*
       Store root nodes in array
    */

    Node **roots =
        (Node**)malloc(rootCount * sizeof(Node*));

    temp = w;

    for (i = 0; i < rootCount; i++) {

        roots[i] = temp;
        temp = temp->right;
    }


    /*
       Consolidate trees having same degree
    */

    for (i = 0; i < rootCount; i++) {

        Node *x = roots[i];

        int d = x->degree;

        while (A[d] != NULL) {

            Node *y = A[d];

            /*
               Smaller key becomes parent
            */

            if (x->key > y->key) {

                Node *swap = x;
                x = y;
                y = swap;
            }

            link(heap, y, x);

            A[d] = NULL;
            d++;
        }

        A[d] = x;
    }

    free(roots);


    /*
       Rebuild root list
    */

    heap->min = NULL;

    for (i = 0; i < maxDegree; i++) {

        if (A[i] != NULL) {

            Node *x = A[i];

            x->left = x;
            x->right = x;

            if (heap->min == NULL) {

                heap->min = x;

            } else {

                x->right = heap->min->right;
                x->left = heap->min;

                heap->min->right->left = x;
                heap->min->right = x;

                if (x->key < heap->min->key) {
                    heap->min = x;
                }
            }
        }
    }
}


/* ---------------- EXTRACT MIN ---------------- */

Node* extractMin(FibonacciHeap *heap) {

    Node *z = heap->min;

    if (z == NULL)
        return NULL;


    /*
       Move all children of z
       to the root list
    */

    if (z->child != NULL) {

        Node *child = z->child;

        int childCount = z->degree;

        Node **children =
            (Node**)malloc(childCount * sizeof(Node*));

        Node *temp = child;

        int i;

        for (i = 0; i < childCount; i++) {

            children[i] = temp;
            temp = temp->right;
        }

        for (i = 0; i < childCount; i++) {

            Node *x = children[i];

            x->parent = NULL;
            x->mark = 0;

            x->left = x;
            x->right = x;

            /*
               Add child to root list
            */

            x->right = heap->min->right;
            x->left = heap->min;

            heap->min->right->left = x;
            heap->min->right = x;
        }

        free(children);
    }


    /*
       Remove minimum node
    */

    removeFromList(z);

    heap->n--;


    /*
       If heap is not empty,
       consolidate the trees.
    */

    if (heap->n == 0) {

        heap->min = NULL;

    } else {

        heap->min = z->right;

        consolidate(heap);
    }

    return z;
}


/* ---------------- DELETE NODE ---------------- */

void deleteNode(FibonacciHeap *heap, Node *x) {

    /*
       Step 1:
       Decrease key to minimum possible value.
    */

    decreaseKey(heap, x, INT_MIN);

    /*
       Step 2:
       Extract minimum.
    */

    Node *deleted = extractMin(heap);

    if (deleted != NULL) {

        printf("\nDeleted node: %d\n", deleted->key);

        free(deleted);
    }
}


/* ---------------- PRINT ROOT LIST ---------------- */

void printRootList(FibonacciHeap *heap) {

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

    printf("Minimum: %d\n", heap->min->key);
}


/* ---------------- PRINT TREE ---------------- */

void printTree(Node *node, int level) {

    if (node == NULL)
        return;

    Node *start = node;
    Node *temp = start;

    do {

        for (int i = 0; i < level; i++) {
            printf("    ");
        }

        printf("|-- %d", temp->key);

        if (temp->mark)
            printf(" [marked]");

        printf("\n");

        if (temp->child != NULL) {
            printTree(temp->child, level + 1);
        }

        temp = temp->right;

    } while (temp != start);
}


/* ---------------- PRINT COMPLETE HEAP ---------------- */

void printHeap(FibonacciHeap *heap) {

    if (heap->min == NULL) {

        printf("Heap is empty.\n");
        return;
    }

    printf("\n========== FIBONACCI HEAP ==========\n");

    printf("Number of nodes: %d\n", heap->n);
    printf("Minimum: %d\n", heap->min->key);

    printf("\nHeap Structure:\n");

    Node *temp = heap->min;

    do {

        printf("\nRoot: %d\n", temp->key);

        if (temp->child != NULL) {
            printTree(temp->child, 1);
        }

        temp = temp->right;

    } while (temp != heap->min);

    printf("\n====================================\n");
}


/* ---------------- MAIN ---------------- */

int main() {

    FibonacciHeap *heap = createHeap();

    /*
       Store pointers so that we can
       perform decrease-key and delete.
    */

    Node *nodes[15];

    int values[] = {
        30, 20, 40, 10, 50,
        60, 70, 80, 90, 100
    };

    int n = 10;

    printf("Creating Fibonacci Heap with 10 nodes...\n");

    /*
       Insert 10 nodes
    */

    for (int i = 0; i < n; i++) {

        nodes[i] = createNode(values[i]);

        /*
           Manually insert the node
           and retain its pointer.
        */

        if (heap->min == NULL) {

            heap->min = nodes[i];

        } else {

            nodes[i]->right = heap->min->right;
            nodes[i]->left = heap->min;

            heap->min->right->left = nodes[i];
            heap->min->right = nodes[i];

            if (nodes[i]->key < heap->min->key) {
                heap->min = nodes[i];
            }
        }

        heap->n++;
    }


    /*
       Print initial heap
    */

    printf("\nInitial Fibonacci Heap:\n");

    printHeap(heap);


    /*
       -----------------------------
       DECREASE KEY
       -----------------------------
    */

    printf("\n\nPerforming Decrease-Key...\n");

    printf("Changing key 70 to 5\n");

    decreaseKey(heap, nodes[6], 5);

    printHeap(heap);


    /*
       -----------------------------
       ANOTHER DECREASE KEY
       -----------------------------
    */

    printf("\n\nPerforming another Decrease-Key...\n");

    printf("Changing key 80 to 15\n");

    decreaseKey(heap, nodes[7], 15);

    printHeap(heap);


    /*
       -----------------------------
       DELETE NODE
       -----------------------------
    */

    printf("\n\nDeleting node 90...\n");

    /*
       Delete node 90 by:
       1. Decrease to -infinity
       2. Extract-Min
    */

    deleteNode(heap, nodes[8]);

    printHeap(heap);


    printf("\nProgram completed successfully.\n");

    return 0;
}