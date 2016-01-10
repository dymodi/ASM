
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mathlib_double.h"
#include "mathlib.h"

//#define Var double	// Test Var
#define Var float		// Test float

//int fake() {
int main() {	

	Var L[] = {1,0,0,1,2,0,1,2,3};
	Var b[] = {4,5,6};
	int n = 3;
	int i;
	Var y[] = {0,0,0};
	//Var R[] = {2.1276, -1.8375, 0.3260, -3.3513, 0, 6.2435, -1.0491, 0.7779, 0, 0, 1.4500, -0.6602, 0, 0, 0, 5.4029};
	Var *invR;
	Var tmp;
	//Var A[] = {1,2,4,4,7,6,5,8,4,10,11,13};
	Var A[] = {0.0000,0.0000,-0.8861, 0.8861, -0.1624, 0.1624, -0.0000, 0.0000, 0.0194, -0.0194, -0.0718, 0.0718, -0.2233, 0.2233, -0.1344, 0.1344, 0.0837, -0.0837, 0.0000, -0.0000, -0.1570, 0.1570 };

	Var *Q, *R, *Qtrans;
	Q = (Var*)calloc(121,sizeof(Var));
	R = (Var*)calloc(121,sizeof(Var));
	Qtrans = (Var*)calloc(121,sizeof(Var));

	//invR = (Var*)calloc(16, sizeof(Var));
	//uInv(R, 4, invR);
	//tmp = norm(b, 3);

	
	//qr(A, 4, 3, Q, R);
	//printf("Q is:\n"); show_matrix(Q,4,4); putchar('\n');
	//printf("R is:\n"); show_matrix(A,3,4); putchar('\n');
	//mat_mul(Q,4,4,A,3,R);
	//printf("A is:\n"); show_matrix(R,3,4); putchar('\n');
	//mat_mulTrans(Q,4,4,Q,4,R);
	//printf("I is:\n"); show_matrix(R,4,4); putchar('\n');

	printf("A is:\n"); show_matrix(A,2,11); putchar('\n');
	gs_m(A, 11, 2, Q, R);
	printf("Q is:\n"); show_matrix(Q,2,11); putchar('\n');
	printf("R is:\n"); show_matrix(R,2,2); putchar('\n');
	mat_mul(Q,11,2,R,2,A);
	printf("A is:\n"); show_matrix(A,2,11); putchar('\n');

	printf("A is:\n"); show_matrix(A,2,11); putchar('\n');
	qr(A, 11, 2, Q, R);
	printf("Q is:\n"); show_matrix(Q,11,11); putchar('\n');
	printf("R is:\n"); show_matrix(A,2,11); putchar('\n');
	mat_mul(Q,11,11,R,2,A);
	printf("A is:\n"); show_matrix(A,2,11); putchar('\n');


	i = qrdcmp(A, 11, 2, Q, R);
	printf("qrdcmp: %d\n",i);
	show_matrix(Q,100,1);
	show_matrix(R,100,1);

	//for (i = 0; i < 16; i ++)
	//	Qtrans[i] = Q[i];
	//transpose(Qtrans,4,4);
	//mat_mul(Qtrans,4,4,Q,4,A);
	//printf("Q'*Q is:\n"); show_matrix(A,4,4); putchar('\n');

	//printf("%f\b",tmp);

	////FowSubL(L, b, n, y);
	//transpose(L,3,3);

	//BacSubU(L, b, n, y);
	//

	//matTrans_vec(L,b,3,3,Q);
	//show_matrix(Q,3,3);
	//transpose(L,3,3);
	//mat_vec(L,b,3,3,Q);
	//show_matrix(Q,3,3);

	printf("debug!\n");
}