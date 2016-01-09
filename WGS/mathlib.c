/*
 * mathlib.c
 *
 *  Created on: 2015-9-3
 *      Author: Yi
 *	Mathematical calculations for wgsQP
 *
 */

#define Print mexPrintf		// For Matlab debug
//#define Print printf		// For Visual Studio debug

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Print the matrix to the consolo. 
void show_matrix(float *m, int w, int h) {
	int i, j;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++)
			Print("%.4f ", m[i * w + j]);
		Print("\n");
	}
}

// Print the matrix to the consolo. 
void show_matrixInt(int *m, int w, int h) {
	int i, j;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++)
			Print("%d ", m[i * w + j]);
		Print("\n");
	}
}

// Find the minimum one of a vector.
float vec_min(float *x, int n) {


	float min;
	int i;
	min = x[0];
	for(i=1;i<n;i++) {
		if(x[i]<min)
			min = x[i];
	}
	return min;
}

// Return the index of the minimum element
int minIndex(float *x, int n) {

	float min;
	int i, index;
	min = x[0];
	index = 0;
	for(i=1;i<n;i++) {
		if(x[i]<min) {
			min = x[i];
			index = i;
		}
	}
	return index;
}

// Find the index of certain element in the vector
// Note: the index returned is from 1 to n (not 0 to n-1)
int findIndex(int *x, int n, int tar) {
	int i;
	for (i = 0; i < n; i++) {
		if (x[i] == tar) 
			return i+1;
	}
	printf("Target not found in the vector!\n");
	return -1;
}

// Vector addation
// c = a + b
void vec_add(float *a, float *b, int n,float *c) {
	int i;
	for(i=0;i<n;i++)	
		c[i]=a[i]+b[i];
}

// Vector subtraction
// c = a - b
void vec_sub(float *a, float *b, int n,float *c) {
	int i;
	for(i=0;i<n;i++)
		c[i]=a[i]-b[i];
}

// Add two matrices.
// a + b = sum
void mat_add(float *a, float *b, int row, int column, float *sum) {
	int i;
	for(i=0;i<row*column;i++)
		sum[i] = a[i]+b[i];
}

// Do the multiplication 
// A * x = b;
void mat_vec(float *A, float *x, int row, int col, float *b) {
	int i,j;
	for(i=0;i<row;i++) {
		b[i]=0;
		for(j=0;j<col;j++)
			b[i] += A[i*col+j]*x[j];				//Attention!2014.5.5
	}
}

// Transpose A, and do the multiplication 
// A' * x = b; 
// Note, the row and col is before 
void matTrans_vec(float *A, float *x, int row, int col, float *b) {
	int i,j;
	for(i=0; i<col; i++) {
		b[i]=0;
		for(j=0; j<row; j++)
			b[i] += A[j*col+i]*x[j];				//Attention!2014.5.5
	}
}

//Do the multiplication x'*A = b;
void vec_mat(float *A, float *x, int row, int col, float *b)
{
	int i,j;
	for(j=0;j<col;j++) {
		b[j]=0;
		for(i=0;i<row;i++)
			b[j]+=A[i*col+j]*x[i];				//Attention!2014.5.5
	}
}

// Do the dot product for two array. n is the number of elements
// a' * b
float dot_product(float *a, float *b, int n) {
	float sum = 0;
	int i;
	for (i = 0; i < n; i++) {
		sum += a[i] * b[i];
	}
	return sum;
}


// Swap a vector/matrix v at two rows p1 and p2
// p1 and p2 is from 1 to n (not 0 to n-1)
void swapVecF(float *v, int p1, int p2, int col, float *tmp, int flag) {	

	// flag == 0 means to swap rows
	// flag == 1 means to swap columns (now col is actually rows)
	int i;
	if (flag == 0) {
		for (i = 0; i < col; i++)
			tmp[i] = v[(p1-1)*col+i];
		for (i = 0; i < col; i++)
			v[(p1-1)*col+i] = v[(p2-1)*col+i];
		for (i = 0; i < col; i++)
			v[(p2-1)*col+i] = tmp[i];
	}
	else if (flag == 1) {
		for (i = 0; i < col; i++)
			tmp[i] = v[i*col+(p1-1)];
		for (i = 0; i < col; i++)
			v[i*col+(p1-1)] = v[i*col+(p2-1)];
		for (i = 0; i < col; i++)
			v[i*col+(p2-1)] = tmp[i];
	}
	else
		printf("Wrong flags!\n");
}

// Swap a vector(matrix not included) v at two positions p1 and p2
// p1 and p2 is from 1 to n (not 0 to n-1)
void swapVecI(int *v, int p1, int p2) {
	int tmp = v[p1-1];
	v[p1-1] = v[p2-1];
	v[p2-1] = tmp;
}

// Swap a positive definite matrix m at two positions p1 and p2
// Achieve the function : H = Pi'*H*Pi; here Pi is the permute function
// p1 and p2 is from 1 to n (not 0 to n-1)
void swapMat(float *m, int p1, int p2, int n, float *tmp) {
	
	int i;

	for (i = 0; i < n; i++) 
		tmp[i] = m[(p1-1)*n+i];
	for (i = 0; i < n; i++) 
		m[(p1-1)*n+i] = m[(p2-1)*n+i];
	for (i = 0; i < n; i++) 
		m[(p2-1)*n+i] = tmp[i];

	for (i = 0; i < n; i++) 
		tmp[i] = m[i*n+(p1-1)];
	for (i = 0; i < n; i++) 
		m[i*n+(p1-1)] = m[i*n+(p2-1)];
	for (i = 0; i < n; i++) 
		m[i*n+(p2-1)] = tmp[i];
}

// Permute a matrix/vector using the permute matrix p (0 ~ n-1)
// Note that if the input is a matrix, the row order is permuted
// the order in p is from 0 to m-1
void permut(float *oriMat, int *p, int m, int n, float *mat) {

	int i,j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			mat[i*n+j] = oriMat[p[i]*n+j];
		}		
	}	

	for (i = 0; i < m*n; i++)
		oriMat[i] = mat[i];
}

// Recover a permuted matrix/vector using the permute matrix p (0 ~ n-1)
// Note that if the input is a matrix, the row order is recovered
void permutReco(float *mat, int *p,  int m, int n, float *oriMat) {

	int i, j;

	for (i = 0; i < m; i++) {
		for (j=0; j < n; j++) {
			oriMat[p[i]*n+j] = mat[i*n+j];
		}
	}
	for (i = 0; i < m*n; i++)
		mat[i] = oriMat[i];
}


// A Cholesky Factorization routine from the book Numerical Recipes in C
// Maybe codes from NRC are more robust?
int chol_NRC(float *A, int n,float *p)
{
	int i,j,k;
	int flag = 1;

	float sum;	
	for (i=1;i<=n;i++) {
		for (j=i;j<=n;j++) {
			for (sum=A[(i-1)*n+(j-1)],k=i-1;k>=1;k--) {
				sum -= A[(i-1)*n+(k-1)]*A[(j-1)*n+(k-1)];
			}
			if (i == j) {
				if (sum <= 0.0) {
					printf("Factorization Failed.\n");
					flag = 0;
				}
				p[i-1]=sqrt(sum);
			}
			else A[(j-1)*n+(i-1)]=sum/p[i-1];
		}
	}
	return flag;
}

// Transpose the matrix m and store the matrix in w.
void transpose(float *m, int w, int h)
{
	int start, next, i;

	float tmp;

	for (start = 0; start <= w * h - 1; start++) {
		next = start;
		i = 0;
		do {	i++;
			next = (next % h) * w + next / h;
		} while (next > start);
		if (next < start || i == 1) continue;

		tmp = m[next = start];
		do {
			i = (next % h) * w + next / h;
			m[next] = (i == start) ? tmp : m[i];
			next = i;
		} while (next > start);
	}
}

// Solve a linear system with lower-triangular matrix using forward substitution
// L * y = b;
void FowSubL(float *L, float *b, int n, float *y, int flag) {
	
	// flag == 0, means L is naturally an lower-triangular matrix
	// flag == 1, means L will be lower-triangular after transpose

	float temp = 0;
	int i, j;

	//Foward solve Ly = b;
	if (flag == 0) {
		y[0] = b[0]/L[0];
		for(i=1;i<n;i++) {
			for(j=0;j<i;j++) {
				temp += L[i*n+j]*y[j];
			}
			y[i] = b[i] - temp;
			y[i] = y[i]/L[i*n+i];
			temp = 0;
		}
	}
	else if (flag == 1) {
		y[0] = b[0]/L[0];
		for(i=1;i<n;i++) {
			for(j=0;j<i;j++) {
				temp += L[j*n+i]*y[j];
			}
			y[i] = b[i] - temp;
			y[i] = y[i]/L[i*n+i];
			temp = 0;
		}
	}
	else
		printf("Wrong flag!\n");

}

