// Lab Question 3: Implementation of a van Emde Boas Tree 

// Aim: 
// Implement a van Emde Boas (vEB) Tree using recursive structure and demonstrate key operations. 

// Tasks: 
// a) Implement a vEB Tree with universe size U = 16. 
// b) Implement and test the following operations: 

// Insert(x) 

// Member(x) 

// Successor(x) and Predecessor(x) 

// Delete(x) 
// c) Demonstrate the recursive layout of the structure and print results of each operation. 

// Expected Output: 

// Structure visualization (showing clusters and summary). 

// Correct output for predecessor/successor queries. 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 9999


/* =========================================
   vEB TREE STRUCTURE
   ========================================= */

typedef struct vEBTree {

    int u;              // Universe size

    int min;            // Minimum element
    int max;            // Maximum element

    struct vEBTree *summary;

    struct vEBTree **cluster;

} vEBTree;


/* =========================================
   HELPER FUNCTIONS
   ========================================= */

/* Return upper square root */
int upper_sqrt(int u) {

    return (int)ceil(sqrt((double)u));
}


/* Return lower square root */
int lower_sqrt(int u) {

    return (int)floor(sqrt((double)u));
}


/* High part of x */
int high(vEBTree *T, int x) {

    return x / lower_sqrt(T->u);
}


/* Low part of x */
int low(vEBTree *T, int x) {

    return x % lower_sqrt(T->u);
}


/* Convert cluster number + position into value */
int index_vEB(vEBTree *T, int highValue, int lowValue) {

    return highValue * lower_sqrt(T->u) + lowValue;
}


/* =========================================
   CREATE vEB TREE
   ========================================= */

vEBTree* create_vEB(int u) {

    vEBTree *T =
        (vEBTree*)malloc(sizeof(vEBTree));

    T->u = u;

    T->min = INF;
    T->max = -1;

    /*
       Base case:
       Universe size 2 has no
       summary or clusters.
    */

    if (u <= 2) {

        T->summary = NULL;
        T->cluster = NULL;

    } else {

        int upper = upper_sqrt(u);

        T->summary = create_vEB(upper);

        T->cluster =
            (vEBTree**)malloc(
                upper * sizeof(vEBTree*)
            );

        for (int i = 0; i < upper; i++) {

            T->cluster[i] =
                create_vEB(lower_sqrt(u));
        }
    }

    return T;
}


/* =========================================
   MEMBER
   ========================================= */

int member(vEBTree *T, int x) {

    /*
       Empty tree
    */

    if (T->min == INF) {
        return 0;
    }


    /*
       x is minimum or maximum
    */

    if (x == T->min || x == T->max) {
        return 1;
    }


    /*
       Base case
    */

    if (T->u <= 2) {
        return 0;
    }


    /*
       Recursively search cluster
    */

    return member(
        T->cluster[high(T, x)],
        low(T, x)
    );
}


/* =========================================
   INSERT
   ========================================= */

void insert(vEBTree *T, int x) {

    /*
       If tree is empty,
       x becomes both min and max.
    */

    if (T->min == INF) {

        T->min = x;
        T->max = x;

        return;
    }


    /*
       Ensure x is not smaller than min.
       If it is, swap them.
    */

    if (x < T->min) {

        int temp = x;

        x = T->min;
        T->min = temp;
    }


    /*
       Base case
    */

    if (T->u > 2) {

        int h = high(T, x);
        int l = low(T, x);

        /*
           If cluster is empty,
           insert cluster number into summary.
        */

        if (T->cluster[h]->min == INF) {

            insert(T->summary, h);
        }

        /*
           Insert into cluster.
        */

        insert(T->cluster[h], l);
    }


    /*
       Update maximum
    */

    if (x > T->max) {
        T->max = x;
    }
}


/* =========================================
   SUCCESSOR
   ========================================= */

int successor(vEBTree *T, int x) {

    /*
       Base case
    */

    if (T->u <= 2) {

        if (x == 0 && T->max == 1) {
            return 1;
        }

        return INF;
    }


    /*
       If x is smaller than minimum
    */

    if (T->min != INF && x < T->min) {
        return T->min;
    }


    int h = high(T, x);
    int l = low(T, x);


    /*
       Check successor inside same cluster
    */

    int maxLow = T->cluster[h]->max;

    if (maxLow != -1 && l < maxLow) {

        int offset =
            successor(T->cluster[h], l);

        return index_vEB(T, h, offset);
    }


    /*
       Search summary for next cluster
    */

    int succCluster =
        successor(T->summary, h);

    if (succCluster == INF) {
        return INF;
    }


    int offset =
        T->cluster[succCluster]->min;

    return index_vEB(T, succCluster, offset);
}


/* =========================================
   PREDECESSOR
   ========================================= */

