//*==========================================================
// * wgsQP.c - active-set method using Weighted Gram-Schmidt for update
// *
// * Solves an convex QP problem with linear (and box) constraints 
// *  
// * The calling syntax is:
// *
// *		wgsQP(H,c,AA,lx,ux,lg,wf,wl,nf,ml,x,xStar)
// *
// * Attention:
// *	1 The index of constraints in wf and wl is from 1 to n (not 0 to n-1)
// *	2 The index in orderPermu is from 0 to n-1 (not 1 to n)
// *
// * This is an implementation of the Matlab function wgsQP.m in C code
// * Copyright Yi Ding 
// * Date	September 1, 2015
// *
// * Note that matrices are stored in arraies by rows (one row after another)
// *========================================================*/
//
//% Matrix dimension 
//% H:  ndec*ndec;    % ndec = nv + nf;    
//% R:  ndec*ndec;
//% Rv: nv*nv;
//% Rf: nf*nf;
//% C:  t*ndec;       % t = nf+ml;
//% If: nf*nf;
//% Av: ml*nv;
//% Af: ml*nf;
//% Lv: ml*ml;
//% Yv: nv*ml;
//% gx:  ndec*1;
//% uv: nv*1;
//% wv: nv*1;
//% vl: ml*1;

// Variables declarations
// nf:	 number of bound constraints in the working set
// ml:	 number of general constraints in the working set
// ndec: number of decision variables (x)
// nbc:	 number of all bound constraints
// ngc:	 number of all general constraints

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mathlib_double.h"

// length(tmpVec1) = max(ngc,ndec);
// length(tmpVec2) = ndec;
// size(tmpMat~) = [ndec, ndec];
// length(wf) = ndec;
// length(wl) = ndec;