// Solve a linear system with upper-triangular matrix using backward substitution
// U * x = y;
void BacSubU(float *U, float *y, int n, float *x, int flag) {
	
	// flag == 0, means U is naturally an upper-triangular matrix
	// flag == 1, means U will be upper-triangular after transpose

	float temp = 0;
	int i, j;

	//Backward solve Ux = y
	if (flag == 0) {		
		x[n-1] = y[n-1]/U[n*n-1];
		for(i=n-2;i>=0;i--) {
			for(j=i+1;j<n;j++) {
				temp += U[i*n+j]*x[j];
			}
			x[i] = y[i] - temp;
			x[i] = x[i]/U[i*n+i];
			temp = 0;
		} 
	}
	else if (flag == 1) {
		x[n-1] = y[n-1]/U[n*n-1];
		for(i=n-2;i>=0;i--) {
			for(j=i+1;j<n;j++) {
				temp += U[j*n+i]*x[j];
			}
			x[i] = y[i] - temp;
			x[i] = x[i]/U[i*n+i];
			temp = 0;
		} 
	}
	else 
		printf("Wrong flag!\n");


}


// Inverse an upper-triangular matrix using backward substitution
// invR = inv(R), where R is an upper-triangular 
void uInv(float *R, int n, float *invR) {

	int i, j, k;

	float tmp;

	for (i = 0; i < n; i++)
		for (j = 0; j < i; j++)
			invR[i*n+j] = 0;

	for (i = 0; i < n; i++) 
		invR[i*n+i] = 1/R[i*n+i];
	for (j = n; j > 0; j--) {
		for (i = j-1; i > 0; i--) {
			tmp = 0;
			for (k = 1; k <= j-i; k++) 
				tmp += R[(i-1)*n+(i-1+k)]*invR[(i-1+k)*n+j-1];
			invR[(i-1)*n+j-1]= -1/R[(i-1)*n+i-1]*tmp;
		}
	}
}


// Matrix multiplication. 
// x1 * x2 = y
void mat_mul(float *x1, int r1, int c1, float *x2, int c2, float *y) {
	int i,j,k;	
	for(i=1;i<=r1;i++) {
		for(j=1;j<=c2;j++) {
			y[(i-1)*c2+(j-1)]=0;
			for(k=1;k<=c1;k++) 
				y[(i-1)*c2+(j-1)]+=x1[(i-1)*c1+(k-1)]*x2[(k-1)*c2+(j-1)];			
		}
	}
}

// Transpose the matrix and do the multiplication
// x1' * x2 = y, Note: the r1 and c1 and rows and columns before transpose
void matTrans_mul(float *x1, int r1, int c1, float *x2, int c2, float *y) {
	int i, j, k;
	for (i = 0; i < c1; i++) {
		for (j = 0; j < c2; j++) {
			y[i*c2+j] = 0;
			for (k = 0; k < r1; k++)
				y[i*c2+j] += x1[k*c1+i]*x2[k*c2+j];
		}
	}
}

// Transpose the matrix and do the multiplication
// x1 * x2' = y, Note: the r1 and c1 and rows and columns before transpose
void mat_mulTrans(float *x1, int r1, int c1, float *x2, int r2, float *y) {
	int i,j,k;	
	for(i = 0; i < r1; i++) {
		for(j = 0; j < r2; j++) {
			y[i*r2 + j] = 0;
			for( k = 0; k < c1; k++) 
				y[i*r2 + j] += x1[i*c1 + k] * x2[j*c1 + k];			
		}
	}
}

// Compute the Euclid norm of a vector
float norm(float *v, int n) {
	int i;
	float en = 0.0;
	for (i = 0; i < n; i++)
		en += v[i]*v[i];
	en = sqrt(en);
	return en;
}

// Check whether a vector is zero or not
// if v < epsilon, then v is zero 
int isZero(float *v, int n, float epsilon) {
	int i;

	for (i = 0; i < n; i++) {
		if (v[i] > epsilon || v[i] < -epsilon)
			return 0;
	}
	return 1;
}

// Do the Givens rotation for a two-element vector
// G is a 2*2 matrix
void myplanerot(float x1, float x2, float *G) {


	float r;

	if (x2 < 0.0000001 && x2 > -0.0000001) {
		G[0] = 1;
		G[1] = 0;
		G[2] = 0;
		G[3] = 1;
	}
	else {
		r = sqrt(x1 * x1 + x2 * x2);
		G[0] = x1/r;
		G[1] = x2/r;
		G[2] = -x2/r;
		G[3] = x1/r;
	}
}

// Form the rotation matrix from the Givens rotations
// G is Givens matrix, i j is the row/column need to be rotated, m is the size
// i and j is from 1 to m
void formRot(float *G, int i, int j, int m, float *P) {
	
	int k1, k2;

	for (k1 = 0; k1 < m*m; k1 ++)
		P[k1] = 0;
	for (k1 = 0; k1 < m; k1++)
		P[k1*m+k1] =1;

	P[(i-1)*m+(i-1)] = G[0];
	P[(j-1)*m+(j-1)] = G[3];
	P[(i-1)*m+(j-1)] = G[1];
	P[(j-1)*m+(i-1)] = G[2];

}

// Rotation of two rows to produce zero on the below row
// Note, here m is the column of the mat
// i and j is from 1 to m
void rowRot(float *mat, float *G, int m, int i, int j) {

	int k;
	
	float tmp1, tmp2;	
	for (k = 0; k < m; k++) {
		tmp1 = mat[(i-1)*m+k];
		tmp2 = mat[(j-1)*m+k];
		mat[(i-1)*m+k] = G[0]*tmp1+G[1]*tmp2;
		mat[(j-1)*m+k] = G[2]*tmp1+G[3]*tmp2;
	}	
}

// Rotation of two columns to produce zero on the right column
// Note, here m is the number of rows of the mat
// n is the number of columns of mat
void colRot(float *mat, float *G, int m, int n, int i, int j) {

	int k;
	float tmp1, tmp2;
	for (k = 0; k < m; k++) {
		tmp1 = mat[k*n+i-1];
		tmp2 = mat[k*n+j-1];
		mat[k*n+i-1] = G[0]*tmp1+G[1]*tmp2;
		mat[k*n+j-1] = G[2]*tmp1+G[3]*tmp2;
	}
}
// QR decomposition using Givens rotation
// A = Q * R;
// size(A) =[row,col]; size(Q) = [row, row]; size(R) = [row, col]; size(G) = [2,2];
// Note: the elements in A will be changed
void qr(float *A, int row, int col, float *Q, float *G) {

	int i,j, colTimes;

	for (i = 0; i < row*row; i++)
		Q[i] = 0;
	for (i = 0; i < row; i++)
		Q[i*row+i] = 1;

	if (row > col)
		colTimes = col;
	else
		colTimes = row-1;

	for (i = 0; i < colTimes; i++) {
		for (j = 0; j < row-1-i; j++) {			
			myplanerot(A[(row-j-2)*col+i],A[(row-j-1)*col+i],G);
			//printf("%f and %f\n",A[(row-j-2)*col+i],A[(row-j-1)*col+i]);
			rowRot(A,G,col,(row-j-1),(row-j));
			rowRot(Q,G,row,(row-j-1),(row-j));
// 			printf("G:\n");show_matrix(G,2,2);putchar('\n');
// 			printf("Q:\n");show_matrix(Q,row,row);putchar('\n');
// 			printf("R:\n");show_matrix(A,col,row);putchar('\n');			
		}
	}
	transpose(Q,row,row);
}


// Modified Gram-Schmidt QR factorization.     
// Reference:
//       N. J. Higham, Accuracy and Stability of Numerical Algorithms,
//       Second edition, Society for Industrial and Applied Mathematics,
//       Philadelphia, PA, 2002; sec 19.8. Gram-Schmidt QR factorization.
// [m, n] = size(A); [m, n] = size(Q);	[n, n] = size(R);
int gs_m(float *A, int m, int n, float *Q, float *R) {

	int i, j, k, l;
    int flag = 1;
	float en;

	for (i = 0; i < m*n; i++)
		Q[i] = 0;
	for (i = 0; i < n*n; i++)
		R[i] = 0;

	for (i = 0; i < n; i++) {
		en = 0.0;
		for (j = 0; j < m; j++)
			en += A[j*n+i]*A[j*n+i];
		en = sqrt(en);
		R[i*n+i] = en;		
        
//         if (en < 0.000001) {
//             printf("en: %.10f\n",en);
//             flag = 0;
//             for (j = 0; j < m; j++) {
//                 if (A[j*n+i] > 0.00001)
//                     flag = 1;
//                 printf("A[j*n+i]: %.10f\n",A[j*n+i]);
//             }
//             if (flag == 0)
//                 return flag;
//         }
        
        if (en < 0.0000001) {
            en = en * 10000000000000000;
            for (j = 0; j < m; j++) {
                Q[j*n+i] = A[j*n+i]*10000000000000000/en;
            }
        }
        else {
            for (j = 0; j < m; j++) {
                Q[j*n+i] = A[j*n+i]/en;
            }
        }
           

	

		for (j = i+1; j < n; j++) {
			en = 0.0;
			for (k = 0; k < m; k++)
				en += Q[k*n+i]*A[k*n+j];
			R[i*n+j] = en;
		}

		for (j = 0; j < m; j++) {
			for (k = i+1; k < n; k++) {
				A[j*n+k] = A[j*n+k] - Q[j*n+i]*R[i*n+k];
			}
		}

	}
    
    return 1;

}

