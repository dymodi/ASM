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
#include "mathlib.h"

// length(tmpVec1) = max(ngc,ndec);
// length(tmpVec2) = ndec;
// size(tmpMat~) = [ndec, ndec];
// length(wf) = ndec;
// length(wl) = ndec;


int fake() {
//int main() {	

	//// Test data
	//// Data1  
	//float H[] = { 4.5267, -3.9095,  0.6937, -7.1302,  1.2138, -0.9079, 
	//		     -3.9095, 42.3583, -7.1494, 11.0149, -1.0405,  0.7782, 
	//			  0.6937, -7.1494,  3.3094, -2.8661,  0.3464, -0.2591, 
	//			 -7.1302, 11.0149, -2.8661, 41.4638, -6.8516,  5.1248, 
	//			  1.2138, -1.0405,  0.3464, -6.8516,  3.2103, -0.9053, 
	//			  -0.9079,  0.7782, -0.2591,  5.1248, -0.9053,  2.6771 };
	//float c[] = { 16.8930, -53.6424, 9.4920, -47.2980, 7.3800, -5.5200 };
	//float lx[] = {-2, -2, -2, -2, -2, -2};
	//float ux[] = {2, 2, 2, 2, 2, 2};
	//float lg[] = {-3, -3, -3, -3, -3, -3};
	//int nbc = 6;
	//int ndec = 6;
	//int ngc = 6;
	//int orderPermu[] = {0,1,2,3,4,5};
	//float *H_ori, *c_ori, *Av, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	//float *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2, *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	//int *isInWl;
	//float AA[] = {//-0.2460,  0.1840,  0,       0,       0,       0,
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
	////float x[] = {0,0,0,0,2,2};
	//float x[] = {2,-1,0,0,0,0};
	//int flag, maxLength;
	//float *xStar;

	//// Data 2 & 3
	//float H[] = { 7,  8.2,  8.7, 7,
	//			8.2,  9.8, 10.2, 8,
	//			8.7, 10.2, 11.7, 9,
	//			7,    8,    9,  10};
	//float c[] = {1,1,2,3};
	//float lx[] = {-4,-4,-4,-4};
	//float ux[] = {4,4,4,4};
	//float lg[] = {2,-3};
	////float lg[] = {2,1};
	//int nbc = 4;
	//int ndec = 4;
	//int ngc = 2;
	//int orderPermu[] = {0,1,2,3};
	//float *H_ori, *c_ori, *Av, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	//float *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2, *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	//int *isInWl;
	//float AA[] = {1,1,0,0,0,1,0,1};
	////float AA[] = {1,1,0,0,1,0,1,0};
	//int wf[] = {3,0,0,0};
	////int wf[] = {4,0,0,0};
	//int wl[] = {1,2,0,0};
	////int wl[] = {0,0,0,0};
	//int nf = 1;
	////int nf = 1;
	//int ml = 2;
	////int ml = 0;
	//float x[] = {2, 0, -4, -3};
	////float x[] = {3, 0, 0, -4};
	//int flag, maxLength;
	//float *xStar;


	// C-failed data 1
	int i;
	int ndec = 5;
	int nbc = 1;
	int ngc = 15;
	float *H_ori, *c_ori, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	float *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2, *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	int *isInWl, *wf, *wl, *orderPermu;
	int nf = 0;
	int ml = 0;
	float *H, *c, *AA, *lg, *lx, *ux, *x;
	float tmp;
	int flag, maxLength;
	float *xStar;
	int iterPoint[1] = {0};
	int maxIter = 1000;

	wf = (int*)calloc(ndec,sizeof(int));
	wl = (int*)calloc(ndec,sizeof(int));
	orderPermu = (int*)calloc(ndec,sizeof(int));

	H = (float*)calloc(ndec*ndec,sizeof(float));
	c = (float*)calloc(ndec*1,sizeof(float));
	AA = (float*)calloc(ngc*ndec,sizeof(float));
	lg = (float*)calloc(ngc*1,sizeof(float));
	lx = (float*)calloc(nbc*1,sizeof(float));
	ux = (float*)calloc(nbc*1,sizeof(float));
	x = (float*)calloc(ndec*1,sizeof(float));

	freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\H.txt","r",stdin);
	for (i = 0; i < ndec*ndec; i++) {
		scanf("%f\n",&tmp);
		H[i] = (float)tmp;
	}
	//show_matrix(H,1,ndec);
	
	freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\c.txt","r",stdin);
	for (i = 0; i < ndec; i++) {
		scanf("%f\n",&tmp);
		c[i] = (float)tmp;
	}
	//show_matrix(c,1,ndec);
	freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\AA.txt","r",stdin);
	for (i = 0; i < ngc*ndec; i++) {
		scanf("%f\n",&tmp);
		AA[i] = (float)tmp;
	}
	//show_matrix(AA,1,ndec);
	freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\lg.txt","r",stdin);
	for (i = 0; i < ngc; i++) {
		scanf("%f\n",&tmp);
		lg[i] = (float)tmp;
	}
	//show_matrix(lg,1,ngc);
	
	freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\lx.txt","r",stdin);
	for (i = 0; i < nbc; i++) {
		scanf("%f\n",&tmp);
		lx[i] = (float)tmp;
	}
	//show_matrix(lx,1,ndec);
	freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\ux.txt","r",stdin);
	for (i = 0; i < nbc; i++) {
		scanf("%f\n",&tmp);
		ux[i] = (float)tmp;
	}
	//show_matrix(ux,1,ndec);
	freopen("D:\\Users\\Yi\\Documents\\Visual Studio 2010\\Projects\\wgsQP\\wgsQP\\testData\\data1\\x.txt","r",stdin);
	for (i = 0; i < ndec; i++) {
		scanf("%f\n",&tmp);
		x[i] = (float)tmp;
	}
	//show_matrix(x,1,ndec);

	
	xStar = (float*)calloc(ndec,sizeof(float));
	H_ori = (float*)calloc(ndec*ndec,sizeof(float));
	c_ori = (float*)calloc(ndec,sizeof(float));
	Af = (float*)calloc(ndec*ndec,sizeof(float));
	Lv = (float*)calloc(ndec*ndec,sizeof(float));
	Yv = (float*)calloc(ndec*ndec,sizeof(float));
	Rv = (float*)calloc(ndec*ndec,sizeof(float));
	pvStar = (float*)calloc(ndec,sizeof(float));
	p = (float*)calloc(ndec*ndec,sizeof(float));
	gx = (float*)calloc(ndec,sizeof(float));
	isInWl = (int*)calloc(ngc,sizeof(int));
	
	uv = (float*)calloc(ndec,sizeof(float));
	vl = (float*)calloc(ndec,sizeof(float));
	wv = (float*)calloc(ndec,sizeof(float));
	tmpMat1 = (float*)calloc(ndec*ndec,sizeof(float));
	tmpMat2 = (float*)calloc(ndec*ndec,sizeof(float));
	tmpMat3 = (float*)calloc(ndec*ndec,sizeof(float));
	tmpMat4 = (float*)calloc(ndec*ndec,sizeof(float));
	tmpMat5 = (float*)calloc(ndec*ndec,sizeof(float));
	tmpMat6 = (float*)calloc(ndec*ndec,sizeof(float));
	lambdal = (float*)calloc(ndec,sizeof(float));
	lambdaf = (float*)calloc(ndec,sizeof(float));
	lambda = (float*)calloc(ndec,sizeof(float));
	P = (float*)calloc(ndec*ndec,sizeof(float));
	G = (float*)calloc(4,sizeof(float));
	tmpVec2 = (float*)calloc(ndec,sizeof(float));
	if (ndec > ngc)
		maxLength = ndec;
	else
		maxLength = ngc;
	tmpVec1 = (float*)calloc(maxLength,sizeof(float));
	

	printf("Enter main\n");
		

	flag = wgsQP(H, c, AA, lx, ux, lg, 
		wf, wl, nf, ml, x, ndec, nbc, ngc,
		orderPermu, H_ori, c_ori, Af, Lv, Yv, Rv,
		pvStar, p, gx, isInWl,uv,vl,wv,
		lambdal,lambdaf,lambda, P,G,
		tmpVec1, tmpVec2, tmpMat1, tmpMat2, tmpMat3, tmpMat4, tmpMat5, tmpMat6,
		xStar,iterPoint, maxIter);	


	printf("xStar is:\n");show_matrix(xStar,1,ndec);
	putchar('\n');

	//free(H);free(c);free(AA);free(lg);free(lx);free(ux);free(x);free(xStar);

}