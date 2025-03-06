#ifndef MATRICES_H
#define MATRICES_H

#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

#define MOD 10007

// Check if matrix with id = ind exists
// total - 1 = max id, ok = matrix count
int exist(int total, int ok, int ind);

// Allocate mem for matrix
int **alloc_mat(int n, int m);

// Free matrix
void free_mat(int **a, int n);

// Read matrix
void read_mat(int **a, int n, int m);

// Multiply matrix
void mult(int **a, int **b, int **temp, int n, int m, int nm);

// Print matrix function used when calling the command
void print(int total, int ok, int ***v, int *n_m, int *m_m);

// Matrix size
void dim(int total, int ok, int *n_m, int *m_m);

// Read array
void read_arr(int *vec, int n);

// Realloc array
void red_arr(int **n_mat, int **m_mat, int **sume, int n, int inc, int *leak);

// Realloc matrix
void red_mat(int ****tab, int n, int inc, int *leak);

// Add matrix to matrix array
void add_mat(int n, int m, int ***v, int *n_m, int *m_m, int *i, int c, int *leak);

// Resize function used by the command
int redim(int total, int ok, int ***v, int *n, int *m, int *leak);

// Check if multiplication is possible
int multip_verif(int total, int ok, int *n_m, int *m_m, int ind1, int ind2);

// Update sum of matrixes
void sum_all(int *sume, int ***v, int *n, int *m, int nr);

// Swap values
void swap_var(int *a, int *b);

// Sort matrixes by sum
void sort_mat(int *sume, int ***v, int *n, int *m, int nr);

// Transpose matrix
void transp(int total, int ok, int ***v, int *n, int *m, int *leak);

// Copy 2nd matrix in the first one
void copy_mat(int **a, int **b, int n);

// Pow's a matrix (logn)
int pow_mat(int total, int ok, int ***v, int *n, int *m, int *leak);

// Delete matrix
void rem_mat(int total, int ind, int ***v, int *n, int *m);

// Clear all allocs
void clear_mem(int ***v, int *s, int *n, int *m, char *a, int nr);

// Strassen matrices
int aloc_st(int ***v, int n, int n_m, int *leak);

// Sum of 2 matrices
void sum_mat(int **a, int **b, int **temp, int n);

// Difference of 2 matrices
void dif_mat(int **a, int **b, int **temp, int n);
// A1 to A4 used in Strassen
void form_mini(int **t, int ***a, int n);

// Quarters for Strassen
void q_mat(int ***c, int ***m, int n);

// Strassen function for fast pow's
void strassen(int **t1, int **t2, int **temp, int n, int *leak);

#endif // MATRICES_H