int predecessor(vEBTree *T, int x) {

    /*
       Base case
    */

    if (T->u <= 2) {

        if (x == 1 && T->min == 0) {
            return 0;
        }

        return -1;
    }


    /*
       If x is greater than maximum
    */

    if (T->max != -1 && x > T->max) {
        return T->max;
    }


    int h = high(T, x);
    int l = low(T, x);


    /*
       Check predecessor inside same cluster
    */

    int minLow = T->cluster[h]->min;

    if (minLow != INF && l > minLow) {

        int offset =
            predecessor(T->cluster[h], l);

        return index_vEB(T, h, offset);
    }


    /*
       Search summary for previous cluster
    */

    int predCluster =
        predecessor(T->summary, h);

    if (predCluster == -1) {

        /*
           Check global minimum
        */

        if (T->min != INF && T->min < x) {
            return T->min;
        }

        return -1;
    }


    int offset =
        T->cluster[predCluster]->max;

    return index_vEB(T, predCluster, offset);
}


/* =========================================
   DELETE
   ========================================= */

void delete_vEB(vEBTree *T, int x) {

    /*
       If only one element exists
    */

    if (T->min == T->max) {

        T->min = INF;
        T->max = -1;

        return;
    }


    /*
       Base case
    */

    if (T->u <= 2) {

        if (x == 0) {

            T->min = 1;

        } else {

            T->max = 0;
        }

        return;
    }


    /*
       If deleting minimum,
       replace it with next minimum.
    */

    if (x == T->min) {

        int firstCluster =
            T->summary->min;

        x = index_vEB(
            T,
            firstCluster,
            T->cluster[firstCluster]->min
        );

        T->min = x;
    }


    /*
       Delete x from its cluster
    */

    int h = high(T, x);
    int l = low(T, x);

    delete_vEB(T->cluster[h], l);


    /*
       If cluster becomes empty,
       remove cluster from summary.
    */

    if (T->cluster[h]->min == INF) {

        delete_vEB(T->summary, h);
    }


    /*
       If x was maximum,
       find new maximum.
    */

    if (x == T->max) {

        if (T->summary->max == -1) {

            T->max = T->min;

        } else {

            int maxCluster =
                T->summary->max;

            T->max =
                index_vEB(
                    T,
                    maxCluster,
                    T->cluster[maxCluster]->max
                );
        }
    }
}


/* =========================================
   PRINT STRUCTURE
   ========================================= */

void printStructure(vEBTree *T, int level) {

    if (T == NULL)
        return;

    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    printf("vEB(U=%d, min=%d, max=%d)\n",
           T->u,
           T->min,
           T->max);


    /*
       Base case
    */

    if (T->u <= 2)
        return;


    /*
       Print summary
    */

    for (int i = 0; i < level + 1; i++) {
        printf("    ");
    }

    printf("Summary:\n");

    printStructure(T->summary, level + 2);


    /*
       Print clusters
    */

    for (int i = 0;
         i < upper_sqrt(T->u);
         i++) {

        for (int j = 0; j < level + 1; j++) {
            printf("    ");
        }

        printf("Cluster[%d]:\n", i);

        printStructure(
            T->cluster[i],
            level + 2
        );
    }
}


/* =========================================
   MAIN
   ========================================= */

int main() {

    /*
       Universe size = 16
    */

    int U = 16;

    vEBTree *T = create_vEB(U);


    /* -------------------------------------
       INSERT
       ------------------------------------- */

    printf("========== INSERT ==========\n");

    int values[] = {
        2, 3, 4, 7, 8, 10, 12, 14
    };

    int n = 8;

    printf("Inserting: ");

    for (int i = 0; i < n; i++) {

        printf("%d ", values[i]);

        insert(T, values[i]);
    }

    printf("\n");

    printStructure(T, 0);


    /* -------------------------------------
       MEMBER
       ------------------------------------- */

    printf("\n========== MEMBER ==========\n");

    int searchValues[] = {
        7, 5, 14
    };

    for (int i = 0; i < 3; i++) {

        int x = searchValues[i];

        if (member(T, x)) {

            printf("%d is present.\n", x);

        } else {

            printf("%d is NOT present.\n", x);
        }
    }


    /* -------------------------------------
       SUCCESSOR
       ------------------------------------- */

    printf("\n========== SUCCESSOR ==========\n");

    int x = 7;

    int s = successor(T, x);

    if (s != INF) {

        printf("Successor of %d = %d\n",
               x, s);

    } else {

        printf("No successor exists.\n");
    }


    /* -------------------------------------
       PREDECESSOR
       ------------------------------------- */

    printf("\n========== PREDECESSOR ==========\n");

    x = 10;

    int p = predecessor(T, x);

    if (p != -1) {

        printf("Predecessor of %d = %d\n",
               x, p);

    } else {

        printf("No predecessor exists.\n");
    }


    /* -------------------------------------
       DELETE
       ------------------------------------- */

    printf("\n========== DELETE ==========\n");

    x = 8;

    printf("Deleting %d...\n", x);

    delete_vEB(T, x);

    printf("\nHeap after deletion:\n");

    printStructure(T, 0);


    /* -------------------------------------
       FINAL MEMBER TEST
       ------------------------------------- */

    printf("\n========== FINAL TEST ==========\n");

    if (member(T, 8)) {

        printf("8 is present.\n");

    } else {

        printf("8 is NOT present.\n");
    }


    return 0;
}