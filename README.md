# ADSA Lab 
## Lab 1
Write a program to implement stack in 1) Array 2) Linked List

## Lab 2
Write a program to impelement following sorting algorithms 1) Heap 2) Merge 3) Quick

## Lab 3
Experiment 1: 

B-Trees: Insert, Search, Delete (order t) 

Aim: Implement a B-Tree of minimum degree  ‘t’  supporting insertion, search and deletion. Demonstrate with sample keys. 

Background: Use standard B-tree algorithms (Cormen et al.). 

Sample I/O: Insert: 10 20 5 6 12 30 7 17; search 6; delete 6. 

## Lab 4
Lab Question 1: Implementation of Fibonacci Heap Operations 

Aim: 
Implement a Fibonacci Heap and demonstrate key mergeable heap operations. 

Tasks: 
a) Implement the following operations on a Fibonacci Heap: 

Insert(x) – Insert a new node 
Find-Min() – Return the minimum key 
Union(H1, H2) – Merge two Fibonacci Heaps 

b) Display the heap structure before and after each operation. 

Expected Output: Display of heap structure after each insert and merge operation. 

Verification of the minimum key after each step. 

Lab Question 2: Key Decrease and Node Deletion in Fibonacci Heap 

Aim: 
Demonstrate decrease-key and delete-node operations in a Fibonacci Heap. 

Tasks: 
a) Construct a Fibonacci Heap with at least 10 nodes. 
b) Perform the following operations sequentially: 

Decrease a key (use cascading cuts if required). 

Delete a node by decreasing its key to -∞ and performing Extract-Min(). 
c) Print the heap structure after each step. 

Expected Output: Intermediate states of the heap showing cascading cuts. 

Final heap after deletion. 

Lab Question 3: Implementation of a van Emde Boas Tree 

Aim: 
Implement a van Emde Boas (vEB) Tree using recursive structure and demonstrate key operations. 

Tasks: 
a) Implement a vEB Tree with universe size U = 16. 
b) Implement and test the following operations: 

Insert(x) 
Member(x) 
Successor(x) and Predecessor(x) 
Delete(x) 

c) Demonstrate the recursive layout of the structure and print results of each operation. 

Expected Output: Structure visualization (showing clusters and summary). 

Correct output for predecessor/successor queries. 

## Lab 5
Find the shortest paths from a single source vertex to all other vertices in a weighted graph using the Bellman-Ford algorithm, which works even with negative edge weights.