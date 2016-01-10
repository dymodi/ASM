// //*
// //* mathlib.c
// //*
// //*  Created on: 2015-9-3
// //*      Author: Yi
// //*	Mathematical calculations for wgsQP
// //*  For Visual Studio Debug
// //*
// //*
//
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//
//// Print the matrix to the consolo. 
//void show_matrix(double *m, int w, int h) {
//	int i, j;
//	for (i = 0; i < h; i++) {
//		for (j = 0; j < w; j++)
//			printf("%.4f ", m[i * w + j]);
//		putchar('\n');
//	}
//}
//
//// Print the matrix to the consolo. 
//void show_matrixInt(int *m, int w, int h) {
//	int i, j;
//	for (i = 0; i < h; i++) {
//		for (j = 0; j < w; j++)
//			printf("%d ", m[i * w + j]);
//		putchar('\n');
//	}
//}
//
//// Find the minimum one of a vector.
//double vec_min(double *x, int n) {
//	double min;
//	int i;
//	min = x[0];
//	for(i=1;i<n;i++) {
//		if(x[i]<min)
//			min = x[i];
//	}
//	return min;
//}
//
//// Return the index of the minimum element
//int minIndex(double *x, int n) {
//	double min;
//	int i, index;
//	min = x[0];
//	index = 0;
//	for(i=1;i<n;i++) {
//		if(x[i]<min) {
//			min = x[i];
//			index = i;
//		}
//	}
//	return index;
//}
//
//// Find the index of certain element in the vector
//// Note: the index returned is from 1 to n (not 0 to n-1)
//int findIndex(int *x, int n, int tar) {
//	int i;
//	for (i = 0; i < n; i++) {
//		if (x[i] == tar) 
//			return i+1;
//	}
//	printf("Target not found in the vector!\n");
//	return -1;
//}
//
//// Vector addation
//// c = a + b
//void vec_add(double *a, double *b, int n,double *c) {
//	int i;
//	for(i=0;i<n;i++)	
//		c[i]=a[i]+b[i];
//}
//
//// Vector subtraction
//// c = a - b
//void vec_sub(double *a, double *b, int n,double *c) {
//	int i;
//	for(i=0;i<n;i++)
//		c[i]=a[i]-b[i];
//}
//
//// Add two matrices.
//// a + b = sum
//void mat_add(double *a, double *b, int row, int column, double *sum) {
//	int i;
//	for(i=0;i<row*column;i++)
//		sum[i] = a[i]+b[i];
//}
//
//// Do the multiplication 
//// A * x = b;
//void mat_vec(double *A, double *x, int row, int col, double *b) {
//	int i,j;
//	for(i=0;i<row;i++) {
//		b[i]=0;
//		for(j=0;j<col;j++)
//			b[i] += A[i*col+j]*x[j];				//Attention!2014.5.5
//	}
//}
//
//// Transpose A, and do the multiplication 
//// A' * x = b; 
//// Note, the row and col is before 
//void matTrans_vec(double *A, double *x, int row, int col, double *b) {
//	int i,j;
//	for(i=0; i<col; i++) {
//		b[i]=0;
//		for(j=0; j<row; j++)
//			b[i] += A[j*col+i]*x[j];				//Attention!2014.5.5
//	}
//}
//
////Do the multiplication x'*A = b;
//void vec_mat(double *A, double *x, int row, int col, double *b)
//{
//	int i,j;
//	for(j=0;j<col;j++) {
//		b[j]=0;
//		for(i=0;i<row;i++)
//			b[j]+=A[i*col+j]*x[i];				//Attention!2014.5.5
//	}
//}
//
//// Do the dot product for two array. n is the number of elements
//// a' * b
//double dot_product(double *a, double *b, int n) {
//	double sum = 0;
//	int i;
//	for (i = 0; i < n; i++) {
//		sum += a[i] * b[i];
//	}
//	return sum;
//}
//
//
//// Swap a vector/matrix v at two rows p1 and p2
//// p1 and p2 is from 1 to n (not 0 to n-1)
//void swapVecF(double *v, int p1, int p2, int col, double *tmp, int flag) {
//	
//	// flag == 0 means to swap rows
//	// flag == 1 means to swap columns (now col is actually rows)
//	int i;
//	if (flag == 0) {
//		for (i = 0; i < col; i++)
//			tmp[i] = v[(p1-1)*col+i];
//		for (i = 0; i < col; i++)
//			v[(p1-1)*col+i] = v[(p2-1)*col+i];
//		for (i = 0; i < col; i++)
//			v[(p2-1)*col+i] = tmp[i];
//	}
//	else if (flag == 1) {
//		for (i = 0; i < col; i++)
//			tmp[i] = v[i*col+(p1-1)];
//		for (i = 0; i < col; i++)
//			v[i*col+(p1-1)] = v[i*col+(p2-1)];
//		for (i = 0; i < col; i++)
//			v[i*col+(p2-1)] = tmp[i];
//	}
//	else
//		printf("Wrong flags!\n");
//}
//
//// Swap a vector(matrix not included) v at two positions p1 and p2
//// p1 and p2 is from 1 to n (not 0 to n-1)
//void swapVecI(int *v, int p1, int p2) {
//	int tmp = v[p1-1];
//	v[p1-1] = v[p2-1];
//	v[p2-1] = tmp;
//}
//
//// Swap a positive definite matrix m at two positions p1 and p2
//// Achieve the function : H = Pi'*H*Pi; here Pi is the permute function
//// p1 and p2 is from 1 to n (not 0 to n-1)
//void swapMat(double *m, int p1, int p2, int n, double *tmp) {
//	
//	int i;
//
//	for (i = 0; i < n; i++) 
//		tmp[i] = m[(p1-1)*n+i];
//	for (i = 0; i < n; i++) 
//		m[(p1-1)*n+i] = m[(p2-1)*n+i];
//	for (i = 0; i < n; i++) 
//		m[(p2-1)*n+i] = tmp[i];
//
//	for (i = 0; i < n; i++) 
//		tmp[i] = m[i*n+(p1-1)];
//	for (i = 0; i < n; i++) 
//		m[i*n+(p1-1)] = m[i*n+(p2-1)];
//	for (i = 0; i < n; i++) 
//		m[i*n+(p2-1)] = tmp[i];
//}
//
//// Permute a matrix/vector using the permute matrix p (0 ~ n-1)
//// Note that if the input is a matrix, the row order is permuted
//// the order in p is from 0 to m-1
//void permut(double *oriMat, int *p, int m, int n, double *mat) {
//
//	int i,j;
//	for (i = 0; i < m; i++) {
//		for (j = 0; j < n; j++) {
//			mat[i*n+j] = oriMat[p[i]*n+j];
//		}		
//	}	
//	for (i = 0; i < m*n; i++)
//		oriMat[i] = mat[i];
//}
//
//// Recover a permuted matrix/vector using the permute matrix p (0 ~ n-1)
//// Note that if the input is a matrix, the row order is recovered
//void permutReco(double *mat, int *p,  int m, int n, double *oriMat) {
//
//	int i, j;
//
//	for (i = 0; i < m; i++) {
//		for (j=0; j < n; j++) {
//			oriMat[p[i]*n+j] = mat[i*n+j];
//		}
//	}
//	for (i = 0; i < m*n; i++)
//		mat[i] = oriMat[i];
//}
//
//
//// A Cholesky Factorization routine from the book Numerical Recipes in C
//// Maybe codes from NRC are more robust?
//int chol_NRC(double *A, int n,double *p)
//{
//	int i,j,k;
//	int flag = 1;
//	double sum;
//	for (i=1;i<=n;i++) {
//		for (j=i;j<=n;j++) {
//			for (sum=A[(i-1)*n+(j-1)],k=i-1;k>=1;k--) {
//				sum -= A[(i-1)*n+(k-1)]*A[(j-1)*n+(k-1)];
//			}
//			if (i == j) {
//				if (sum <= 0.0) {
//					printf("Factorization Failed.\n");
//					flag = 0;
//				}
//				p[i-1]=sqrt(sum);
//			}
//			else A[(j-1)*n+(i-1)]=sum/p[i-1];
//		}
//	}
//	return flag;
//}
//
//
//// Cholesky decomposition.
//// Rosetta.
//void cholesky(double *A, int n, double *L)
//{	
//	int i,j,k;
//	double s;
//	//double *L = (double*)calloc(n * n, sizeof(double));
//	//   if (L == NULL)
//	//       exit(EXIT_FAILURE);
//
//    for (i = 0; i < n; i++)
//        for (j = 0; j < (i+1); j++) {
//        	s = 0;
//            for (k = 0; k < j; k++)
//                s += L[i * n + k] * L[j * n + k];
//				L[i * n + j] = (i == j) ?
//            			sqrt(A[i * n + i] - s) :
//						//sqrtsp(A[i * n + i] - s) :
//                           (1.0 / L[j * n + j] * (A[i * n + j] - s));
//        }
//
//    //return L;
//}
//
//
//// Transpose the matrix m and store the matrix in w.
//void transpose(double *m, int w, int h)
//{
//	int start, next, i;
//	double tmp;
//
//	for (start = 0; start <= w * h - 1; start++) {
//		next = start;
//		i = 0;
//		do {	i++;
//			next = (next % h) * w + next / h;
//		} while (next > start);
//		if (next < start || i == 1) continue;
//
//		tmp = m[next = start];
//		do {
//			i = (next % h) * w + next / h;
//			m[next] = (i == start) ? tmp : m[i];
//			next = i;
//		} while (next > start);
//	}
//}
//
//
//// Do back substatution to solve linear equation using LU.
//void luEvaluate(double *L,double *U, double*b,int n,double *x,double *y)
//{	
//	int i,j;
//	double temp = 0;
//	if(x == NULL || y == NULL)
//		exit(0);
//
//	for (i = 0; i < n; i++)
//		y[i] = 0;
//
//	//Foward solve Ly = b;
//	y[0] = b[0]/L[0];
//	for(i=1;i<n;i++)
//	{
//		for(j=0;j<i;j++)
//		{
//			temp += L[i*n+j]*y[j];
//		}
//		y[i] = b[i] - temp;
//		y[i] = y[i]/L[i*n+i];
//		temp = 0;
//	}
//	//show_matrix(y,1,n);
//
//	//Backward solve Ux = y
//	x[n-1] = y[n-1]/U[n*n-1];
//	temp = 0;
//	for(i=n-2;i>=0;i--)
//	{
//		for(j=i+1;j<n;j++)
//		{
//			temp += U[i*n+j]*x[j];
//		}
//		x[i] = y[i] - temp;
//		x[i] = x[i]/U[i*n+i];
//		temp = 0;
//	}
//}
//
//
//// Solve a linear system with lower-triangular matrix using forward substitution
//// L * y = b;
//void FowSubL(double *L, double *b, int n, double *y, int flag) {
//	
//	// flag == 0, means L is naturally an lower-triangular matrix
//	// flag == 1, means L will be lower-triangular after transpose
//
//	double temp = 0;
//	int i, j;
//
//	//Foward solve Ly = b;
//	if (flag == 0) {
//		y[0] = b[0]/L[0];
//		for(i=1;i<n;i++) {
//			for(j=0;j<i;j++) {
//				temp += L[i*n+j]*y[j];
//			}
//			y[i] = b[i] - temp;
//			y[i] = y[i]/L[i*n+i];
//			temp = 0;
//		}
//	}
//	else if (flag == 1) {
//		y[0] = b[0]/L[0];
//		for(i=1;i<n;i++) {
//			for(j=0;j<i;j++) {
//				temp += L[j*n+i]*y[j];
//			}
//			y[i] = b[i] - temp;
//			y[i] = y[i]/L[i*n+i];
//			temp = 0;
//		}
//	}
//	else
//		printf("Wrong flag!\n");
//
//}
//
//// Solve a linear system with upper-triangular matrix using backward substitution
//// U * x = y;
//void BacSubU(double *U, double *y, int n, double *x, int flag) {
//	
//	// flag == 0, means U is naturally an upper-triangular matrix
//	// flag == 1, means U will be upper-triangular after transpose
//
//	double temp = 0;
//	int i, j;
//
//	//Backward solve Ux = y
//	if (flag == 0) {		
//		x[n-1] = y[n-1]/U[n*n-1];
//		for(i=n-2;i>=0;i--) {
//			for(j=i+1;j<n;j++) {
//				temp += U[i*n+j]*x[j];
//			}
//			x[i] = y[i] - temp;
//			x[i] = x[i]/U[i*n+i];
//			temp = 0;
//		} 
//	}
//	else if (flag == 1) {
//		x[n-1] = y[n-1]/U[n*n-1];
//		for(i=n-2;i>=0;i--) {
//			for(j=i+1;j<n;j++) {
//				temp += U[j*n+i]*x[j];
//			}
//			x[i] = y[i] - temp;
//			x[i] = x[i]/U[i*n+i];
//			temp = 0;
//		} 
//	}
//	else 
//		printf("Wrong flag!\n");
//
//
//}
//
//
//// Inverse an upper-triangular matrix using backward substitution
//// invR = inv(R), where R is an upper-triangular 
//void uInv(double *R, int n, double *invR) {
//
//	int i, j, k;
//	double tmp;
//
//	for (i = 0; i < n; i++)
//		for (j = 0; j < i; j++)
//			invR[i*n+j] = 0;
//
//	for (i = 0; i < n; i++) 
//		invR[i*n+i] = 1/R[i*n+i];
//	for (j = n; j > 0; j--) {
//		for (i = j-1; i > 0; i--) {
//			tmp = 0;
//			for (k = 1; k <= j-i; k++) 
//				tmp += R[(i-1)*n+(i-1+k)]*invR[(i-1+k)*n+j-1];
//			invR[(i-1)*n+j-1]= -1/R[(i-1)*n+i-1]*tmp;
//		}
//	}
//}
//
//
//// Matrix multiplication. 
//// x1 * x2 = y
//void mat_mul(double *x1, int r1, int c1, double *x2, int c2, double *y) {
//	int i,j,k;	
//	for(i=1;i<=r1;i++) {
//		for(j=1;j<=c2;j++) {
//			y[(i-1)*c2+(j-1)]=0;
//			for(k=1;k<=c1;k++) 
//				y[(i-1)*c2+(j-1)]+=x1[(i-1)*c1+(k-1)]*x2[(k-1)*c2+(j-1)];			
//		}
//	}
//}
//
//// Transpose the matrix and do the multiplication
//// x1' * x2 = y, Note: the r1 and c1 and rows and columns before transpose
//void matTrans_mul(double *x1, int r1, int c1, double *x2, int c2, double *y) {
//	int i, j, k;
//	for (i = 0; i < c1; i++) {
//		for (j = 0; j < c2; j++) {
//			y[i*c2+j] = 0;
//			for (k = 0; k < r1; k++)
//				y[i*c2+j] += x1[k*c1+i]*x2[k*c2+j];
//		}
//	}
//}
//
//// Transpose the matrix and do the multiplication
//// x1 * x2' = y, Note: the r1 and c1 and rows and columns before transpose
//void mat_mulTrans(double *x1, int r1, int c1, double *x2, int r2, double *y) {
//	int i,j,k;	
//	for(i = 0; i < r1; i++) {
//		for(j = 0; j < r2; j++) {
//			y[i*r2 + j] = 0;
//			for( k = 0; k < c1; k++) 
//				y[i*r2 + j] += x1[i*c1 + k] * x2[j*c1 + k];			
//		}
//	}
//}
//
//// Compute the Euclid norm of a vector
//double norm(double *v, int n) {
//	int i;
//	double en = 0.0;
//	for (i = 0; i < n; i++)
//		en += v[i]*v[i];
//	en = sqrt(en);
//	return en;
//}
//
//// Check whether a vector is zero or not
//// if v < epsilon, then v is zero 
//int isZero(double *v, int n, double epsilon) {
//	int i;
//
//	for (i = 0; i < n; i++) {
//		if (v[i] > epsilon || v[i] < -epsilon)
//			return 0;
//	}
//	return 1;
//}
//
//// Do the Givens rotation for a two-element vector
//// G is a 2*2 matrix
//void myplanerot(double x1, double x2, double *G) {
//
//	double r;
//
//	if (x2 < 0.0000001 && x2 > -0.0000001) {
//		G[0] = 1;
//		G[1] = 0;
//		G[2] = 0;
//		G[3] = 1;
//	}
//	else {
//		r = sqrt(x1 * x1 + x2 * x2);
//		G[0] = x1/r;
//		G[1] = x2/r;
//		G[2] = -x2/r;
//		G[3] = x1/r;
//	}
//}
//
//// Form the rotation matrix from the Givens rotations
//// G is Givens matrix, i j is the row/column need to be rotated, m is the size
//// i and j is from 1 to m
//void formRot(double *G, int i, int j, int m, double *P) {
//	
//	int k1, k2;
//
//	for (k1 = 0; k1 < m*m; k1 ++)
//		P[k1] = 0;
//	for (k1 = 0; k1 < m; k1++)
//		P[k1*m+k1] =1;
//
//	P[(i-1)*m+(i-1)] = G[0];
//	P[(j-1)*m+(j-1)] = G[3];
//	P[(i-1)*m+(j-1)] = G[1];
//	P[(j-1)*m+(i-1)] = G[2];
//
//}
//
//// Rotation of two rows to produce zero on the below row
//// Note, here m is the column of the mat
//// i and j is from 1 to m
//void rowRot(double *mat, double *G, int m, int i, int j) {
//
//	int k;
//	
//	double tmp1, tmp2;	
//	for (k = 0; k < m; k++) {
//		tmp1 = mat[(i-1)*m+k];
//		tmp2 = mat[(j-1)*m+k];
//		mat[(i-1)*m+k] = G[0]*tmp1+G[1]*tmp2;
//		mat[(j-1)*m+k] = G[2]*tmp1+G[3]*tmp2;
//	}	
//}
//
//// Rotation of two columns to produce zero on the right column
//// Note, here m is the number of rows of the mat
//// n is the number of columns of mat
//void colRot(double *mat, double *G, int m, int n, int i, int j) {
//
//	int k;
//	double tmp1, tmp2;
//	for (k = 0; k < m; k++) {
//		tmp1 = mat[k*n+i-1];
//		tmp2 = mat[k*n+j-1];
//		mat[k*n+i-1] = G[0]*tmp1+G[1]*tmp2;
//		mat[k*n+j-1] = G[2]*tmp1+G[3]*tmp2;
//	}
//}
//
//
//// QR decomposition using Givens rotation
//// A = Q * R;
//// size(A) =[row,col]; size(Q) = [row, row]; size(R) = [row, col]; size(G) = [2,2];
//// Note: the elements in A will be changed
//void qr(double *A, int row, int col, double *Q, double *G) {
//
//	int i,j, colTimes;
//
//	for (i = 0; i < row*row; i++)
//		Q[i] = 0;
//	for (i = 0; i < row; i++)
//		Q[i*row+i] = 1;
//
//	if (row > col)
//		colTimes = col;
//	else
//		colTimes = row-1;
//
//	for (i = 0; i < colTimes; i++) {
//		for (j = 0; j < row-1-i; j++) {			
//			myplanerot(A[(row-j-2)*col+i],A[(row-j-1)*col+i],G);
//			printf("%f and %f\n",A[(row-j-2)*col+i],A[(row-j-1)*col+i]);
//			rowRot(A,G,col,(row-j-1),(row-j));
//			rowRot(Q,G,row,(row-j-1),(row-j));
//			printf("G:\n");show_matrix(G,2,2);putchar('\n');
//			printf("Q:\n");show_matrix(Q,row,row);putchar('\n');
//			printf("R:\n");show_matrix(A,col,row);putchar('\n');
//			
//		}
//	}
//
//	transpose(Q,row,row);
//}
//
//// Modified Gram-Schmidt QR factorization.     
//// Reference:
////       N. J. Higham, Accuracy and Stability of Numerical Algorithms,
////       Second edition, Society for Industrial and Applied Mathematics,
////       Philadelphia, PA, 2002; sec 19.8. Gram-Schmidt QR factorization.
//// [m, n] = size(A); [m, n] = size(Q);	[n, n] = size(R);
//void gs_m(double *A, int m, int n, double *Q, double *R) {
//
//	int i, j, k, l;
//	double en;
//
//	for (i = 0; i < m*n; i++)
//		Q[i] = 0;
//	for (i = 0; i < n*n; i++)
//		R[i] = 0;
//
//	for (i = 0; i < n; i++) {
//		en = 0.0;
//		for (j = 0; j < m; j++)
//			en += A[j*n+i]*A[j*n+i];
//		en = sqrt(en);
//		R[i*n+i] = en;
//		
//		for (j = 0; j < m; j++)
//			Q[j*n+i] = A[j*n+i]/en;
//
//		for (j = i+1; j < n; j++) {
//			en = 0.0;
//			for (k = 0; k < m; k++)
//				en += Q[k*n+i]*A[k*n+j];
//			R[i*n+j] = en;
//		}
//
//		for (j = 0; j < m; j++) {
//			for (k = i+1; k < n; k++) {
//				A[j*n+k] = A[j*n+k] - Q[j*n+i]*R[i*n+k];
//			}
//		}
//
//	}
//
//}
//
////*  The main routine */
//int wgsQP(double *H_ori, double *c_ori, double *AA, double *lx, double *ux, double *lg, 
//	int *wf, int *wl, int nf, int ml, double *x, int ndec, int nbc, int ngc, 
//	int *orderPermu, double *H, double *c, double *Af, double *Lv, double *Yv, 
//	double *Rv, double *pvStar, double *p, double *gx, int *isInWl, double *uv, double *vl, double *wv,
//	double *lambdal, double *lambdaf, double *lambda, double *P, double *G,double *tmpVec1, double *tmpVec2, 
//	double *tmpMat1, double *tmpMat2, double *tmpMat3, double *tmpMat4, double *tmpMat5, double *tmpMat6,
//	double *xStar) {
//
//	// Variables declaration
//	int maxIter = 200;
//	double alpha;
//	int nv = ndec - nf;
//	int i, j, index, indexJ;
//	int consIndex, xIndex, boundIndex, fixedIndex, fixedPos, iter, generalIndex;	
//	double minLambdal, minLambdaf, minLambda, tmpAlpha, ap;
//	double eta, rau, gamma, mu, ve, tmp, tau, diff, maxDiff;
//	int addBoundConstraint, addGeneralConstraint;
//	int flag = 1;
//	int needCheckFlag = 0;
//	int tmpFlag = 0;
//	FILE *fp_Rv, *fp_invRv, *fp_H;
//
//	fp_Rv = fopen("Rv.txt","w");
//	fp_invRv = fopen("invRv.txt","w");
//	fp_H = fopen("H.txt","w");
//
//	// Varaibles check
//	//printf("H:\n"); show_matrix(H_ori,ndec,ndec); putchar('\n');
//	for (i = 0; i < ndec; i++) {
//		for (j = 0; j < ndec; j++) {
//			fprintf(fp_H,"%lf\t",H_ori[i*ndec+j]);
//		}
//		putchar('\n');
//	}
//		
//	printf("c:\n"); show_matrix(c_ori,ndec,1); putchar('\n');
//	printf("nf: %d, ml: %d\n",nf,ml);
//	printf("x:\n"); show_matrix(x,ndec,1); putchar('\n');
//
//	
//
//
//	// Here we check whether the intial x is feasible with given constraints
//	for (i = 0; i<nbc; i++) {
//		if (x[i] < lx[i]-0.000001 || x[i] > ux[i]+0.000001) {
//			printf("Initial x infeasible with bound constraint!\n");
//			return 0;
//		}
//		mat_vec(AA,x,ngc,ndec,tmpVec1);		// tmpVec1 = AA * x;
//		vec_sub(tmpVec1,lg,ngc,tmpVec1);		// tmpVec1 = AA * x - lg;
//		if (vec_min(tmpVec1,ngc) < -0.000001) {
//			printf("Initial x infeasible with general constraint!\n");
//			return 0;
//		}
//	}										// tmpVec1 Free
//
//	// Here we check whether the initial x accords with the initial working set
//	for (i = 0; i < nf; i++) {
//		consIndex = wf[i];
//		if (consIndex <= ndec) {
//			if (x[consIndex-1] - lx[consIndex-1] > 0.000000001) {
//				printf("Initial x does not fit with initial working set! (Bound constraint)\n");
//				flag = 0;
//			}
//		}
//		else {
//			if (x[consIndex-1-ndec]- ux[consIndex-1-ndec] > 0.000000001) {
//				printf("Initial x does not fit with initial working set! (Bound constraint)\n");
//				flag = 0;
//			}
//		}
//	}
//	for (i = 0; i < ml; i++) {
//		consIndex = wl[i];
//		for (j = 0; j < ndec; j++) {
//			tmpVec1[j] = AA[(consIndex-1)*ndec+j];	// tmpVec1 = AA(consIndex,:);
//		}
//		if (dot_product(tmpVec1,x,ndec) - lg[consIndex-1] > 0.000000001) {
//			printf("Initial x does not fit with initial working set! (General constraint)\n");
//			flag = 0;
//		}
//	}												// tmpVec1 Free.
//
//	// Here order is used to keep track of the order change of decision variables
//	for (i = 0; i < ndec; i++) 
//		orderPermu[i] = i;		// Note, in Matlab, order is 1:ndec; in C, order is 0:ndec-1
//	for (i = 0; i < ndec*ndec; i++)
//		H[i] = H_ori[i];
//	for (i = 0; i < ndec; i++)
//		c[i] = c_ori[i];
//
//	// If the last nf items of x is not according with the initial bound constraints
//	// we should adjust it to meet the requirement of the algorithm
//	for (i = 0; i < nf; i++) {
//		boundIndex = wf[i];
//		fixedIndex = boundIndex % ndec;
//		if (fixedIndex==0)
//			fixedIndex = ndec;
//		fixedPos = nv+1;
//		if (fixedIndex <= nv) { // means the fixed item of x is in the first nv rows, needs adjustment              
//			swapVecI(orderPermu, fixedPos, fixedIndex);		
//			swapMat(H,fixedPos,fixedIndex,ndec,tmpMat6);        
//			tmpFlag = 1;
//		}
//	}	
//
//	// Compute and update gx
//	mat_vec(H_ori,x,ndec,ndec,gx);
//	vec_add(c_ori,gx,ndec,gx);
//	if (tmpFlag == 1)
//		permut(gx,orderPermu,ndec,1,tmpMat6);
//
//	// Initialization of isInWl
//	for (i = 0; i < ngc; i++) 
//		isInWl[i] = 0;
//	// isInWl is used to check whether a general constraint is in the working set or not
//	for (i = 0; i < ml; i++)
//		isInWl[wl[i]-1] = 1;	// Note that the index of the 1st element in isInWl is 
//
//	// Initialize Hv, Rv
//	for (i = 0; i < ndec*ndec; i++)
//		tmpMat1[i] = H[i];
//	chol_NRC(tmpMat1, ndec, tmpVec1);
//	for (i = 0; i < ndec; i++)
//		tmpMat1[i*ndec+i] = tmpVec1[i];
//	for (i = 0; i < ndec; i++)
//		for (j = i+1; j < ndec; j++)
//			tmpMat1[i*ndec+j] = 0;
//
//	for (i = 0; i < nv; i++)
//		for (j = 0; j < nv; j++)
//			Rv[i*nv+j] = tmpMat1[i*ndec+j];
//	transpose(Rv,nv,nv);
//
//	// Compute pStar for the first iteration
//	if (ml == 0) {				
//		for (i = 0; i < nv; i++)
//			tmpVec1[i] = -gx[i];
//		//printf("Rv':\n"); show_matrix(tmpMat1,nv,nv); putchar('\n');
//		//printf("-gv:\n"); show_matrix(tmpVec1,nv,1); putchar('\n');	
//		//printf("orderPermu:\n"); show_matrixInt(orderPermu,ndec,1); putchar('\n');	
//		
//		FowSubL(Rv,tmpVec1,nv,tmpMat2,1);	// tmpMat2 = MIDDLE
//		BacSubU(Rv,tmpMat2,nv,p,0);
//		
//		for (i = 0; i < nv; i++)
//			pvStar[i] = p[i];
//		for (i = nv; i < ndec; i++)
//			p[i]  = 0;
//		permutReco(p,orderPermu,ndec,1,tmpMat6);
//	}
//	else {
//		for (i = 0; i < ml; i++) {
//			for (j = 0; j < ndec; j++) 
//				tmpVec1[j] = AA[(wl[i]-1)*ndec+j];	// tmpVec1 = AA(wl(i),:);
//			permut(tmpVec1, orderPermu, ndec, 1,tmpMat6);
//			for (j = 0; j < nv; j++)
//				tmpMat1[i*nv+j] = tmpVec1[j];			// tmpMat1 = Av;
//			for (j = 0; j < nf; j++)
//				Af[i*nf+j] = tmpVec1[j+nv];
//		}
//
//		// Inverse Rv and QR factorize Av
//		uInv(Rv, nv, tmpMat2);						// tmpMat2 = invRv;
//		mat_mul(tmpMat1, ml, nv, tmpMat2, nv, tmpMat3);	// tmpMat3 = AinvR;		
//		transpose(tmpMat3, nv, ml);		
//
//		gs_m(tmpMat3, nv, ml, Yv, Lv);
//		transpose(Lv, ml, ml);
//
//		// Initial value of auxiliary vectors
//		FowSubL(Rv, gx, nv, uv, 1);			// tmpVec1 = gv;
//		matTrans_vec(Yv,uv,nv,ml,vl);
//		mat_vec(Yv,vl,nv,ml,wv);
//		vec_sub(wv,uv,nv,wv);
//		BacSubU(Rv, wv, nv, p, 0);
//		for (i = 0; i < nv; i++)
//			pvStar[i] = p[i];
//		for (i = nv; i < ndec; i++)
//			p[i]  = 0;		
//		permutReco(p,orderPermu,ndec,1,tmpMat6);		
//	}
//	printf("p is (before the first iteration. \n");show_matrix(p,ndec,1);putchar('\n');
//
/////*===========================================================================================================*/
//
//	// Iteration start!
//	// Iteration start!
//	if (flag != 0) {
//		for (iter = 0; iter < maxIter; iter++) {
//			if (iter == maxIter) {
//				printf("Maximum iteration reached!");
//				flag = 0;
//				break;
//			}
//
//			 // Decide the changes in the working set according to pStar
//			if (isZero(p, ndec, 0.000001) == 1) {			// NOTE: here the choice of 0.0001 is unsafe!
//				if (ml == 0) {
//					for (i = 0; i < nf; i++) {
//						if (wf[i] <= nbc)
//							lambda[i] = gx[i+nv];
//						else
//							lambda[i] = -gx[i+nv];
//					}
//				}
//				else {
//					printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
//					printf("vl:\n"); show_matrix(vl,ml,1); putchar('\n');
//					BacSubU(Lv,vl,ml,lambdal,1);
//					for (i = 0; i < nf; i++) {
//						tmpVec1[i] = 0;
//						for (j = 0; j < nv; j++)
//							tmpVec1[i] += H[j*ndec+i+nv]*pvStar[j];
//					}
//					//printf("K'*pvStar: \n"); show_matrix(tmpVec1,nf,1); putchar('\n');
//
//					for (i = 0; i < nf; i++)
//						lambdaf[i] = gx[i+nv] + tmpVec1[i];
//					printf("Af:\n"); show_matrix(Af,nf,ml); putchar('\n');
//					matTrans_vec(Af,lambdal,ml,nf,tmpVec1);		// tmpVec1 = Af'*lambdal
//					vec_sub(lambdaf,tmpVec1,nf,lambdaf);
//					for (i = 0; i < nf; i++)
//						if (wf[i] > nbc)
//							lambdaf[i] = -lambdaf[i];
//					for (i = 0; i < nf; i++)
//						lambda[i] = lambdaf[i];
//					for (i = 0; i < ml; i++)
//						lambda[i+nf] = lambdal[i];
//				}
//				printf("lambda:\n");show_matrix(lambda,1,nf+ml);putchar('\n');
//				minLambda = vec_min(lambda,nf+ml);
//				if ((nf == 0) && (ml == 0) || minLambda > 0) {
//					for (i = 0; i < ndec; i++)
//						xStar[i] = x[i];
//					flag = 1;
//					break;
//				}
//				else {
//					minLambdal = vec_min(lambdal,ml);
//					minLambdaf = vec_min(lambdaf,nf);
//					if ((ml == 0) || ((nf > 0 ) && (minLambdaf < minLambdal))) {					
//						// Delete a bound constraint
//
//						index = minIndex(lambda, nf+ml);
//						indexJ = wf[index] % nbc;
//						if (indexJ == 0)
//							indexJ = nbc;
//						indexJ = findIndex(orderPermu, ndec, indexJ-1);
//						wf[index] = wf[0];
//						for (i = 0; i < nf - 1; i++)
//							wf[i] = wf[i+1];
//						printf("wf:\n");show_matrixInt(wf,nf-1,1);putchar('\n');
//						if (indexJ <= nv - 1) {
//							printf("Bound constraints must be in last nf rows");
//							flag = 0;
//							break;
//						}					
//						swapVecI(orderPermu,indexJ,nv+1);
//						swapMat(H,indexJ,nv+1,ndec,tmpMat6);
//						swapVecF(gx,indexJ,nv+1,1,tmpMat6,0);
//
//						for (i = 0; i < nv; i++)
//							tmpMat2[i] = H[nv*ndec+i];							// tmpMat2 = h;
//						eta = H[nv*ndec+nv];
//
//						FowSubL(Rv,tmpMat2,nv,tmpVec1,1);						// tmpVec1 = r;
//						rau = sqrt(eta - dot_product(tmpVec1,tmpVec1,nv));
//						for (i = 0; i < nv; i++)
//							for (j = 0; j < nv; j++)
//								tmpMat3[i*(nv+1)+j] = Rv[i*nv+j];
//						for (i = 0; i < nv; i++)
//							tmpMat3[i*(nv+1)+nv] = tmpVec1[i];
//						for (i = 0; i < nv; i++)
//							tmpMat3[nv*(nv+1)+i] = 0;
//						tmpMat3[nv*(nv+1)+nv] = rau;							// tmpMat3 = Rv_bar;		
//						// Recover Av before Rv is updated
//						matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);					// tmpMat1 = Yv'*Rv;
//						mat_mul(Lv,ml,ml,tmpMat1,nv,tmpMat4);					// tmpMat4 = Av;
//
//						for (i = 0; i < (nv+1); i++) 
//							for (j = 0; j < nv+1; j++) 
//								Rv[i*(nv+1)+j] = tmpMat3[i*(nv+1)+j];																						
//
//						nv = nv + 1;
//						nf = nf - 1;
//
//						if (ml == 0) {
//							for (i = 0; i < nv; i++)
//								tmpMat2[i] = -gx[i];						// tmpMat2 = -gv;							
//							FowSubL(Rv,tmpMat2,nv,tmpMat1,1);				// tmpMat1 = MIDDLE
//							BacSubU(Rv,tmpMat1,nv,pvStar,0);
//							for (i = 0; i < nv; i++)
//								p[i] = pvStar[i];
//							for (i = nv; i < ndec; i++)
//								p[i] = 0;
//							permutReco(p,orderPermu,ndec,1,tmpMat6);
//							printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//						}
//						else {
//							for (i = 0; i < nv; i++)		
//								tmpMat1[i] = 0;
//							tmpMat1[nv-1]  = 1;									// tmpMat1 = ev1;
//							BacSubU(Rv,tmpMat1,nv,tmpMat2,0);					// tmpMat2 = q;
//
//							// Update Af
//							for (i = 0; i < ml; i++)
//								tmpMat3[i] = Af[i*(nf+1)+indexJ-nv];			// tmpMat3 = a;
//							for (i = 0; i < ml; i++)
//								Af[i*(nf+1)+indexJ-nv] = Af[i*(nf+1)];
//							for (i = 0; i < ml; i++)
//								for (j = 0; j < nf; j++)
//									Af[i*nf+j] = Af[i*(nf+1)+j+1];
//							printf("Af:\n"); show_matrix(Af,nf,ml); putchar('\n');
//							for (i = 0; i < ml; i++)
//								for (j = 0; j < nv-1; j++)
//									tmpMat1[i*nv+j] =  tmpMat4[i*(nv-1)+j];
//							for (i = 0; i < ml; i++)
//								tmpMat1[i*nv+nv-1] = tmpMat3[i];				// tmpMat1 = Av_bar;							
//							mat_vec(tmpMat1,tmpMat2,ml,nv,tmpMat3);				// tmpMat3 = v;
//
//							// Updates
//							for (i = 0; i < nv - 1; i++)
//								tmpMat2[i] = alpha * wv[i];						// tmpMat2 = alpha*wv;
//							vec_add(uv,tmpMat2,nv-1,tmpMat2);					// tmpMat2 = uv_tilde;
//							gamma = gx[nv-1];
//							mu = (gamma - dot_product(tmpVec1,tmpMat2,nv-1))/rau;				
//							uv[nv-1] = mu;	
//							for (i = 0; i < nv-1; i++)
//								uv[i] = tmpMat2[i];
//							for (i = 0; i < ml; i++)
//								tmpVec1[i] = vl[i];
//							tmpVec1[ml] = mu;									// tmpVec1 = [vl;mu];
//
//							for (i = 0; i < ml; i++)
//								for (j = 0; j < ml; j++)
//									tmpMat1[i*(ml+1)+j] = Lv[i*ml+j];
//							for (i = 0; i < ml; i++)
//								tmpMat1[i*(ml+1)+ml] = tmpMat3[i];				// tmpMat1 = LvvP;
//				
//							for (i = 0; i < nv-1; i++)
//								for (j = 0; j < ml; j++)
//									tmpMat2[i*(ml+1)+j] = Yv[i*ml+j];
//							for (i = 0; i < nv-1; i++)
//								tmpMat2[i*(ml+1)+ml] = 0;
//							for (i = 0; i < ml; i++)
//								tmpMat2[(nv-1)*(ml+1)+i] = 0;					// tmpMat2 = [Yv,zeros(nv-1,1);zeros(1,ml),1];
//							tmpMat2[(nv-1)*(ml+1)+ml] = 1;						// tmpMat2 = YvP;
//						
//							for (i = 0; i < ml; i++) {
//								myplanerot(tmpMat1[i*(ml+1)+i],tmpMat1[i*(ml+1)+ml],G);
//								colRot(tmpMat1, G, ml, ml+1, i+1, ml+1);		// Rotate LvvP
//								colRot(tmpMat2, G, nv, ml+1, i+1, ml+1);		// Rotate YvP
//								rowRot(tmpVec1, G, 1, i+1, ml+1);				// Rotate vl_barv;
//							}
//
//							for (i = 0; i < ml; i++) 
//								for (j = 0; j < ml; j++)
//									Lv[i*ml+j] = tmpMat1[i*(ml+1)+j];						
//							
//							for (i = 0; i < nv; i++)
//								for (j = 0; j < ml; j++)
//									Yv[i*ml+j] = tmpMat2[i*(ml+1)+j];
//							for (i = 0; i < nv; i++)
//								tmpMat1[i] = tmpMat2[i*(ml+1)+ml];				// tmpMat1 = z_bar;
//							for (i = 0; i < ml; i++)
//								vl[i] = tmpVec1[i];
//							ve = tmpVec1[ml];									// Here ve is the v in m-file
//							for (i = 0; i < nv; i++)
//								tmpMat1[i] = ve * tmpMat1[i];					// tmpMat1 = v*z_bar;
//							for (i = 0; i < nv - 1; i++)
//								wv[i] = (1-alpha)*wv[i];
//							wv[nv-1] = 0;
//							vec_sub(wv,tmpMat1,nv,wv);
//							BacSubU(Rv,wv,nv,pvStar,0);
//						
//							for (i = 0; i < nv; i++)
//								p[i] = pvStar[i];
//							for (i = nv; i < ndec; i++)
//								p[i] = 0;					
//							permutReco(p,orderPermu,ndec,1,tmpMat6);
//							printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//						}
//					}
//					else {
//						// Delete a general constraint
//						// Delete a general constraint
//						index = minIndex(lambdal, ml);
//						isInWl[wl[index]-1] = 0;
//						for (i = 0; i < ml-1; i++) 
//							if (i >= index)
//								wl[i] = wl[i+1];
//						printf("wl is:\n");show_matrixInt(wl,ml-1,1);putchar('\n');
//						ml = ml - 1;
//						if (ml == 0) {
//							for (i = 0; i < nv; i++)
//								tmpVec1[i] = -gx[i];				// tmpVec1 = -gv;
//							FowSubL(Rv,tmpVec1,nv,tmpMat2,1);		// tmpMat2 = MIDDLE
//							BacSubU(Rv,tmpMat2,nv,pvStar,0);
//							for (i = 0; i < nv; i++)
//								p[i] = pvStar[i];
//							for (i = nv; i < ndec; i++)
//								p[i] = 0;
//							permutReco(p,orderPermu,ndec,1,tmpMat6);
//							printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//						}
//						else {							
//							for (i = 0; i < (ml+1)*(ml+1); i++)		// Here use ml+1 because ml has been updated
//								tmpMat1[i] = Lv[i];
//							for (i = 0; i < (ml+1); i++)
//								tmpMat1[ml*(ml+1)+i] = Lv[index*(ml+1)+i];
//							for (i = index; i < ml; i++)
//								for (j = 0; j < (ml+1); j++)
//									tmpMat1[i*(ml+1)+j] = Lv[(i+1)*(ml+1)+j];	// tmpMat1 = Lv_tilde;
//
//							for (i = 0; i < nv*(ml+1); i++)
//								tmpMat2[i] = Yv[i];								// tmpMat2 = YP;
//							
//							for (i = 0; i < ml-index; i++) {					// Here, index is not same as in Matlab
//								myplanerot(tmpMat1[(index+i)*(ml+1)+(index+i)],tmpMat1[(index+i)*(ml+1)+index+i+1],G);								
//								colRot(tmpMat1, G, ml+1, ml+1, index+i+1, index+2+i);	// Rotate Lv_tilde;
//								rowRot(vl, G, 1, index+i+1, index+2+i);					// Rotate vl;
//								colRot(tmpMat2, G, nv, ml+1, index+i+1, index+2+i);		// Rotate YP;												
//							}
//							ve = vl[ml];
//							for (i = 0; i < ml; i++)
//								for (j = 0; j < ml; j++)
//									Lv[i*ml+j] = tmpMat1[i*(ml+1)+j];
//							for (i = 0; i < nv; i++)
//								for (j = 0; j < ml; j++)
//									Yv[i*ml+j] = tmpMat2[i*(ml+1)+j];	
//							for (i = 0; i < nv; i++)
//								tmpVec1[i] = tmpMat2[i*(ml+1)+ml];				// tmpVec1 = z_bar;
//							for (i = 0; i < nv; i++)
//								tmpMat1[i] = alpha * wv[i];						// tmpMat1 = alpha * wv;
//							vec_add(uv,tmpMat1,nv,uv);					
//							
//							for (i = 0; i < nv; i++)
//								wv[i] = (1-alpha)*wv[i] - ve*tmpVec1[i];
//							printf("wv is:\n");show_matrix(wv,nv,1);putchar('\n');
//							printf("vl is:\n");show_matrix(vl,ml,1);putchar('\n');
//							printf("uv is:\n");show_matrix(uv,nv,1);putchar('\n');
//							printf("Yv:\n"); show_matrix(Yv,ml,nv); putchar('\n');
//							printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
//
//							// Update Af
//							for (i = 0; i < ml; i++) {
//								if (i >= index) {
//									for (j = 0; j < nf; j++) 	
//										Af[i*nf+j] = Af[(i+1)*nf+j];
//								}
//							}
//							printf("Af:\n"); show_matrix(Af,nf,ml); putchar('\n');
//
//							//// Check code
//							//matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);
//							//mat_mul(Lv,ml,ml,tmpMat1,nv,tmpMat3);
//							//vec_sub(Av,tmpMat3,nv*ml,tmpMat4);
//							//for (i = 0; i < nv*ml; i++) {
//							//	if (tmpMat4[i] > 0.000001 || tmpMat4[i] < -0.000001) {
//							//		printf("Av or Lv update fails");
//							//		printf("Av:\n"); show_matrix(Av,nv,ml); putchar('\n');
//							//		printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
//							//		printf("Yv:\n"); show_matrix(Yv,ml,nv); putchar('\n');
//							//		printf("Rv:\n"); show_matrix(Rv,nv,nv); putchar('\n');
//							//		return 0;
//							//	}
//							//}
//
//							
//							// Compute p for the next iteration
//							BacSubU(Rv,wv,nv,pvStar,0);
//							for (i = 0; i < nv; i++)
//								p[i] = pvStar[i];
//							for (i = nv; i < ndec; i++)
//								p[i] = 0;					
//							permutReco(p,orderPermu,ndec,1,tmpMat6);
//							printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//						}
//					}
//				}
//			}
//			else {
//				// Calculate alpha
//				alpha = 1;
//				addBoundConstraint = 0;
//				addGeneralConstraint = 0;
//				for (i = 0; i < nbc; i++) {
//					if (p[i] < 0) {
//						tmpAlpha = (lx[i]-x[i])/p[i];
//						if (tmpAlpha < alpha) {
//							alpha = tmpAlpha;
//							addBoundConstraint = 1;
//							boundIndex = i+1;
//						}
//					}
//				}
//				for (i = nbc; i < 2*nbc; i++) {
//					if (p[i-nbc] > 0) {
//						tmpAlpha = (ux[i-nbc]-x[i-nbc])/p[i-nbc];
//						if (tmpAlpha < alpha) {
//							alpha = tmpAlpha;
//							addBoundConstraint = 1;
//							boundIndex = i+1;
//						}
//					}
//				}
//				printf("alpha (2nd): %lf\n",alpha);
//				if (alpha > 0.000000001) {
//					for (i = 0; i < ngc; i++) {
//						if (isInWl[i] == 0) {
//							ap = 0.0;
//							for (j = 0; j < ndec; j++) {
//								ap += AA[i*ndec+j]*p[j];
//							}	
//							if (ap < 0) {
//								tmp = 0.0;
//								for (j = 0; j < ndec; j++)
//									tmp += AA[i*ndec+j]*x[j];
//								tmp = lg[i] - tmp;
//								if (ap > -0.000001 && tmp > -0.00001 && tmp < 0.00001)		// Need note after
//									continue;
//								tmpAlpha = tmp/ap;
//								if (tmpAlpha < alpha + 0.0000001) {
//									alpha = tmpAlpha;
//									addGeneralConstraint = 1;
//									addBoundConstraint = 0;
//									generalIndex = i+1;
//								}
//								if (alpha < 0.000000001)
//									break;
//							}
//						}
//					}
//				}
//
//				if (alpha > 1)
//					alpha = 1;
//				if (alpha < 0)
//					alpha = 0;
//				for (i = 0; i < ndec; i++)
//					x[i] = x[i] + alpha*p[i];
//				printf("alpha: %lf\n",alpha);
//			
//				// Compute and update gx
//				mat_vec(H_ori,x,ndec,ndec,gx);
//				vec_add(c_ori,gx,ndec,gx);
//				permut(gx,orderPermu,ndec,1,tmpMat6);
//			
//				printf("x is:\n");show_matrix(x,ndec,1);putchar('\n');
//				printf("gx is:\n");show_matrix(gx,ndec,1);putchar('\n');
//
//				if (alpha < 1) {
//					if ((addBoundConstraint == 1) && (addGeneralConstraint == 0)) {					
//						// Adding a bound constraint
//						for (i = nf; i > 0; i--) 
//							wf[i] = wf[i-1];
//						wf[0] = boundIndex;
//						printf("wf is:\n");show_matrixInt(wf,nf+1,1);putchar('\n');
//						indexJ = boundIndex % nbc;
//						if (indexJ == 0)
//							indexJ = nbc;
//						indexJ = findIndex(orderPermu, ndec, indexJ-1);
//						// Here indexJ should be from 1 to n (not 0 to n-1), for comparison with Matlab
//						for (i = 0; i < nv*nv; i++)
//							tmpMat1[i] = Rv[i];			
//
//						swapVecF(tmpMat1,indexJ,nv,nv,tmpMat6,1);		// tmpMat1 = tmpS;
//
//						for (i = 0; i < nv * nv; i++)
//							tmpMat4[i] = 0;
//						for (i = 0; i < nv; i++)
//							tmpMat4[i*nv+i] = 1;				// tmpMat4 = Q;	
//						for (i = 0; i < (nv-indexJ-1); i++) {
//							myplanerot(tmpMat1[(nv-1)*nv+indexJ-1],tmpMat1[(nv-(i+1)-1)*nv+indexJ-1],G);										
//							rowRot(tmpMat1,G,nv,nv,nv-(i+1));
//							rowRot(tmpMat4,G,nv,nv,nv-(i+1));
//						}					
//						for (i = 0; i < (nv - indexJ); i++) {
//							myplanerot(tmpMat1[((i+1)+indexJ-2)*nv+((i+1)+indexJ-2)],tmpMat1[(nv-1)*nv+((i+1)+indexJ-2)],G);
//							rowRot(tmpMat1,G,nv,(i+1)+indexJ-1,nv);
//							rowRot(tmpMat4,G,nv,(i+1)+indexJ-1,nv);
//						}		
//
//						for (i = 0; i < nv-1; i++)
//							for (j = 0; j < nv-1; j++)
//								Rv[i*(nv-1)+j] = tmpMat1[i*nv+j];		// tmpMat1 = Rv_hat;
//						swapVecI(orderPermu,indexJ,nv);
//						swapMat(H,indexJ,nv,ndec,tmpMat6);
//						swapVecF(gx,indexJ,nv,1,tmpMat6,0);				
//					
//						nv = nv - 1;
//						nf = nf + 1;
//
//						if (ml == 0) {
//							for (i = 0; i < nv; i++)
//								tmpVec1[i] = -gx[i];				// tmpVec1 = -gv;
//
//							FowSubL(Rv,tmpVec1,nv,tmpMat2,1);
//
//							BacSubU(Rv,tmpMat2,nv,pvStar,0);						
//							for (i = 0; i < nv; i++)
//								p[i] = pvStar[i];
//							for (i = nv; i < ndec; i++)
//								p[i] = 0;
//							permutReco(p,orderPermu,ndec,1,tmpMat6);
//							printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//						}
//						else {				
//							mat_mul(tmpMat4,nv+1,nv+1,Yv,ml,tmpMat3);			// tmpMat3 = QYv(Y_tilde);
//							for (i = 0; i < ml; i++)								// QYv: (nv+1)*(ml)
//								tmpMat2[i] = tmpMat3[nv*ml+i];					// tmpMat2 = y_tilde;			
//							tau = 1/sqrt(1-dot_product(tmpMat2,tmpMat2,ml));
//							mat_vec(tmpMat3,tmpMat2,nv,ml,tmpVec1);				// tmpVec1 = Y_tilde*y_tilde;
//							for (i = 0; i < nv; i++)
//								tmpVec1[i] = -tau*tmpVec1[i];				
//							tmpVec1[nv] = 1/tau;								// tmpVec1 = z;				
//							if (ml > nv) {
//								printf("Unsolvable!\n");
//								flag = 0;
//								break;
//							}
//							for (i = 0; i < (nv+1); i++)
//								for (j = 0; j < ml; j++)
//									tmpMat5[i*(ml+1)+j] = tmpMat3[i*ml+j];	
//							for (i = 0; i < nv+1; i++)
//								tmpMat5[i*(ml+1)+ml] = tmpVec1[i];				// QYzTrans: (ml+1)*(nv+1)
//							transpose(tmpMat5,ml+1,nv+1);						// tmpMat5 = QYzTrans;										
//
//							// Update Af
//							for (i = 0; i < ml; i++)
//								tmpVec2[i] = AA[(wl[i]-1)*ndec+orderPermu[nv]];
//							
//							for (i = 0; i < (nf-1)*(ml); i++)
//								tmpMat1[i] = Af[i];								// tmpMat1 = Af;
//							for (i = 0; i < ml; i++)
//								Af[i*nf] = tmpVec2[i];
//							for (i = 0; i < ml; i++)
//								for (j = 0; j < nf-1; j++)
//									Af[i*nf+j+1] = tmpMat1[i*(nf-1)+j];
//							printf("Af:\n"); show_matrix(Af,nf,ml); putchar('\n');
//							for (i = 0; i < (ml+1)*(ml+1); i++)
//								P[i] = 0;
//							for (i = 0; i < ml+1; i++)
//								P[i*(ml+1)+i] = 1;
//							for (i = 0; i < ml; i++) {
//								myplanerot(tmpMat5[ml*(nv+1)+nv],tmpMat5[(ml-(i+1))*(nv+1)+nv],G);
//								rowRot(tmpMat5, G, nv+1,ml+1,ml+1-(i+1));
//								rowRot(P, G, ml+1,ml+1,ml+1-(i+1));
//							}
//							transpose(P,ml+1,ml+1);
//							for (i = 0; i < nv+1; i++)
//								for (j = 0; j < ml; j++)
//									tmpMat1[i*(ml+1)+j] = tmpMat3[i*ml+j];			
//							for (i = 0; i < nv+1; i++)
//								tmpMat1[i*(ml+1)+ml] = tmpVec1[i];				// tmpMat1 = [QYv,z];
//							mat_mul(tmpMat1,nv+1,ml+1,P,ml+1,tmpMat5);			// tmpMat5 = QYP;
//							vec_mat(tmpMat4,tmpVec1,nv+1,nv+1,tmpVec2);			// tmpVec2 = z;
//							for (i = 0; i < nv; i++)
//								for (j = 0; j < ml; j++)
//									Yv[i*ml+j] = tmpMat5[i*(ml+1)+j];
//							for (i = 0; i < ml; i++)
//								for (j = 0; j < ml; j++)
//									tmpMat1[i*(ml+1)+j] = Lv[i*ml+j];
//							for (i = 0; i < ml; i++)
//								tmpMat1[i*(ml+1)+ml] = 0;						// tmpMat1 = [Lv,zeros(ml,1)]
//							mat_mul(tmpMat1,ml,ml+1,P,ml+1,tmpMat2);			// tmpMat2 = LvP;
//							for (i = 0; i < ml; i++)
//								for (j = 0; j < ml; j++)
//									Lv[i*ml+j] = tmpMat2[i*(ml+1)+j];
//							for (i = 0; i < nv+1; i++)
//								tmpVec1[i] = uv[i] + alpha * wv[i];				// tmpVec1 = uv+alpha*wv;
//							mat_vec(tmpMat4,tmpVec1,nv+1,nv+1,tmpMat1);			// tmpMat1 = uv_bar;
//							ve = (1-alpha)*dot_product(tmpVec2,uv,nv+1);
//							for (i = 0; i < ml; i++)
//								tmpVec1[i] = vl[i];
//							tmpVec1[ml] = ve;									// tmpVec1 = [vl;v];
//							vec_mat(P,tmpVec1,ml+1,ml+1,vl);
//							for (i = 0; i < nv; i++)
//								uv[i] = tmpMat1[i];
//							for (i = 0; i < nv+1; i++)
//								tmpVec1[i] = (1-alpha)*wv[i]+ve*tmpVec2[i];		// tmpVec1 = (1-alpha)*wv+v*z;
//							mat_vec(tmpMat4,tmpVec1,nv+1,nv+1,wv);
//
//							// Compute p for the next iteration
//							BacSubU(Rv,wv,nv,pvStar,0);
//							for (i = 0; i < nv; i++)
//								p[i] = pvStar[i];
//							for (i = nv; i < ndec; i++)
//								p[i] = 0;					
//							permutReco(p,orderPermu,ndec,1,tmpMat6);
//							printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//						}
//					}
//					else if ((addBoundConstraint == 0) && (addGeneralConstraint ==1)) {
//						// Adding a general constraint
//						isInWl[generalIndex-1] = 1;
//						wl[ml] = generalIndex;
//						printf("wl is(add):\n"); show_matrixInt(wl,ml+1,1); putchar('\n');
//						ml = ml + 1;
//					
//						for (i = 0; i < ndec; i++)
//							tmpVec1[i] = AA[(generalIndex-1)*ndec+i];
//						permut(tmpVec1,orderPermu,ndec,1,tmpMat6);			// tmpVec1 = a;
//
//
//						if (ml == 1) {
//							uInv(Rv, nv, tmpMat2);							// tmpMat2 = inv(Rv);
//							for (i = 0; i < nv; i++)
//								tmpMat1[i] = tmpVec1[i];					// tmpMat1 = Av;
//							for (i = nv; i < ndec; i++)
//								Af[i-nv] = tmpVec1[i];
//
//							mat_mul(tmpMat1,ml,nv,tmpMat2,nv,tmpMat3);			// tmpMat3 = AinvR';
//							printf("AinvR':\n"); show_matrix(tmpMat3,nv,ml); putchar('\n');
//
//							gs_m(tmpMat3, nv, ml, Yv, Lv);
//							transpose(Lv, ml, ml);
//
//							printf("Yv:\n"); show_matrix(Yv,ml,nv); putchar('\n');
//							printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
//							mat_mulTrans(Lv,ml,ml,Yv,nv,tmpMat2);
//							printf("AinvR(recover)':\n"); show_matrix(tmpMat2,nv,ml); putchar('\n');
//							
//							FowSubL(Rv, gx, nv, uv, 1);	
//							printf("uv:\n"); show_matrix(uv,nv,1); putchar('\n');
//							matTrans_vec(Yv,uv,nv,ml,vl);
//							mat_vec(Yv,vl,nv,ml,wv);
//							vec_sub(wv,uv,nv,wv);								
//							printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
//							printf("vl:\n"); show_matrix(vl,ml,1); putchar('\n');
//							printf("Yv:\n"); show_matrix(Yv,ml,nv); putchar('\n');
//						}
//						else {
//							FowSubL(Rv, tmpVec1, nv, tmpVec2, 1);			// tmpVec2 = q;
//							
//							mat_mulTrans(Yv,nv,ml-1,Yv,nv,tmpMat3);			// tmpMat3 = Yv*Yv';
//
//							for (i = 0; i < nv*nv; i++)
//								tmpMat3[i] = -tmpMat3[i];
//							for (i = 0; i < nv; i++)
//								tmpMat3[i*nv+i] = tmpMat3[i*nv+i] + 1;		// tmpMat3 = (eye(nv,nv)-Yv*Yv');
//							mat_vec(tmpMat3,tmpVec2,nv,nv,tmpMat4);			// tmpMat4 = z_unnomalized;
//							tau = sqrt(1/(dot_product(tmpMat4,tmpMat4,nv)));
//							for (i = 0; i < nv; i++)
//								tmpMat5[i] = tau*tmpMat4[i];				// tmpMat5 = z;
//							for (i = 0; i < nv; i++)
//								for (j = 0; j < ml-1; j++)
//									tmpMat1[i*ml+j] = Yv[i*(ml-1)+j];
//							for (i = 0; i < nv; i++)
//								tmpMat1[i*ml+(ml-1)] = tmpMat5[i];			// tmpMat1 = Yv_bar;
//							
//							matTrans_vec(Yv,tmpVec2,nv,ml-1,tmpMat3);		// tmpMat3 = l;
//
//							gamma = dot_product(tmpMat5,tmpVec2,nv);
//							for (i = 0; i < ml-1; i++)
//								for (j = 0; j < ml-1; j++)
//									tmpMat2[i*ml+j] = Lv[i*(ml-1)+j];
//							for (i = 0; i < ml-1; i++)
//								tmpMat2[i*ml+ml-1] = 0;
//							for (i = 0; i < ml-1; i++)
//								tmpMat2[(ml-1)*ml+i] = tmpMat3[i];
//							tmpMat2[(ml-1)*ml+ml-1] = gamma;				// tmpMat2 = Lv_bar;		
//							for (i = 0; i < nv; i++)
//								tmpVec2[i] = uv[i] + alpha*wv[i];			// tmpVec2 = uv_bar;
//							ve = (1-alpha)*dot_product(tmpMat5,uv,nv);
//							printf("ve:%lf\n",ve);
//							vl[ml-1] = ve;
//							for (i = 0; i < nv; i++)
//								wv[i] = (1-alpha)*wv[i]+ve*tmpMat5[i];
//
//							// Update Af
//							for (i = 0; i < nf; i++)
//								Af[(ml-1)*nf+i] = tmpVec1[i+nv];
//							printf("Af:\n"); show_matrix(Af,nf,ml); putchar('\n');
//							for (i = 0; i < nv*ml; i++)
//								Yv[i] = tmpMat1[i];
//							for (i = 0; i < ml*ml; i++)
//								Lv[i] = tmpMat2[i];
//							for (i = 0; i < nv; i++)
//								uv[i] = tmpVec2[i];
//
//							printf("Yv:\n"); show_matrix(Yv,ml,nv); putchar('\n');
//							printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
//							printf("vl:\n"); show_matrix(vl,ml,1); putchar('\n');
//
//							if (needCheckFlag == 1) {	// Imprecision may happen
//								tmpMat3[ml-1] = gamma;
//								matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);
//								vec_mat(tmpMat1,tmpMat3,ml,nv,tmpMat2);
//								maxDiff = 0;
//								for (i = 0; i < nv; i++) {
//									diff = tmpVec1[i] - tmpMat2[i];
//									if ( diff > maxDiff)
//										maxDiff = diff;
//									else if (-diff > maxDiff)
//										maxDiff = -diff;
//								}
//								if (maxDiff > 0.0005) {		// Threshold need to be set
//									// Update Error, initialize factorization
//									// Get Av
//									for (i = 0; i < ml; i++) {
//										for (j = 0; j < ndec; j++) 
//											tmpVec1[j] = AA[(wl[i]-1)*ndec+j];		// tmpVec1 = AA(wl(i),:);
//										permut(tmpVec1, orderPermu, ndec, 1,tmpMat6);
//										for (j = 0; j < nv; j++)
//											tmpMat1[i*nv+j] = tmpVec1[j];			// tmpMat1 = Av;
//									}
//									// Inverse Rv and QR factorize Av
//									uInv(Rv, nv, tmpMat2);							// tmpMat2 = invRv;
//									mat_mul(tmpMat1, ml, nv, tmpMat2, nv, tmpMat3);	// tmpMat3 = AinvR;		
//									transpose(tmpMat3, nv, ml);		
//									gs_m(tmpMat3, nv, ml, Yv, Lv);
//									transpose(Lv, ml, ml);
//									// Initial value of auxiliary vectors
//									for (i = 0; i < nv; i++)
//										tmpVec1[i] = gx[i];
//									FowSubL(tmpMat1, tmpVec1, nv, uv, 0);			// tmpVec1 = gv;
//									matTrans_vec(Yv,uv,nv,ml,vl);
//									mat_vec(Yv,vl,nv,ml,wv);
//									vec_sub(wv,uv,nv,wv);
//								}
//							}
//
//						}										
//						if (ml == ndec) {
//							for (i = 0; i < ndec; i++)
//								p[i] = 0;
//							needCheckFlag = 1;
//						}
//						else {
//							BacSubU(Rv, wv, nv, p, 0);
//						}
//						for (i = 0; i < nv; i++)
//							pvStar[i] = p[i];
//						for (i = nv; i < ndec; i++)
//							p[i]  = 0;		
//						permutReco(p,orderPermu,ndec,1,tmpMat6);	
//						printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//					}
//					else {
//						printf("Add constraint error!\n");
//						flag = 0;
//						break;
//					}
//				}
//				else {		// If alpha == 1, p is solved again without changing working set
//					if (ml == 0) {
//						for (i = 0; i < nv; i++)
//							tmpVec1[i] = -gx[i];				// tmpVec1 = -gv;
//						FowSubL(Rv,tmpVec1,nv,tmpVec2,1);		// tmpVec2 = MIDDLE
//						BacSubU(Rv,tmpVec2,nv,pvStar,0);
//						for (i = 0; i < nv; i++)
//							p[i] = pvStar[i];
//						for (i = nv; i < ndec; i++)
//							p[i] = 0;
//						permutReco(p,orderPermu,ndec,1,tmpMat6);
//						printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//					}
//					else {
//						FowSubL(Rv,gx,nv,uv,1);
//						matTrans_vec(Yv,uv,nv,ml,vl);
//						mat_vec(Yv,vl,nv,ml,wv);
//						for (i = 0; i < nv; i++)
//							wv[i] = wv[i] - uv[i];
//						BacSubU(Rv, wv, nv, p, 0);
//						for (i = 0; i < nv; i++)
//							pvStar[i] = p[i];
//						for (i = nv; i < ndec; i++)
//							p[i]  = 0;		
//						permutReco(p,orderPermu,ndec,1,tmpMat6);	
//						printf("p is:\n");show_matrix(p,ndec,1);putchar('\n');
//					}
//				}
//			}
//		}
//	}
//	return flag;
//}