/*  The main routine */
int wgsQP(float *H_ori, float *c_ori, float *AA, float *lx, float *ux, float *lg, 
	int *wf, int *wl, int nf, int ml, float *x, int ndec, int nbc, int ngc, 
	int *orderPermu, float *H, float *c, float *Af, float *Lv, float *Yv, 
	float *Rv, float *pvStar, float *p, float *gx, int *isInWl, float *uv, float *vl, float *wv,
	float *lambdal, float *lambdaf, float *lambda, float *P, float *G,float *tmpVec1, float *tmpVec2, 
	float *tmpMat1, float *tmpMat2, float *tmpMat3, float *tmpMat4, float *tmpMat5, float *tmpMat6,
	float *xStar, int *iterPoint, int maxIter) {

	// Variables declaration
	float alpha;
	int nv = ndec - nf;
	int i, j, index, indexJ;
	int consIndex, xIndex, boundIndex, fixedIndex, fixedPos, iter, generalIndex;	
	float minLambdal, minLambdaf, minLambda, tmpAlpha, ap;
	float eta, rau, gamma, mu, ve, tmp, tau, maxDiff, diff;
	int addBoundConstraint, addGeneralConstraint;
	int flag = 1;
	int tmpFlag = 0;
	int needCheckFlag = 0;
    int alphaOneTimes = 0;
    
	//FILE *fp_tT, *fp_iniT, *fp_abT, *fp_agT, *fp_dbT, *fp_dgT, *fp_alphaT, *fp_plRtT;


	// Time recording
	//float totalTime, iniTime, AdBdTime, AdGeTime, DeBdTime, DeGeTime, alphaTime, planeRotTime;	

	//clock_t totalStart, totalEnd, iniStart, iniEnd, plRtStart, plRtEnd;		
	//clock_t abStart, abEnd, agStart, agEnd, dbStart, dbEnd, dgStart, dgEnd, aStart, aEnd;


	//fp_tT = fopen("totalTime.txt","r");
	//fp_iniT = fopen("initialTime.txt","r");
	//fp_abT = fopen("AddBoundTime.txt","r");
	//fp_agT = fopen("AddGeneralTime.txt","r");
	//fp_dbT = fopen("DeleteBoundTime.txt","r");
	//fp_dgT = fopen("DeleteGeneralTime.txt","r");
	//fp_alphaT = fopen("alphaTime.txt","r");
	//fp_plRtT = fopen("planeRotTime.txt","r");

	//fscanf(fp_tT,"%lf",&totalTime);
	//fscanf(fp_iniT,"%lf",&iniTime);
	//fscanf(fp_abT,"%lf",&AdBdTime);
	//fscanf(fp_agT,"%lf",&AdGeTime);
	//fscanf(fp_dbT,"%lf",&DeBdTime);
	//fscanf(fp_alphaT,"%lf",&alphaTime);
	//fscanf(fp_plRtT,"%lf",&planeRotTime);

	//fclose(fp_tT); fclose(fp_iniT); fclose(fp_abT); fclose(fp_agT); 
	//fclose(fp_dbT); fclose(fp_dgT);	fclose(fp_alphaT); fclose(fp_plRtT);

	//Print("Before running.\n");
	//Print("totalTime: %lf, iniTime: %lf, AdBdTime: %lf, PlRtTime: %lf", totalTime,iniTime,AdBdTime, planeRotTime);
	//Print(" AdGeTime: %lf, DeBdTime: %lf, DeGeTime: %lf, alphaTime: %lf\n", AdGeTime, DeBdTime, DeGeTime, alphaTime);

	//Print("x:\n"); show_matrix(x,ndec,1); Print("\n");
	//Print("wf:\n"); show_matrixInt(wf,nf,1); Print("\n");
	//Print("wl:\n"); show_matrixInt(wl,ml,1); Print("\n");
	//Print("c:\n"); show_matrix(c_ori,ndec,1); Print("\n");

	//totalStart = clock();
	//iniStart = clock();

	//// Here we check whether the intial x is feasible with given constraints
	//for (i = 0; i<nbc; i++) {
	//	if (x[i] < lx[i]-0.000001 || x[i] > ux[i]+0.000001) {
	//		Print("Initial x infeasible with bound constraint!\n");
	//		return 0;
	//	}

	//	mat_vec(AA,x,ngc,ndec,tmpVec1);		// tmpVec1 = AA * x;
	//	vec_sub(tmpVec1,lg,ngc,tmpVec1);		// tmpVec1 = AA * x - lg;
	//	if (vec_min(tmpVec1,ngc) < -0.000001) {
	//		Print("Initial x infeasible with general constraint!\n");
	//		return 0;
	//	}
	//}										// tmpVec1 Free

	//// Here we check whether the initial x accords with the initial working set
	//for (i = 0; i < nf; i++) {
	//	consIndex = wf[i];
	//	if (consIndex <= nbc) {
	//		if (x[consIndex-1] - lx[consIndex-1] > 0.000000001) {
	//			Print("Initial x does not fit with initial working set! (Bound constraint)\n");
	//			flag = 0;
	//		}
	//	}
	//	else {
	//		if (x[consIndex-1-nbc]- ux[consIndex-1-nbc] > 0.000000001) {
	//			Print("Initial x does not fit with initial working set! (Bound constraint)\n");
	//			flag = 0;
	//		}
	//	}
	//}
	//for (i = 0; i < ml; i++) {
	//	consIndex = wl[i];
	//	for (j = 0; j < ndec; j++) {
	//		tmpVec1[j] = AA[(consIndex-1)*ndec+j];	// tmpVec1 = AA(consIndex,:);
	//	}
	//	if (dot_product(tmpVec1,x,ndec) - lg[consIndex-1] > 0.000000001) {
	//		Print("Initial x does not fit with initial working set! (General constraint)\n");
	//		flag = 0;
	//	}
	//}												// tmpVec1 Free.


	// Here order is used to keep track of the order change of decision variables
	for (i = 0; i < ndec; i++) 
		orderPermu[i] = i;		// Note, in Matlab, order is 1:ndec; in C, order is 0:ndec-1
	for (i = 0; i < ndec*ndec; i++)
		H[i] = H_ori[i];
	for (i = 0; i < ndec; i++)
		c[i] = c_ori[i];

	// If the last nf items of x is not according with the initial bound constraints
	// we should adjust it to meet the requirement of the algorithm
	for (i = 0; i < nf; i++) {
		boundIndex = wf[i];
		fixedIndex = boundIndex % ndec;
		if (fixedIndex==0)
			fixedIndex = ndec;
		fixedPos = nv+1;
		if (fixedIndex <= nv) { // means the fixed item of x is in the first nv rows, needs adjustment              
			swapVecI(orderPermu, fixedPos, fixedIndex);		
			swapMat(H,fixedPos,fixedIndex,ndec,tmpMat6);        
			tmpFlag = 1;
		}
	}	

	// Compute and update gx
	mat_vec(H_ori,x,ndec,ndec,gx);
	vec_add(c_ori,gx,ndec,gx);
	if (tmpFlag == 1)
		permut(gx,orderPermu,ndec,1,tmpMat6);

	// Initialization of isInWl
	for (i = 0; i < ngc; i++) 
		isInWl[i] = 0;
	// isInWl is used to check whether a general constraint is in the working set or not
	for (i = 0; i < ml; i++)
		isInWl[wl[i]-1] = 1;	// Note that the index of the 1st element in isInWl is 

	// Initialize Hv, Rv
	for (i = 0; i < ndec*ndec; i++)
		tmpMat1[i] = H[i];
	chol_NRC(tmpMat1, ndec, tmpVec1);
	for (i = 0; i < ndec; i++)
		tmpMat1[i*ndec+i] = tmpVec1[i];
	for (i = 0; i < ndec; i++)
		for (j = i+1; j < ndec; j++)
			tmpMat1[i*ndec+j] = 0;					// tmpMat1 = R';

	for (i = 0; i < nv; i++)
		for (j = 0; j < nv; j++)
			Rv[i*nv+j] = tmpMat1[i*ndec+j];
	transpose(Rv,nv,nv);

	// Compute pStar for the first iteration
	if (ml == 0) {				
		for (i = 0; i < nv; i++)
			tmpVec1[i] = -gx[i];
		//Print("Rv':\n"); show_matrix(tmpMat1,nv,nv); Print("\n");
		//Print("-gv:\n"); show_matrix(tmpVec1,nv,1); Print("\n");	
		FowSubL(Rv,tmpVec1,nv,tmpMat2,1);	// tmpMat2 = MIDDLE
		BacSubU(Rv,tmpMat2,nv,p,0);

		for (i = 0; i < nv; i++)
			pvStar[i] = p[i];
		for (i = nv; i < ndec; i++)
			p[i]  = 0;
		permutReco(p,orderPermu,ndec,1,tmpMat6);
	}
	else {
		for (i = 0; i < ml; i++) {
			for (j = 0; j < ndec; j++) 
				tmpVec1[j] = AA[(wl[i]-1)*ndec+j];	// tmpVec1 = AA(wl(i),:);
			permut(tmpVec1, orderPermu, ndec, 1,tmpMat6);
			for (j = 0; j < nv; j++)
				tmpMat1[i*nv+j] = tmpVec1[j];			// tmpMat1 = Av;
			for (j = 0; j < nf; j++)
				Af[i*nf+j] = tmpVec1[j+nv];
		}

		// Inverse Rv and QR factorize Av
		uInv(Rv, nv, tmpMat2);							// tmpMat2 = invRv;
		mat_mul(tmpMat1, ml, nv, tmpMat2, nv, tmpMat3);	// tmpMat3 = AinvR;		
		transpose(tmpMat3, nv, ml);		
		gs_m(tmpMat3, nv, ml, Yv, Lv);
		transpose(Lv, ml, ml);

		// Initial value of auxiliary vectors
		FowSubL(Rv, gx, nv, uv, 1);
		matTrans_vec(Yv,uv,nv,ml,vl);
		mat_vec(Yv,vl,nv,ml,wv);
		vec_sub(wv,uv,nv,wv);
		BacSubU(Rv, wv, nv, p, 0);
		for (i = 0; i < nv; i++)
			pvStar[i] = p[i];
		for (i = nv; i < ndec; i++)
			p[i]  = 0;		
		permutReco(p,orderPermu,ndec,1,tmpMat6);		
	}
	//Print("p is (before the first iteration. \n");show_matrix(p,ndec,1);Print("\n");

/*===========================================================================================================*/

	//iniEnd = clock();
	////iniTime += (float)(iniEnd-iniStart)/CLOCKS_PER_SEC;
	//iniTime += (iniEnd-iniStart);

	// Iteration start!
	// Iteration start!
	if (flag != 0) {
		for (iter = 0; iter < maxIter; iter++) {
			if (iter == maxIter) {
				Print("Maximum iteration reached!");
				flag = 0;
				break;
			}

			 // Decide the changes in the working set according to pStar
			if (isZero(p, ndec, 0.0005) == 1) {	//5e-4真是个神奇的数字
				if (ml == 0) {
					for (i = 0; i < nf; i++) {
						if (wf[i] <= nbc)
							lambda[i] = gx[i+nv];
						else
							lambda[i] = -gx[i+nv];
					}
				}
				else {
					BacSubU(Lv,vl,ml,lambdal,1);
					for (i = 0; i < nf; i++) {
						tmpVec1[i] = 0;
						for (j = 0; j < nv; j++)
							tmpVec1[i] += H[j*ndec+i+nv]*pvStar[j];
					}

					for (i = 0; i < nf; i++)
						lambdaf[i] = gx[i+nv] + tmpVec1[i];

					matTrans_vec(Af,lambdal,ml,nf,tmpVec1);		// tmpVec1 = Af'*lambdal
					vec_sub(lambdaf,tmpVec1,nf,lambdaf);
					for (i = 0; i < nf; i++)
						if (wf[i] > nbc)
							lambdaf[i] = -lambdaf[i];
					for (i = 0; i < nf; i++)
						lambda[i] = lambdaf[i];
					for (i = 0; i < ml; i++)
						lambda[i+nf] = lambdal[i];
				}
				//Print("lambda:\n");show_matrix(lambda,nf+ml,1);Print("\n");
				minLambda = vec_min(lambda,nf+ml);
				if ((nf == 0) && (ml == 0) || minLambda > 0) {
					for (i = 0; i < ndec; i++)
						xStar[i] = x[i];
					flag = 1;
					break;
				}
				else {
					minLambdal = vec_min(lambdal,ml);
					minLambdaf = vec_min(lambdaf,nf);
					if ((ml == 0) || ((nf > 0 ) && (minLambdaf < minLambdal))) {	

						//dbStart = clock();

						// Delete a bound constraint
						// Delete a bound constraint
						//index = minIndex(lambdaf, nf);
						index = minIndex(lambda, nf+ml);
						indexJ = wf[index] % nbc;
						if (indexJ == 0)
							indexJ = nbc;
						indexJ = findIndex(orderPermu, ndec, indexJ-1);
						wf[index] = wf[0];
						for (i = 0; i < nf - 1; i++)
							wf[i] = wf[i+1];
						//Print("wf (Del):\n",nf-1);show_matrixInt(wf,nf-1,1);Print("\n");
						if (indexJ <= nv - 1) {
							Print("Bound constraints must be in last nf rows");
							flag = 0;
							break;
						}					
						swapVecI(orderPermu,indexJ,nv+1);
						swapMat(H,indexJ,nv+1,ndec,tmpMat6);
						swapVecF(gx,indexJ,nv+1,1,tmpMat6,0);

						for (i = 0; i < nv; i++)
							tmpMat2[i] = H[nv*ndec+i];							// tmpMat2 = h;
						eta = H[nv*ndec+nv];

						FowSubL(Rv,tmpMat2,nv,tmpVec1,1);						// tmpVec1 = r;
						rau = sqrt(eta - dot_product(tmpVec1,tmpVec1,nv));
						for (i = 0; i < nv; i++)
							for (j = 0; j < nv; j++)
								tmpMat3[i*(nv+1)+j] = Rv[i*nv+j];
						for (i = 0; i < nv; i++)
							tmpMat3[i*(nv+1)+nv] = tmpVec1[i];
						for (i = 0; i < nv; i++)
							tmpMat3[nv*(nv+1)+i] = 0;
						tmpMat3[nv*(nv+1)+nv] = rau;							// tmpMat3 = Rv_bar;

						// Recover Av before Rv is updated
						matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);					// tmpMat1 = Yv'*Rv;
						mat_mul(Lv,ml,ml,tmpMat1,nv,tmpMat4);					// tmpMat4 = Av;	

						for (i = 0; i < (nv+1); i++) 
							for (j = 0; j < nv+1; j++) 
								Rv[i*(nv+1)+j] = tmpMat3[i*(nv+1)+j];																						

						nv = nv + 1;
						nf = nf - 1;

						if (ml == 0) {
							for (i = 0; i < nv; i++)
								tmpMat2[i] = -gx[i];							// tmpMat2 = -gv;
							FowSubL(Rv,tmpMat2,nv,tmpMat1,1);					// tmpMat1 = MIDDLE
							BacSubU(Rv,tmpMat1,nv,pvStar,0);
							for (i = 0; i < nv; i++)
								p[i] = pvStar[i];
							for (i = nv; i < ndec; i++)
								p[i] = 0;
							permutReco(p,orderPermu,ndec,1,tmpMat6);
							//Print("p is:\n");show_matrix(p,ndec,1);Print("\n");
						}
						else {
							for (i = 0; i < nv; i++)		
								tmpMat1[i] = 0;
							tmpMat1[nv-1]  = 1;									// tmpMat1 = ev1;
							BacSubU(Rv,tmpMat1,nv,tmpMat2,0);					// tmpMat2 = q;

							// Update Af
							for (i = 0; i < ml; i++)
								tmpMat3[i] = Af[i*(nf+1)+indexJ-nv];			// tmpMat3 = a;
							for (i = 0; i < ml; i++)
								Af[i*(nf+1)+indexJ-nv] = Af[i*(nf+1)];
							for (i = 0; i < ml; i++)
								for (j = 0; j < nf; j++)
									Af[i*nf+j] = Af[i*(nf+1)+j+1];
								
							for (i = 0; i < ml; i++)
								for (j = 0; j < nv-1; j++)
									tmpMat1[i*nv+j] =  tmpMat4[i*(nv-1)+j];
							for (i = 0; i < ml; i++)
								tmpMat1[i*nv+nv-1] = tmpMat3[i];				// tmpMat1 = Av_bar;							

							mat_vec(tmpMat1,tmpMat2,ml,nv,tmpMat3);				// tmpMat3 = v;

							// Updates
							for (i = 0; i < nv - 1; i++)
								tmpMat2[i] = alpha * wv[i];						// tmpMat2 = alpha*wv;
							vec_add(uv,tmpMat2,nv-1,tmpMat2);					// tmpMat2 = uv_tilde;
							gamma = gx[nv-1];
							mu = (gamma - dot_product(tmpVec1,tmpMat2,nv-1))/rau;				
							uv[nv-1] = mu;	
							for (i = 0; i < nv-1; i++)
								uv[i] = tmpMat2[i];
							for (i = 0; i < ml; i++)
								tmpVec1[i] = vl[i];
							tmpVec1[ml] = mu;									// tmpVec1 = [vl;mu];

							for (i = 0; i < ml; i++)
								for (j = 0; j < ml; j++)
									tmpMat1[i*(ml+1)+j] = Lv[i*ml+j];
							for (i = 0; i < ml; i++)
								tmpMat1[i*(ml+1)+ml] = tmpMat3[i];				// tmpMat1 = LvvP;
				
							for (i = 0; i < nv-1; i++)
								for (j = 0; j < ml; j++)
									tmpMat2[i*(ml+1)+j] = Yv[i*ml+j];
							for (i = 0; i < nv-1; i++)
								tmpMat2[i*(ml+1)+ml] = 0;
							for (i = 0; i < ml; i++)
								tmpMat2[(nv-1)*(ml+1)+i] = 0;					// tmpMat2 = [Yv,zeros(nv-1,1);zeros(1,ml),1];

							tmpMat2[(nv-1)*(ml+1)+ml] = 1;						// tmpMat2 = YvP;

							for (i = 0; i < ml; i++) {
								myplanerot(tmpMat1[i*(ml+1)+i],tmpMat1[i*(ml+1)+ml],G);
								colRot(tmpMat1, G, ml, ml+1, i+1, ml+1);		// Rotate LvvP
								colRot(tmpMat2, G, nv, ml+1, i+1, ml+1);		// Rotate YvP
								rowRot(tmpVec1, G, 1, i+1, ml+1);				// Rotate vl_barv;
							}

							for (i = 0; i < ml; i++) 
								for (j = 0; j < ml; j++)
									Lv[i*ml+j] = tmpMat1[i*(ml+1)+j];						
							
							for (i = 0; i < nv; i++)
								for (j = 0; j < ml; j++)
									Yv[i*ml+j] = tmpMat2[i*(ml+1)+j];
							for (i = 0; i < nv; i++)
								tmpMat1[i] = tmpMat2[i*(ml+1)+ml];				// tmpMat1 = z_bar;

							for (i = 0; i < ml; i++)
								vl[i] = tmpVec1[i];
							ve = tmpVec1[ml];									// Here ve is the v in m-file
							for (i = 0; i < nv; i++)
								tmpMat1[i] = ve * tmpMat1[i];					// tmpMat1 = v*z_bar;
							for (i = 0; i < nv - 1; i++)
								wv[i] = (1-alpha)*wv[i];
							wv[nv-1] = 0;
							vec_sub(wv,tmpMat1,nv,wv);
							BacSubU(Rv,wv,nv,pvStar,0);
						
							for (i = 0; i < nv; i++)
								p[i] = pvStar[i];
							for (i = nv; i < ndec; i++)
								p[i] = 0;					
							permutReco(p,orderPermu,ndec,1,tmpMat6);
							//Print("p is:\n");show_matrix(p,ndec,1);Print("\n");
						}
						//dbEnd = clock();
						////DeBdTime += (float)(dbEnd-dbStart)/CLOCKS_PER_SEC;
						//DeBdTime += (dbEnd-dbStart);
					}
					else {

						//dgStart = clock();

						// Delete a general constraint
						// Delete a general constraint
						index = minIndex(lambdal, ml);
						isInWl[wl[index]-1] = 0;
						for (i = 0; i < ml-1; i++) 
							if (i >= index)
								wl[i] = wl[i+1];
						ml = ml - 1;
						//Print("wl (Del):\n");show_matrixInt(wl,ml,1);Print("\n");
						if (ml == 0) {
							for (i = 0; i < nv; i++)
								tmpVec1[i] = -gx[i];				// tmpVec1 = -gv;							
							FowSubL(Rv,tmpVec1,nv,tmpMat2,1);		// tmpMat2 = MIDDLE
							BacSubU(Rv,tmpMat2,nv,pvStar,0);
							for (i = 0; i < nv; i++)
								p[i] = pvStar[i];
							for (i = nv; i < ndec; i++)
								p[i] = 0;
							permutReco(p,orderPermu,ndec,1,tmpMat6);
							//Print("p is:\n");show_matrix(p,ndec,1);Print("\n");
						}

						else {
							for (i = 0; i < (ml+1)*(ml+1); i++)		// Here use ml+1 because ml has been updated
								tmpMat1[i] = Lv[i];
							for (i = 0; i < (ml+1); i++)
								tmpMat1[ml*(ml+1)+i] = Lv[index*(ml+1)+i];
							for (i = index; i < ml; i++)
								for (j = 0; j < (ml+1); j++)
									tmpMat1[i*(ml+1)+j] = Lv[(i+1)*(ml+1)+j];	// tmpMat1 = Lv_tilde;

							for (i = 0; i < nv*(ml+1); i++)
								tmpMat2[i] = Yv[i];								// tmpMat2 = YP;
							
							for (i = 0; i < ml-index; i++) {					// Here, index is not same as in Matlab
								myplanerot(tmpMat1[(index+i)*(ml+1)+(index+i)],tmpMat1[(index+i)*(ml+1)+index+i+1],G);								
								colRot(tmpMat1, G, ml+1, ml+1, index+i+1, index+2+i);	// Rotate Lv_tilde;
								rowRot(vl, G, 1, index+i+1, index+2+i);					// Rotate vl;
								colRot(tmpMat2, G, nv, ml+1, index+i+1, index+2+i);		// Rotate YP;												
							}

							ve = vl[ml];
							for (i = 0; i < ml; i++)
								for (j = 0; j < ml; j++)
									Lv[i*ml+j] = tmpMat1[i*(ml+1)+j];

							for (i = 0; i < nv; i++)
								for (j = 0; j < ml; j++)
									Yv[i*ml+j] = tmpMat2[i*(ml+1)+j];	
							for (i = 0; i < nv; i++)
								tmpVec1[i] = tmpMat2[i*(ml+1)+ml];				// tmpVec1 = z_bar;
							for (i = 0; i < nv; i++)
								tmpMat1[i] = alpha * wv[i];						// tmpMat1 = alpha * wv;
							vec_add(uv,tmpMat1,nv,uv);												

							for (i = 0; i < nv; i++)
								wv[i] = (1-alpha)*wv[i] - ve*tmpVec1[i];


							// Update Af
							for (i = 0; i < ml; i++) {
								if (i >= index) {
									for (j = 0; j < nf; j++) 	
										Af[i*nf+j] = Af[(i+1)*nf+j];
								}
							}
							//Print("Af:\n"); show_matrix(Af,nf,ml); putchar('\n');

                            
                            
//                             if (needCheckFlag == 1) {	// Imprecision may happen
//                                 tmpMat3[ml-1] = gamma;
//                                 matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);
//                                 vec_mat(tmpMat1,tmpMat3,ml,nv,tmpMat2);
//                                 maxDiff = 0;
//                                 for (i = 0; i < nv; i++) {
//                                     diff = tmpVec1[i] - tmpMat2[i];
//                                     if ( diff > maxDiff)
//                                         maxDiff = diff;
//                                     else if (-diff > maxDiff)
//                                         maxDiff = -diff;
//                                     
//                                 }
//                                 //if (maxDiff > 0.0005) {		// Threshold need to be set
//                                 if (maxDiff > 0.001) {		//设成0.01看float解MPC行不行 // Threshold need to be set
//                                     // Update Error, initialize factorization
//                                     //Print("maxDiff: %f. No ReUpdate.\n",maxDiff);
//                                     // Get Av
//                                     Print("(Deleting) maxDiff: %f. Need re-decomposition.\n",maxDiff);
//                                     for (i = 0; i < ml; i++) {
//                                         for (j = 0; j < ndec; j++)
//                                             tmpVec1[j] = AA[(wl[i]-1)*ndec+j];		// tmpVec1 = AA(wl(i),:);
//                                         permut(tmpVec1, orderPermu, ndec, 1,tmpMat6);
//                                         for (j = 0; j < nv; j++)
//                                             tmpMat1[i*nv+j] = tmpVec1[j];			// tmpMat1 = Av;
//                                         
//                                     }
//                                     // Inverse Rv and QR factorize Av
//                                     uInv(Rv, nv, tmpMat2);							// tmpMat2 = invRv;
//                                     mat_mul(tmpMat1, ml, nv, tmpMat2, nv, tmpMat3);	// tmpMat3 = AinvR;
//                                     transpose(tmpMat3, nv, ml);
//                                     Print("AinvR':\n"); show_matrix(tmpMat3,ml,nv); Print("\n");
//                                     if (gs_m(tmpMat3, nv, ml, tmpMat1, tmpMat2) == 1) {
//                                         Print("Re-decomposition succeed.\n");
//                                         for (i = 0; i < nv*ml; i++)
//                                             Yv[i] = tmpMat1[i];
//                                         for (i = 0; i < ml*ml; i++)
//                                             Lv[i] = tmpMat2[i];
//                                         transpose(Lv, ml, ml);
//                                         Print("Yv:\n"); show_matrix(Yv,ml,nv); Print("\n");
//                                         //Print("Lv:\n"); show_matrix(Lv,ml,ml); Print("\n");
//                                         // Initial value of auxiliary vectors
//                                         //FowSubL(tmpMat1, tmpVec1, nv, uv, 0);			// tmpVec1 = gv;
//                                         FowSubL(Rv, gx, nv, uv, 1);			// tmpVec1 = gv;
//                                         Print("uv:\n"); show_matrix(uv,nv,1); Print("\n");
//                                         matTrans_vec(Yv,uv,nv,ml,vl);
//                                         //Print("Yv:\n"); show_matrix(Yv,nv,ml); Print("\n");
//                                         Print("vl:\n"); show_matrix(vl,ml,1); Print("\n");
//                                         mat_vec(Yv,vl,nv,ml,wv);
//                                         vec_sub(wv,uv,nv,wv);
//                                     }
//                                     // 更新之后的再求解p就好象有点问题？
//                                     //Print("Rv:\n"); show_matrix(Rv,nv,nv); Print("\n");
//                                     //Print("wv:\n"); show_matrix(wv,nv,1); Print("\n");
//                                     //Print("Yv'*wv:\n"); show_matrix(tmpVec1,nv,1); Print("\n");
//                                     
//                                 }
//                                 
//                             }
                            
                            
                            
// 							// Check code
// 							matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);
// 							mat_mul(Lv,ml,ml,tmpMat1,nv,tmpMat3);
// 							for (i = 0; i < ml; i++) {
// 								for (j = 0; j < ndec; j++) 
// 									tmpVec1[j] = AA[(wl[i]-1)*ndec+j];		// tmpVec1 = AA(wl(i),:);
// 								permut(tmpVec1, orderPermu, ndec, 1,tmpMat6);
// 								for (j = 0; j < nv; j++)
// 									tmpMat1[i*nv+j] = tmpVec1[j];			// tmpMat1 = Av;
// 							}
// 							vec_sub(tmpMat1,tmpMat3,nv*ml,tmpMat4);
// 							for (i = 0; i < nv*ml; i++) {
// 								if (tmpMat4[i] > 0.0001 || tmpMat4[i] < -0.0001) {
// 									Print("Av or Lv update fails. (error: %f)\n",tmpMat4[i]);
// 									//printf("Av:\n"); show_matrix(tmpMat1,nv,ml); putchar('\n');
// 									//printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
// 									//printf("Yv:\n"); show_matrix(Yv,ml,nv); putchar('\n');
// 									//printf("Rv:\n"); show_matrix(Rv,nv,nv); putchar('\n');
// 									//return 0;



// 								}
// 							}
							                            
							// Compute p for the next iteration
							BacSubU(Rv,wv,nv,pvStar,0);
							for (i = 0; i < nv; i++)
								p[i] = pvStar[i];
							for (i = nv; i < ndec; i++)
								p[i] = 0;					
							permutReco(p,orderPermu,ndec,1,tmpMat6);
							//Print("p is:\n");show_matrix(p,ndec,1);Print("\n");

						}
						//dgEnd = clock();
						////DeGeTime += (float)(dgEnd-dgStart)/CLOCKS_PER_SEC;
						//DeGeTime += (dgEnd-dgStart);
					}
				}
			}
			else {
				//aStart = clock();
				
				// Calculate alpha				
				alpha = 1;
				addBoundConstraint = 0;
				addGeneralConstraint = 0;
				for (i = 0; i < nbc; i++) {
					if (p[i] < 0) {
						tmpAlpha = (lx[i]-x[i])/p[i];
						if (tmpAlpha < alpha) {
							alpha = tmpAlpha;
							addBoundConstraint = 1;
							boundIndex = i+1;
						}
					}
				}
				//Print("alpha (1st): %f\n",alpha);
				for (i = nbc; i < 2*nbc; i++) {
					if (p[i-nbc] > 0) {
						tmpAlpha = (ux[i-nbc]-x[i-nbc])/p[i-nbc];
						if (tmpAlpha < alpha) {
							alpha = tmpAlpha;
							addBoundConstraint = 1;
							boundIndex = i+1;
						}
					}
				}
				//Print("alpha (2nd): %f\n",alpha);
				if (alpha > 0.00000001) {
					for (i = 0; i < ngc; i++) {
						if (isInWl[i] == 0) {
							ap = 0.0;
							for (j = 0; j < ndec; j++) {
								ap += AA[i*ndec+j]*p[j];

							}
							if (ap < -0.000001) {
								tmp = 0.0;
								for (j = 0; j < ndec; j++)
									tmp += AA[i*ndec+j]*x[j];
								tmp = lg[i] - tmp;
								if (ap > -0.000001 && tmp > -0.00001 && tmp < 0.00001)		// Need note after
									continue;
								tmpAlpha = tmp/ap;
								if (tmpAlpha < alpha + 0.0000001) {
									alpha = tmpAlpha;
									addGeneralConstraint = 1;
									addBoundConstraint = 0;
									generalIndex = i+1;
								}
								if (alpha < 0.000000001)
									break;
							}
						}
					}
				}

				//aEnd = clock();
				////alphaTime += (float)(aEnd-aStart)/CLOCKS_PER_SEC;
				//alphaTime += (aEnd-aStart);

				if (alpha > 1)
					alpha = 1;
				if (alpha < 0)
					alpha = 0;
                if (alpha > 0.9999)
                    alphaOneTimes = alphaOneTimes + 1;
                else
                    alphaOneTimes = 0;
                
				for (i = 0; i < ndec; i++)
					x[i] = x[i] + alpha*p[i];
				//Print("alpha: %f\n",alpha);
			
				// Compute and update gx
				mat_vec(H_ori,x,ndec,ndec,gx);
				vec_add(c_ori,gx,ndec,gx);
				permut(gx,orderPermu,ndec,1,tmpMat6);
			
				//Print("x is:\n");show_matrix(x,ndec,1);Print("\n");
				//Print("gx is:\n");show_matrix(gx,ndec,1);Print("\n");

				if (alpha < 1) {
					if ((addBoundConstraint == 1) && (addGeneralConstraint == 0)) {					
						
						//abStart = clock();
						
						// Adding a bound constraint
						for (i = nf; i > 0; i--) 
							wf[i] = wf[i-1];
						wf[0] = boundIndex;
						//Print("wf (Add):\n");show_matrixInt(wf,nf+1,1);Print("\n");
						indexJ = boundIndex % nbc;
						if (indexJ == 0)
							indexJ = nbc;
						indexJ = findIndex(orderPermu, ndec, indexJ-1);
						// Here indexJ should be from 1 to n (not 0 to n-1), for comparison with Matlab
						for (i = 0; i < nv*nv; i++)
							tmpMat1[i] = Rv[i];			

						swapVecF(tmpMat1,indexJ,nv,nv,tmpMat6,1);		// tmpMat1 = tmpS;

						for (i = 0; i < nv * nv; i++)
							tmpMat4[i] = 0;
						for (i = 0; i < nv; i++)
							tmpMat4[i*nv+i] = 1;						// tmpMat4 = Q;	
						
						//plRtStart = clock();
						for (i = 0; i < (nv-indexJ-1); i++) {
							myplanerot(tmpMat1[(nv-1)*nv+indexJ-1],tmpMat1[(nv-(i+1)-1)*nv+indexJ-1],G);										
							rowRot(tmpMat1,G,nv,nv,nv-(i+1));
							rowRot(tmpMat4,G,nv,nv,nv-(i+1));
						}					
						for (i = 0; i < (nv - indexJ); i++) {
							myplanerot(tmpMat1[((i+1)+indexJ-2)*nv+((i+1)+indexJ-2)],tmpMat1[(nv-1)*nv+((i+1)+indexJ-2)],G);
							rowRot(tmpMat1,G,nv,(i+1)+indexJ-1,nv);
							rowRot(tmpMat4,G,nv,(i+1)+indexJ-1,nv);
						}		

						//plRtEnd = clock();
						//planeRotTime += (plRtEnd - plRtStart);

						//mat_mul(tmpMat4,nv,nv,Rv,nv,tmpMat1);		// tmpMat1 = Q*Rv;
						//swapVecF(tmpMat1,indexJ,nv,nv,tmpMat6,1);	// tmpMat1 = Rv_hat;

						for (i = 0; i < nv-1; i++)
							for (j = 0; j < nv-1; j++)
								Rv[i*(nv-1)+j] = tmpMat1[i*nv+j];	// tmpMat1 = Rv_hat;
						
						swapVecI(orderPermu,indexJ,nv);
						swapMat(H,indexJ,nv,ndec,tmpMat6);
						swapVecF(gx,indexJ,nv,1,tmpMat6,0);				
					
						nv = nv - 1;
						nf = nf + 1;

						if (ml == 0) {
							
							if (nf == ndec) {
								for (i = 0; i < ndec; i++)
									pvStar[i] = 0;
							}
							else {
								for (i = 0; i < nv; i++)
									tmpVec1[i] = -gx[i];				// tmpVec1 = -gv;
								FowSubL(Rv,tmpVec1,nv,tmpMat2,1);
								BacSubU(Rv,tmpMat2,nv,pvStar,0);													
							}
							for (i = 0; i < nv; i++)
								p[i] = pvStar[i];
							for (i = nv; i < ndec; i++)
								p[i] = 0;
							permutReco(p,orderPermu,ndec,1,tmpMat6);
							//Print("p is:\n");show_matrix(p,ndec,1);Print("\n");
						}
						else {				
							mat_mul(tmpMat4,nv+1,nv+1,Yv,ml,tmpMat3);			// tmpMat3 = QYv(Y_tilde);
							for (i = 0; i < ml; i++)								// QYv: (nv+1)*(ml)
								tmpMat2[i] = tmpMat3[nv*ml+i];					// tmpMat2 = y_tilde;			
							tau = 1/sqrt(1-dot_product(tmpMat2,tmpMat2,ml));
							mat_vec(tmpMat3,tmpMat2,nv,ml,tmpVec1);				// tmpVec1 = Y_tilde*y_tilde;
							for (i = 0; i < nv; i++)
								tmpVec1[i] = -tau*tmpVec1[i];				
							tmpVec1[nv] = 1/tau;								// tmpVec1 = z;				
							if (ml > nv) {
								Print("Unsolvable!\n");
								flag = 0;
								break;
							}
							for (i = 0; i < (nv+1); i++)
								for (j = 0; j < ml; j++)
									tmpMat5[i*(ml+1)+j] = tmpMat3[i*ml+j];	
							for (i = 0; i < nv+1; i++)
								tmpMat5[i*(ml+1)+ml] = tmpVec1[i];				// tmpMat5 = QYz	// QYz: (nv+1)*(ml+1)
						

							for (i = 0; i < ml; i++)
								tmpVec2[i] = AA[(wl[i]-1)*ndec+orderPermu[nv]];

							for (i = 0; i < (nf-1)*(ml); i++)
								tmpMat1[i] = Af[i];								// tmpMat1 = Af;
							for (i = 0; i < ml; i++)
								Af[i*nf] = tmpVec2[i];
							for (i = 0; i < ml; i++)
								for (j = 0; j < nf-1; j++)
									Af[i*nf+j+1] = tmpMat1[i*(nf-1)+j];

							for (i = 0; i < (ml+1)*(ml+1); i++)
								P[i] = 0;
							for (i = 0; i < ml+1; i++)
								P[i*(ml+1)+i] = 1;
							
							//plRtStart = clock();
							for (i = 0; i < ml; i++) {
                                myplanerot(tmpMat5[nv*(ml+1)+ml],tmpMat5[(nv*(ml+1)+ml-(i+1))],G);
                                colRot(tmpMat5, G, nv+1, ml+1, ml+1,ml+1-(i+1));
								colRot(P, G, ml+1,ml+1,ml+1,ml+1-(i+1));
							}
							//plRtEnd = clock();
							//planeRotTime += (plRtEnd - plRtStart);

							for (i = 0; i < nv+1; i++)
								for (j = 0; j < ml; j++)
									tmpMat1[i*(ml+1)+j] = tmpMat3[i*ml+j];			
							for (i = 0; i < nv+1; i++)
								tmpMat1[i*(ml+1)+ml] = tmpVec1[i];				// tmpMat1 = [QYv,z];
							mat_mul(tmpMat1,nv+1,ml+1,P,ml+1,tmpMat5);			// tmpMat5 = QYP;
							vec_mat(tmpMat4,tmpVec1,nv+1,nv+1,tmpVec2);			// tmpVec2 = z;
							for (i = 0; i < nv; i++)
								for (j = 0; j < ml; j++)
									Yv[i*ml+j] = tmpMat5[i*(ml+1)+j];
							for (i = 0; i < ml; i++)
								for (j = 0; j < ml; j++)
									tmpMat1[i*(ml+1)+j] = Lv[i*ml+j];
							for (i = 0; i < ml; i++)
								tmpMat1[i*(ml+1)+ml] = 0;						// tmpMat1 = [Lv,zeros(ml,1)]
							mat_mul(tmpMat1,ml,ml+1,P,ml+1,tmpMat2);			// tmpMat2 = LvP;
							for (i = 0; i < ml; i++)
								for (j = 0; j < ml; j++)
									Lv[i*ml+j] = tmpMat2[i*(ml+1)+j];


							for (i = 0; i < nv+1; i++)
								tmpVec1[i] = uv[i] + alpha * wv[i];				// tmpVec1 = uv+alpha*wv;
							mat_vec(tmpMat4,tmpVec1,nv+1,nv+1,tmpMat1);			// tmpMat1 = uv_bar;
							ve = (1-alpha)*dot_product(tmpVec2,uv,nv+1);
							for (i = 0; i < ml; i++)
								tmpVec1[i] = vl[i];
							tmpVec1[ml] = ve;									// tmpVec1 = [vl;v];
							vec_mat(P,tmpVec1,ml+1,ml+1,vl);
							for (i = 0; i < nv; i++)
								uv[i] = tmpMat1[i];
							for (i = 0; i < nv+1; i++)
								tmpVec1[i] = (1-alpha)*wv[i]+ve*tmpVec2[i];		// tmpVec1 = (1-alpha)*wv+v*z;
							mat_vec(tmpMat4,tmpVec1,nv+1,nv+1,wv);

							// Compute p for the next iteration
							BacSubU(Rv,wv,nv,pvStar,0);
							for (i = 0; i < nv; i++)
								p[i] = pvStar[i];
							for (i = nv; i < ndec; i++)
								p[i] = 0;					
							permutReco(p,orderPermu,ndec,1,tmpMat6);
							//Print("p is:\n");show_matrix(p,ndec,1);Print("\n");
						}
						//abEnd = clock();
						////AdBdTime += (float)(abEnd-abStart)/CLOCKS_PER_SEC;
						//AdBdTime += (abEnd-abStart);
					}
					else if ((addBoundConstraint == 0) && (addGeneralConstraint ==1)) {

						//agStart = clock();

						// Adding a general constraint
						isInWl[generalIndex-1] = 1;
						wl[ml] = generalIndex;
						//Print("wl (Add):\n"); show_matrixInt(wl,ml+1,1); Print("\n");
						ml = ml + 1;
					
						for (i = 0; i < ndec; i++)
							tmpVec1[i] = AA[(generalIndex-1)*ndec+i];
						permut(tmpVec1,orderPermu,ndec,1,tmpMat6);			// tmpVec1 = a;

						if (ml == 1) {
							uInv(Rv, nv, tmpMat2);							// tmpMat2 = inv(Rv);
							for (i = 0; i < nv; i++)
								tmpMat1[i] = tmpVec1[i];					// tmpMat1 = Av;		
							for (i = nv; i < ndec; i++)
								Af[i-nv] = tmpVec1[i];							
							mat_mul(tmpMat1,ml,nv,tmpMat2,nv,tmpMat3);		// tmpMat3 = AinvR';							
							gs_m(tmpMat3, nv, ml, Yv, Lv);
							transpose(Lv, ml, ml);

							FowSubL(Rv, gx, nv, uv, 1);	
							matTrans_vec(Yv,uv,nv,ml,vl);
							mat_vec(Yv,vl,nv,ml,wv);
							vec_sub(wv,uv,nv,wv);			
						}
						else {
							FowSubL(Rv, tmpVec1, nv, tmpVec2, 1);			// tmpVec2 = q;
							mat_mulTrans(Yv,nv,ml-1,Yv,nv,tmpMat3);			// tmpMat3 = Yv*Yv';

							for (i = 0; i < nv*nv; i++)
								tmpMat3[i] = -tmpMat3[i];
							for (i = 0; i < nv; i++)
								tmpMat3[i*nv+i] = tmpMat3[i*nv+i] + 1;		// tmpMat3 = (eye(nv,nv)-Yv*Yv');
							mat_vec(tmpMat3,tmpVec2,nv,nv,tmpMat4);			// tmpMat4 = z_unnomalized;
							tau = sqrt(1/(dot_product(tmpMat4,tmpMat4,nv)));
							for (i = 0; i < nv; i++)
								tmpMat5[i] = tau*tmpMat4[i];				// tmpMat5 = z;
							for (i = 0; i < nv; i++)
								for (j = 0; j < ml-1; j++)
									tmpMat1[i*ml+j] = Yv[i*(ml-1)+j];
							for (i = 0; i < nv; i++)
								tmpMat1[i*ml+(ml-1)] = tmpMat5[i];			// tmpMat1 = Yv_bar;

							matTrans_vec(Yv,tmpVec2,nv,ml-1,tmpMat3);		// tmpMat3 = l;

							gamma = dot_product(tmpMat5,tmpVec2,nv);
							for (i = 0; i < ml-1; i++)
								for (j = 0; j < ml-1; j++)
									tmpMat2[i*ml+j] = Lv[i*(ml-1)+j];
							for (i = 0; i < ml-1; i++)
								tmpMat2[i*ml+ml-1] = 0;
							for (i = 0; i < ml-1; i++)
								tmpMat2[(ml-1)*ml+i] = tmpMat3[i];
							tmpMat2[(ml-1)*ml+ml-1] = gamma;				// tmpMat2 = Lv_bar;		
							for (i = 0; i < nv; i++)
								tmpVec2[i] = uv[i] + alpha*wv[i];			// tmpVec2 = uv_bar;
							ve = (1-alpha)*dot_product(tmpMat5,uv,nv);
							vl[ml-1] = ve;
							for (i = 0; i < nv; i++)
								wv[i] = (1-alpha)*wv[i]+ve*tmpMat5[i];
							// Update Af
							for (i = 0; i < nf; i++)
								Af[(ml-1)*nf+i] = tmpVec1[i+nv];

							for (i = 0; i < nv*ml; i++)
								Yv[i] = tmpMat1[i];
							for (i = 0; i < ml*ml; i++)
								Lv[i] = tmpMat2[i];
							for (i = 0; i < nv; i++)
								uv[i] = tmpVec2[i];

							// 正常状态下校验Yv'*wv
							//matTrans_vec(Yv,wv,nv,ml,tmpVec1);
							//Print("Yv'*wv (Normal):\n"); show_matrix(tmpVec1,nv,1); Print("\n");

							//if (needCheckFlag == 1) {	// Imprecision may happen
								tmpMat3[ml-1] = gamma;
								matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);
								vec_mat(tmpMat1,tmpMat3,ml,nv,tmpMat2);
								maxDiff = 0;
								for (i = 0; i < nv; i++) {
									diff = tmpVec1[i] - tmpMat2[i];
									if ( diff > maxDiff)
										maxDiff = diff;
									else if (-diff > maxDiff)
										maxDiff = -diff;

								}
								//if (maxDiff > 0.0005) {		// Threshold need to be set
                                if (maxDiff > 0.001) {		//设成0.01看float解MPC行不行 // Threshold need to be set
									// Update Error, initialize factorization									
                                    //Print("maxDiff: %f. No ReUpdate.\n",maxDiff);
                                    // Get Av
									//Print("maxDiff: %f. Need re-decomposition.\n",maxDiff);
									for (i = 0; i < ml; i++) {
										for (j = 0; j < ndec; j++) 
											tmpVec1[j] = AA[(wl[i]-1)*ndec+j];		// tmpVec1 = AA(wl(i),:);
										permut(tmpVec1, orderPermu, ndec, 1,tmpMat6);
										for (j = 0; j < nv; j++)
											tmpMat1[i*nv+j] = tmpVec1[j];			// tmpMat1 = Av;

									}
									// Inverse Rv and QR factorize Av
                                    uInv(Rv, nv, tmpMat2);							// tmpMat2 = invRv;
                                    mat_mul(tmpMat1, ml, nv, tmpMat2, nv, tmpMat3);	// tmpMat3 = AinvR;
                                    transpose(tmpMat3, nv, ml);
                                    //Print("AinvR':\n"); show_matrix(tmpMat3,ml,nv); Print("\n");
                                    if (gs_m(tmpMat3, nv, ml, tmpMat1, tmpMat2) == 1) {
                                        //Print("Re-decomposition succeed.\n");
                                        for (i = 0; i < nv*ml; i++)
                                            Yv[i] = tmpMat1[i];
                                        for (i = 0; i < ml*ml; i++)
                                            Lv[i] = tmpMat2[i];
                                        transpose(Lv, ml, ml);
                                        //Print("Yv:\n"); show_matrix(Yv,ml,nv); Print("\n");
                                        //Print("Lv:\n"); show_matrix(Lv,ml,ml); Print("\n");
                                        // Initial value of auxiliary vectors
                                        //FowSubL(tmpMat1, tmpVec1, nv, uv, 0);			// tmpVec1 = gv;
                                        FowSubL(Rv, gx, nv, uv, 1);			// tmpVec1 = gv;
                                        //Print("uv:\n"); show_matrix(uv,nv,1); Print("\n");
                                        matTrans_vec(Yv,uv,nv,ml,vl);
                                        //Print("Yv:\n"); show_matrix(Yv,nv,ml); Print("\n");
                                        //Print("vl:\n"); show_matrix(vl,ml,1); Print("\n");
                                        mat_vec(Yv,vl,nv,ml,wv);
                                        vec_sub(wv,uv,nv,wv);
                                    }                                                                     
									// 更新之后的再求解p就好象有点问题？
									//Print("Rv:\n"); show_matrix(Rv,nv,nv); Print("\n");
									//Print("wv:\n"); show_matrix(wv,nv,1); Print("\n");
									//Print("Yv'*wv:\n"); show_matrix(tmpVec1,nv,1); Print("\n");
                                    
								}
                                
							//}

						}
						
// 						// Check code
// 						matTrans_mul(Yv,nv,ml,Rv,nv,tmpMat1);
// 						mat_mul(Lv,ml,ml,tmpMat1,nv,tmpMat3);
// 						for (i = 0; i < ml; i++) {
// 							for (j = 0; j < ndec; j++) 
// 								tmpVec1[j] = AA[(wl[i]-1)*ndec+j];		// tmpVec1 = AA(wl(i),:);	
// 							permut(tmpVec1, orderPermu, ndec, 1,tmpMat6);
// 							for (j = 0; j < nv; j++)
// 								tmpMat1[i*nv+j] = tmpVec1[j];			// tmpMat1 = Av;
// 						}
// 						vec_sub(tmpMat1,tmpMat3,nv*ml,tmpMat4);
// 						for (i = 0; i < nv*ml; i++) {
// 							if (tmpMat4[i] > 0.001 || tmpMat4[i] < -0.001) {
// 								Print("Av or Lv update fails. (nv: %d, ml: %d, i: %d, error: %f)\n",nv,ml,i,tmpMat4[i]);
// 								//printf("Av:\n"); show_matrix(tmpMat1,nv,ml); putchar('\n');
// 								//printf("Lv:\n"); show_matrix(Lv,ml,ml); putchar('\n');
// 								//printf("Yv:\n"); show_matrix(Yv,ml,nv); putchar('\n');
// 								//printf("Rv:\n"); show_matrix(Rv,nv,nv); putchar('\n');
// 								//return 0;
// 							}
// 						}


						if (ml == ndec) {
							for (i = 0; i < ndec; i++)
								p[i] = 0;
							needCheckFlag = 1;
						}
						else {
							BacSubU(Rv, wv, nv, p, 0);
						}
						
						for (i = 0; i < nv; i++)
							pvStar[i] = p[i];
						for (i = nv; i < ndec; i++)
							p[i]  = 0;		
						permutReco(p,orderPermu,ndec,1,tmpMat6);	
						//Print("p is:\n");show_matrix(p,ndec,1);Print("\n");

						//agEnd = clock();
						////AdGeTime += (float)(agEnd-agStart)/CLOCKS_PER_SEC;
						//AdGeTime += (agEnd-agStart);

					}
					else {
						Print("Add constraint error!\n");
						flag = 0;
						break;
					}
				}
				else {		// If alpha == 1, p is solved again without changing working set

					if (ml == 0) {
						for (i = 0; i < nv; i++)
							tmpVec1[i] = -gx[i];				// tmpVec1 = -gv;
						FowSubL(Rv,tmpVec1,nv,tmpVec2,1);	// tmpVec2 = MIDDLE
						BacSubU(Rv,tmpVec2,nv,pvStar,0);
						for (i = 0; i < nv; i++)
							p[i] = pvStar[i];
						for (i = nv; i < ndec; i++)
							p[i] = 0;
						permutReco(p,orderPermu,ndec,1,tmpMat6);
						//Print("p (Alpha==1):\n");show_matrix(p,ndec,1);Print("\n");
					}
					else {
						FowSubL(Rv,gx,nv,uv,1);
						matTrans_vec(Yv,uv,nv,ml,vl);
						mat_vec(Yv,vl,nv,ml,wv);
						for (i = 0; i < nv; i++)
							wv[i] = wv[i] - uv[i];
						
						BacSubU(Rv, wv, nv, p, 0);

						for (i = 0; i < nv; i++)
							pvStar[i] = p[i];
						for (i = nv; i < ndec; i++)
							p[i]  = 0;		
						permutReco(p,orderPermu,ndec,1,tmpMat6);	
						//Print("p (Alpha==1):\n");show_matrix(p,ndec,1);Print("\n");
					}
                    
                    // 这里采用新的思路，即 alpha == 1 的时候就把 p 置为0
                    // 连续3次alpha为1就强制为0
                    if (alphaOneTimes > 2) {
                        for (i = 0; i < ndec; i++) {
                            p[i] = 0;
                            pvStar[i] = 0;
                        }
                    }
                    //Print("Force p to be zeros here.\n");
                }
            }
		}
	}
	iterPoint[0] = iter;

	//totalEnd = clock();	
	////totalTime += (float)(totalEnd - totalStart)/CLOCKS_PER_SEC;
	//totalTime += (totalEnd - totalStart);

	//fp_tT = fopen("totalTime.txt","w");
	//fp_iniT = fopen("initialTime.txt","w");
	//fp_abT = fopen("AddBoundTime.txt","w");
	//fp_agT = fopen("AddGeneralTime.txt","w");
	//fp_dbT = fopen("DeleteBoundTime.txt","w");
	//fp_dgT = fopen("DeleteGeneralTime.txt","w");
	//fp_alphaT = fopen("alphaTime.txt","w");
	//fp_plRtT = fopen("planeRotTime.txt","w");

	//fprintf(fp_tT,"%lf\n",totalTime);
	//fprintf(fp_iniT,"%lf\n",iniTime);
	//fprintf(fp_abT,"%lf\n",AdBdTime);
	//fprintf(fp_agT,"%lf\n",AdGeTime);
	//fprintf(fp_dbT,"%lf\n",DeBdTime);
	//fprintf(fp_dgT,"%lf\n",DeGeTime);
	//fprintf(fp_alphaT,"%lf\n",alphaTime);
	//fprintf(fp_plRtT,"%lf\n",planeRotTime);

	//Print("After running.\n");
	//Print("totalTime: %lf, iniTime: %lf, AdBdTime: %lf, PlRtTime: %lf", totalTime,iniTime,AdBdTime,planeRotTime);
	//Print(" AdGeTime: %lf, DeBdTime: %lf, DeGeTime: %lf, alphaTime: %lf\n", AdGeTime, DeBdTime, DeGeTime, alphaTime);

	//fclose(fp_tT); fclose(fp_iniT); fclose(fp_abT); fclose(fp_agT); 
	//fclose(fp_dbT); fclose(fp_dgT);	fclose(fp_alphaT); fclose(fp_plRtT);

	return flag;
}
