/*
 * mathlib.h
 *
 *  Created on: 2015-9-3
 *      Author: Yi
 *
 *	Mathematical calculations for wgsQP
 *
 *
 */

#ifndef MATHLIB_H_
#define MATHLIB_H_

// Print the matrix to the consolo. Matrix stored in a array. w column, h rows.
void show_matrix(float *m, int w, int h);

// Print the matrix to the consolo. Matrix stored in a array. w column, h rows.
// Rosetta.
void show_matrixInt(int *m, int w, int h);

//Find the minimum one of a vector.
float vec_min(float *x, int n);

// Return the index of the minimum element
int minIndex(float *x, int n);

// Find the index of certain element in the vector
int findIndex(int *x, int n, int tar);

// Vector addation
// c = a + b
void vec_add(float *a, float *b, int n,float *c);

// Vector subtraction
// c = a - b
void vec_sub(float *a, float *b, int n,float *c);

// Add two matrices.
// a + b = sum
void mat_add(float *a, float *b, int row, int column, float *sum);

// Do the multiplication 
// A * x = b;
void mat_vec(float *A, float *x, int row, int col, float *b);

// Transpose A, and do the multiplication 
// A' * x = b; 
// Note, the row and col is before 
void matTrans_vec(float *A, float *x, int row, int col, float *b);

//Do the multiplication x'*A = b;
void vec_mat(float *A, float *x, int row, int col, float *b);

// Do the dot product for two array. n is the number of elements
// a' * b
float dot_product(float *a, float *b, int n);

// Swap a vector(matrix not included) v at two positions p1 and p2
// p1 and p2 is from 1 to n (not 0 to n-1)
void swapVecF(float *v, int p1, int p2, int col, float *tmp, int flag);
void swapVecI(int *v, int p1, int p2);

// Swap a positive definite matrix m at two positions p1 and p2
// Achieve the function : H = Pi'*H*Pi; here Pi is the permute function
// p1 and p2 is from 1 to n (not 0 to n-1)
void swapMat(float *m, int p1, int p2, int n, float *tmp);

// Permute a matrix/vector using the permute matrix p
// Note that if the input is a matrix, the row order is permuted
// the order in p is from 0 to m-1
void permut(float *oriMat, int *p, int m, int n, float *mat);

// Recover a permuted matrix/vector using the permute matrix p
// Note that if the input is a matrix, the row order is recovered
void permutReco(float *mat, int *p,  int m, int n, float *oriMat);

// A Cholesky Factorization routine from the book Numerical Recipes in C
// Maybe codes from NRC are more robust?
int chol_NRC(float *A, int n,float *p);

// Cholesky decomposition.
// Rosetta.
void cholesky(float *A, int n, float *L);

// Transpose the matrix m and store the matrix in w.
void transpose(float *m, int w, int h);

// Do back substatution to solve linear equation using LU.
void luEvaluate(float *L,float *U, float*b,int n,float *x,float *y);

// Solve a linear system with lower-triangular matrix using forward substitution
// L * y = b;
void FowSubL(float *L, float *b, int n, float *y, int flag);

// Solve a linear system with upper-triangular matrix using backward substitution
// U * x = y;
void BacSubU(float *U, float *y, int n, float *x, int flag);

// Inverse an upper-triangular matrix using backward substitution
// invR = inv(R), where R is an upper-triangular 
void uInv(float *R, int n, float *invR);

// Matrix multiplication. Just like DSP_sp_mat_mul.c in ti DSPlib.
// x1 * x2 = y
void mat_mul(float *x1, int r1, int c1, float *x2, int c2, float *y);

// Transpose the matrix and do the multiplication
// x1' * x2 = y, Note: the r1 and c1 and rows and columns before transpose
void matTrans_mul(float *x1, int r1, int c1, float *x2, int c2, float *y);

// Transpose the matrix and do the multiplication
// x1 * x2' = y, Note: the r1 and c1 and rows and columns before transpose
void mat_mulTrans(float *x1, int r1, int c1, float *x2, int r2, float *y);

// Compute the Euclid norm of a vector
float norm(float *v, int n);

// Check whether a vector is zero or not
// if v < epsilon, then v is zero 
int isZero(float *v, int n, float epsilon);

// Do the Givens rotation for a two-element vector
// G is a 2*2 matrix
void myplanerot(float x1, float x2, float *G);

// Form the rotation matrix from the Givens rotations
// G is Givens matrix, i j is the row/column need to be rotated, m is the size
// i and j is from 1 to m
void formRot(float *G, int i, int j, int m, float *P);

// Rotation of two rows to produce zero on the below row
// Note, here mat is m*m square matrix
// i and j is from 1 to m
void rowRot(float *mat, float *G, int m, int i, int j);

// Rotation of two columns to produce zero on the right column
// Note, here m is the number of rows of the mat
// n is the number of columns of mat
void colRot(float *mat, float *G, int m, int n, int i, int j);

// QR decomposition using Givens rotation
// A = Q * R;
// size(A) =[row,col]; size(Q) = [row, row]; size(R) = [row, col]; size(G) = [2,2];
// Note: the elements in A will be changed
void qr(float *A, int row, int col, float *Q, float *G);


// Modified Gram-Schmidt QR factorization.     
// Reference:
//       N. J. Higham, Accuracy and Stability of Numerical Algorithms,
//       Second edition, Society for Industrial and Applied Mathematics,
//       Philadelphia, PA, 2002; sec 19.8. Gram-Schmidt QR factorization.
// [m, n] = size(A); [m, n] = size(Q);	[n, n] = size(R);
void gs_m(float *A, int m, int n, float *Q, float *R);

int qrdcmp(float *a, int m, int n, float *c, float *d);

/*  The main routine */
int wgsQP(float *H_ori, float *c_ori, float *AA, float *lx, float *ux, float *lg, 
	int *wf, int *wl, int nf, int ml, float *x, int ndec, int nbc, int ngc, 
	int *orderPermu, float *H, float *c, float *Af, float *Lv, float *Yv, 
	float *Rv, float *pvStar, float *p, float *gx, int *isInWl, float *uv, float *vl, float *wv,
	float *lambdal, float *lambdaf, float *lambda, float *P, float *G,float *tmpVec1, float *tmpVec2, 
	float *tmpMat1, float *tmpMat2, float *tmpMat3, float *tmpMat4, float *tmpMat5, float *tmpMat6,
	float *xStar, int *iterPoint, int maxIter);

#endif /* MATHLIB_H_ */