//int fake() {
int main() {	

	//// Test data
	//// Data1  
	//double H[] = { 4.5267, -3.9095,  0.6937, -7.1302,  1.2138, -0.9079, 
	//		     -3.9095, 42.3583, -7.1494, 11.0149, -1.0405,  0.7782, 
	//			  0.6937, -7.1494,  3.3094, -2.8661,  0.3464, -0.2591, 
	//			 -7.1302, 11.0149, -2.8661, 41.4638, -6.8516,  5.1248, 
	//			  1.2138, -1.0405,  0.3464, -6.8516,  3.2103, -0.9053, 
	//			  -0.9079,  0.7782, -0.2591,  5.1248, -0.9053,  2.6771 };
	//double c[] = { 16.8930, -53.6424, 9.4920, -47.2980, 7.3800, -5.5200 };
	//double invH[] = { 0.313898329,  0.01946685,  0.0189869,  0.04721292, -0.0112787,  0.00843874,
	//				  0.019466851,  0.03949486,  0.0791899, -0.0042709,  -0.0100907,  0.00754907,
	//                  0.018986944,  0.07918987,  0.4827451,  0.01547409, -0.0004751,  0.00035868,
	//				  0.047212918, -0.0042709,   0.0154741,  0.05494788,  0.07958196,-0.0595248,
	//                 -0.011278695, -0.0100907,  -0.0004751,  0.07958196,  0.4854597,  0.01088291,
	//                  0.008438737,  0.00754907,  0.0003587, -0.0595248,   0.01088291, 0.4918698};
	//double lx[] = {-2, -2, -2, -2, -2, -2};
	//double ux[] = {2, 2, 2, 2, 2, 2};
	//double lg[] = {-3, -3, -3, -3, -3, -3};
	//int nbc = 6;
	//int ndec = 6;
	//int ngc = 6;
	//int orderPermu[] = {0,1,2,3,4,5};
	//double *H_ori, *c_ori, *invH_ori, *Av, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	//double *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2, *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	//int *isInWl;
	//double AA[] = {//-0.2460,  0.1840,  0,       0,       0,       0,
	//		 -1,  1,  0,       0,       0,       0,
	//	     -0.0704,  1.3926, -0.2460,  0.1840,  0,       0,
	//	     -0.2467,  0.2115, -0.0704,  1.3926, -0.2460,  0.1840,
	//	     // 0.2460, -0.1840,  0,       0,       0,       0,
	//		 1,  -1,  0,       0,       0,       0,
	//		0.0704, -1.3926,  0.2460, -0.1840,  0,       0,
	//		0.2467, -0.2115,  0.0704, -1.3926,  0.2460, -0.1840 };
	////int wf[] = {11,12,0,0,0,0};
	//int wf[] = {7,0,0,0,0,0};
	////int wl[] = {0,0,0,0,0,0};	// wl should be empty, but empty initialization is not allowed
	//int wl[] = {1,0,0,0,0,0};	
	////int nf = 2;
	//int nf = 1;
	////int ml = 0;
	//int ml = 1;
	//double x[] = {0,0,0,0,2,2};
	////double x[] = {2,-1,0,0,0,0};
	//int flag, maxLength;
	//double *xStar;
	//int mc = ngc + nbc * 2;
	//double *A, *b, *Aw, *bw;
	//int i;
	//int *iterPoint;
	//int w[] = {2,3,0,0,0,0};

	// Data 2 & 3
	double H[] = { 7,  8.2,  8.7, 7,
				8.2,  9.8, 10.2, 8,
				8.7, 10.2, 11.7, 9,
				7,    8,    9,  10};
	double c[] = {1,1,2,3};
	double invH[] = {        10,-6.666666667,-1.111111111,-0.66666667,
					-6.66666667, 5.555555556,-0.185185185, 0.38888889,
					-1.11111111,-0.185185185, 1.172839506,-0.12962963,
					-0.66666667, 0.388888889,-0.12962963,  0.37222222};
	double lx[] = {-4,-4,-4,-4};
	double ux[] = {4,4,4,4};
	double lg[] = {2,-3};
	//double lg[] = {2,1};
	int nbc = 4;
	int ndec = 4;
	int ngc = 2;
	int orderPermu[] = {0,1,2,3};
	double *H_ori, *c_ori, *invH_ori, *Av, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	double *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2, *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	int *isInWl;
	double AA[] = {1,1,0,0,0,1,0,1};
	//double AA[] = {1,1,0,0,1,0,1,0};
	int wf[] = {3,0,0,0};
	//int wf[] = {4,0,0,0};
	int wl[] = {1,2,0,0};
	//int wl[] = {0,0,0,0};
	int nf = 1;
	//int nf = 1;
	int ml = 2;
	//int ml = 0;
	double x[] = {2, 0, -4, -3};
	//double x[] = {3, 0, 0, -4};
	int flag, maxLength, i;
	double *xStar;
	int mc = ngc + nbc * 2;
	double *A, *b, *Aw, *bw;
	int *iterPoint;
	int w[] = {3,9,10,0};


	//// C-failed data 1
	//int i;
	//int ndec = 160;
	//int nbc = 160;
	//int ngc = 800;
	//double *H_ori, *c_ori, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	//double *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2, *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	//int *isInWl, *wf, *wl, *orderPermu;
	//int nf = 0;
	//int ml = 0;
	//double *H, *c, *AA, *lg, *lx, *ux, *x;
	//double tmp;
	//int flag, maxLength;
	//double *xStar;
	//int *iterPoint;
	//int maxIter = 300;

	//wf = (int*)calloc(ndec,sizeof(int));
	//wl = (int*)calloc(ndec,sizeof(int));
	//orderPermu = (int*)calloc(ndec,sizeof(int));

	//H = (double*)calloc(ndec*ndec,sizeof(double));
	//c = (double*)calloc(ndec*1,sizeof(double));
	//AA = (double*)calloc(ngc*ndec,sizeof(double));
	//lg = (double*)calloc(ngc*1,sizeof(double));
	//lx = (double*)calloc(nbc*1,sizeof(double));
	//ux = (double*)calloc(nbc*1,sizeof(double));
	//x = (double*)calloc(ndec*1,sizeof(double));
	//iterPoint = (int*)calloc(1,sizeof(int));

	//freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\H.txt","r",stdin);
	//for (i = 0; i < ndec*ndec; i++) {
	//	scanf("%lf\n",&tmp);
	//	H[i] = (double)tmp;
	//}
	////show_matrix(H,1,ndec);
	//freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\c.txt","r",stdin);
	//for (i = 0; i < ndec; i++) {
	//	scanf("%lf\n",&tmp);
	//	c[i] = (double)tmp;
	//}
	////show_matrix(c,1,ndec);
	//freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\AA.txt","r",stdin);
	//for (i = 0; i < ngc*ndec; i++) {
	//	scanf("%lf\n",&tmp);
	//	AA[i] = (double)tmp;
	//}
	////show_matrix(AA,1,ndec);
	//freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\lg.txt","r",stdin);
	//for (i = 0; i < ngc; i++) {
	//	scanf("%lf\n",&tmp);
	//	lg[i] = (double)tmp;
	//}
	////show_matrix(lg,1,ngc);	
	//freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\lx.txt","r",stdin);
	//for (i = 0; i < nbc; i++) {
	//	scanf("%lf\n",&tmp);
	//	lx[i] = (double)tmp;
	//}
	////show_matrix(lx,1,ndec);
	//freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\ux.txt","r",stdin);
	//for (i = 0; i < nbc; i++) {
	//	scanf("%lf\n",&tmp);
	//	ux[i] = (double)tmp;
	//}
	////show_matrix(ux,1,ndec);
	//freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\x.txt","r",stdin);
	//for (i = 0; i < ndec; i++) {
	//	scanf("%lf\n",&tmp);
	//	x[i] = (double)tmp;
	//}
	////show_matrix(x,1,ndec);
	//
	//xStar = (double*)calloc(ndec,sizeof(double));
	H_ori = (double*)calloc(ndec*ndec,sizeof(double));
	c_ori = (double*)calloc(ndec,sizeof(double));
	invH_ori = (double*)calloc(ndec*ndec,sizeof(double));
	//Af = (double*)calloc(ndec*ndec,sizeof(double));
	//Lv = (double*)calloc(ndec*ndec,sizeof(double));
	//Yv = (double*)calloc(ndec*ndec,sizeof(double));
	//Rv = (double*)calloc(ndec*ndec,sizeof(double));
	//pvStar = (double*)calloc(ndec,sizeof(double));
	p = (double*)calloc(ndec*ndec,sizeof(double));
	gx = (double*)calloc(ndec,sizeof(double));
	//isInWl = (int*)calloc(ngc,sizeof(int));
	//uv = (double*)calloc(ndec,sizeof(double));
	//vl = (double*)calloc(ndec,sizeof(double));
	//wv = (double*)calloc(ndec,sizeof(double));
	//lambdal = (double*)calloc(ndec,sizeof(double));
	//lambdaf = (double*)calloc(ndec,sizeof(double));
	lambda = (double*)calloc(ndec,sizeof(double));
	//P = (double*)calloc(ndec*ndec,sizeof(double));
	//G = (double*)calloc(4,sizeof(double));	
	//if (ndec > ngc)
	//	maxLength = ndec;
	//else
	//	maxLength = ngc;
	

	// For ASM debug
	if (ndec > mc)
		maxLength = ndec;
	else
		maxLength = mc;
	tmpMat1 = (double*)calloc((ndec+1)*ndec,sizeof(double));
	tmpMat2 = (double*)calloc(ndec*ndec,sizeof(double));
	tmpMat3 = (double*)calloc(ndec*ndec,sizeof(double));
	tmpMat4 = (double*)calloc(ndec*ndec,sizeof(double));
	tmpMat5 = (double*)calloc(ndec*ndec,sizeof(double));
	tmpMat6 = (double*)calloc(ndec*ndec,sizeof(double));
	tmpVec1 = (double*)calloc(maxLength,sizeof(double));
	tmpVec2 = (double*)calloc(maxLength,sizeof(double));
	A = (double*)calloc(mc*ndec,sizeof(double));
	Aw = (double*)calloc(ndec*ndec,sizeof(double));	
	b = (double*)calloc(mc,sizeof(double));
	bw = (double*)calloc(ndec,sizeof(double));
	iterPoint = (int*)calloc(1,sizeof(double));
	xStar = (double*)calloc(ndec,sizeof(double));

	for (i = 0; i < ndec; i++) {
		A[i*ndec+i] = 1;
		A[(i+ndec)*ndec+i] = -1;
	}
	for (i = ndec*ndec*2; i<ndec*mc; i++)
		A[i] = AA[i-ndec*ndec*2];
	for (i = 0; i < nbc; i++) {
		b[i] = lx[i];
		b[i+nbc] = -ux[i];
	}
	for (i = 0; i < ngc; i++)
		b[i+2*nbc] = lg[i];

	//printf("Enter main\n");
	//	
	//flag = wgsQP(H, c, AA, lx, ux, lg, 
	//	wf, wl, nf, ml, x, ndec, nbc, ngc,
	//	orderPermu, H_ori, c_ori, Af, Lv, Yv, Rv,
	//	pvStar, p, gx, isInWl,uv,vl,wv,
	//	lambdal,lambdaf,lambda, P,G,
	//	tmpVec1, tmpVec2, tmpMat1, tmpMat2, tmpMat3, tmpMat4, tmpMat5, tmpMat6,
	//	xStar,iterPoint,maxIter) ;	

	//flag = gauss(H,6,6,tmpVec1);
	//printf("Gauss is:\n");show_matrix(H,6,6);putchar('\n');

	// Debug the primal ASM algorithm
	flag = ASM (H, invH, c, A, b, 
		x, ndec, mc, w, 3,
		Aw, bw,
		H_ori, invH_ori, c_ori, p, gx, 
		lambda, tmpVec1, tmpVec2, 
		tmpMat1, tmpMat2, tmpMat3,tmpMat4,
		xStar, iterPoint, 300);

	printf("xStar is:\n");show_matrix(xStar,1,ndec);putchar('\n');
	

	//free(H);free(c);free(AA);free(lg);free(lx);free(ux);free(x);free(xStar);

}