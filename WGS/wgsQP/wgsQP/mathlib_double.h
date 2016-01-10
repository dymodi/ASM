///*
// * mathlib.h
// *
// *  Created on: 2015-9-3
// *      Author: Yi
// *
// *	Mathematical calculations for wgsQP
// *
// *
// */
//
//#ifndef MATHLIB_H_
//#define MATHLIB_H_
//
//// Print the matrix to the consolo. Matrix stored in a array. w column, h rows.
//void show_matrix(double *m, int w, int h);
//
//// Print the matrix to the consolo. Matrix stored in a array. w column, h rows.
//// Rosetta.
//void show_matrixInt(int *m, int w, int h);
//
////Find the minimum one of a vector.
//double vec_min(double *x, int n);
//
//// Return the index of the minimum element
//int minIndex(double *x, int n);
//
//// Find the index of certain element in the vector
//int findIndex(int *x, int n, int tar);
//
//// Vector addation
//// c = a + b
//void vec_add(double *a, double *b, int n,double *c);
//
//// Vector subtraction
//// c = a - b
//void vec_sub(double *a, double *b, int n,double *c);
//
//// Add two matrices.
//// a + b = sum
//void mat_add(double *a, double *b, int row, int column, double *sum);
//
//// Do the multiplication 
//// A * x = b;
//void mat_vec(double *A, double *x, int row, int col, double *b);
//
//// Transpose A, and do the multiplication 
//// A' * x = b; 
//// Note, the row and col is before 
//void matTrans_vec(double *A, double *x, int row, int col, double *b);
//
////Do the multiplication x'*A = b;
//void vec_mat(double *A, double *x, int row, int col, double *b);
//
//// Do the dot product for two array. n is the number of elements
//// a' * b
//double dot_product(double *a, double *b, int n);
//
//// Swap a vector(matrix not included) v at two positions p1 and p2
//// p1 and p2 is from 1 to n (not 0 to n-1)
//void swapVecF(double *v, int p1, int p2, int col, double *tmp, int flag);
//void swapVecI(int *v, int p1, int p2);
//
//// Swap a positive definite matrix m at two positions p1 and p2
//// Achieve the function : H = Pi'*H*Pi; here Pi is the permute function
//// p1 and p2 is from 1 to n (not 0 to n-1)
//void swapMat(double *m, int p1, int p2, int n, double *tmp);
//
//// Permute a matrix/vector using the permute matrix p
//// Note that if the input is a matrix, the row order is permuted
//// the order in p is from 0 to m-1
//void permut(double *oriMat, int *p, int m, int n, double *mat);
//
//// Recover a permuted matrix/vector using the permute matrix p
//// Note that if the input is a matrix, the row order is recovered
//void permutReco(double *mat, int *p,  int m, int n, double *oriMat);
//
//// A Cholesky Factorization routine from the book Numerical Recipes in C
//// Maybe codes from NRC are more robust?
//int chol_NRC(double *A, int n,double *p);
//
//// Cholesky decomposition.
//// Rosetta.
//void cholesky(double *A, int n, double *L);
//
//// Transpose the matrix m and store the matrix in w.
//void transpose(double *m, int w, int h);
//
//// Do back substatution to solve linear equation using LU.
//void luEvaluate(double *L,double *U, double*b,int n,double *x,double *y);
//
//// Solve a linear system with lower-triangular matrix using forward substitution
//// L * y = b;
//void FowSubL(double *L, double *b, int n, double *y, int flag);
//
//// Solve a linear system with upper-triangular matrix using backward substitution
//// U * x = y;
//void BacSubU(double *U, double *y, int n, double *x, int flag);
//
//// Inverse an upper-triangular matrix using backward substitution
//// invR = inv(R), where R is an upper-triangular 
//void uInv(double *R, int n, double *invR);
//
//// Matrix multiplication. Just like DSP_sp_mat_mul.c in ti DSPlib.
//// x1 * x2 = y
//void mat_mul(double *x1, int r1, int c1, double *x2, int c2, double *y);
//
//// Transpose the matrix and do the multiplication
//// x1' * x2 = y, Note: the r1 and c1 and rows and columns before transpose
//void matTrans_mul(double *x1, int r1, int c1, double *x2, int c2, double *y);
//
//// Transpose the matrix and do the multiplication
//// x1 * x2' = y, Note: the r1 and c1 and rows and columns before transpose
//void mat_mulTrans(double *x1, int r1, int c1, double *x2, int r2, double *y);
//
//// Compute the Euclid norm of a vector
//double norm(double *v, int n);
//
//// Check whether a vector is zero or not
//// if v < epsilon, then v is zero 
//int isZero(double *v, int n, double epsilon);
//
//// Do the Givens rotation for a two-element vector
//// G is a 2*2 matrix
//void myplanerot(double x1, double x2, double *G);
//
//// Form the rotation matrix from the Givens rotations
//// G is Givens matrix, i j is the row/column need to be rotated, m is the size
//// i and j is from 1 to m
//void formRot(double *G, int i, int j, int m, double *P);
//
//// Rotation of two rows to produce zero on the below row
//// Note, here mat is m*m square matrix
//// i and j is from 1 to m
//void rowRot(double *mat, double *G, int m, int i, int j);
//
//// Rotation of two columns to produce zero on the right column
//// Note, here m is the number of rows of the mat
//// n is the number of columns of mat
//void colRot(double *mat, double *G, int m, int n, int i, int j);
//
//// QR decomposition using Givens rotation
//// A = Q * R;
//// size(A) =[row,col]; size(Q) = [row, row]; size(R) = [row, col]; size(G) = [2,2];
//// Note: the elements in A will be changed
//void qr(double *A, int row, int col, double *Q, double *G);
//
//
//// Modified Gram-Schmidt QR factorization.     
//// Reference:
////       N. J. Higham, Accuracy and Stability of Numerical Algorithms,
////       Second edition, Society for Industrial and Applied Mathematics,
////       Philadelphia, PA, 2002; sec 19.8. Gram-Schmidt QR factorization.
//// [m, n] = size(A); [m, n] = size(Q);	[n, n] = size(R);
//void gs_m(double *A, int m, int n, double *Q, double *R);
//
///*  The main routine */
////int wgsQP(double *H, double *c, double *AA, double *lx, double *ux, double *lg, int *wf, int *wl, int nf, int ml, double *x, int ndec, int nbc, int ngc, double *xStar);
//
//*  The main routine */
//int wgsQP(double *H_ori, double *c_ori, double *AA, double *lx, double *ux, double *lg, 
//	int *wf, int *wl, int nf, int ml, double *x, int ndec, int nbc, int ngc, 
//	int *orderPermu, double *H, double *c, double *Af, double *Lv, double *Yv, 
//	double *Rv, double *pvStar, double *p, double *gx, int *isInWl, double *uv, double *vl, double *wv,
//	double *lambdal, double *lambdaf, double *lambda, double *P, double *G,double *tmpVec1, double *tmpVec2, 
//	double *tmpMat1, double *tmpMat2, double *tmpMat3, double *tmpMat4, double *tmpMat5, double *tmpMat6,
//	double *xStar);
//
//#endif /* MATHLIB_H_ */