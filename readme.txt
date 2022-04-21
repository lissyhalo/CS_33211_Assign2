/*
 * Melissa Halozan
 * Assignment 2 : bankers_algorithm.cpp
 * CS OS
 *
 * C program for Banker's Algorithm 
 * see https://www.studytonight.com/operating-system/bankers-algorithm
 *
 */

# to compile
g++ bankers_algorithm.cpp -o bankers

# to run program 
./bankers_algorithm states.txt

# program outputs tables read from file 
# then it checks for safe state and print the safe sequence 

NP = 5, NR = 3
alloc table:
0 0 1
3 0 0
1 0 1
2 3 2
0 0 3
max table:
7 6 3
3 2 2
8 0 2
2 1 2
5 2 3
available:
2 3 2
System is in a safe state!
The safe sequence is as follows:
 P1 -> P3 -> P4 -> P0 -> P2


Table Format:
First Row: NP = Number of processes (max 10) 
NR = Number of Resources (max 10)
NP Rows: NR resources allocated for processes
NP Rows: NR maximum resources for processes
Last Row : NR available resources

5, 3
0, 1, 0
2, 0, 0
3, 0, 2
2, 1, 1
0, 0, 2
7, 5, 3
3, 2, 2
9, 0, 2
2, 2, 2
4, 3, 3
3, 3, 2

 