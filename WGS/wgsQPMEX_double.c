/*
 * Interface function between C and MATLAB via MEX
 *
 * Sep. 10, 2015
 *
 */


#include "mex.h"
#include "mathlib_double.c"
//#include <time.h>

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {


	double *H, *c; 
	double *AA, *lg;
	double *lx, *ux;  
	int32_T *wf, *wl; 
	int32_T *nf_p, *ml_p, *maxIter_p; 
	mwSize nf, ml, maxIter; 
	double *x; 
	mwSize ndec, nbc, ngc; 
	double *xStar;
	double *H_ori, *c_ori, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	double *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2;
	double *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	int32_T *isInWl, *orderPermu, *iter;

	size_t i;


	/* check for proper number of arguments */
    if(nrhs!= 40) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","40 inputs required.");
    }

	/* make sure the first input argument is type single */
	for (i = 0; i < 6; i++)
    if( !mxIsDouble(prhs[i]) || 
         mxIsComplex(prhs[i])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type single.");
    }

	if( !mxIsDouble(prhs[8]) || 
         mxIsComplex(prhs[8])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type single.");
    }

	if( !mxIsInt32(prhs[6]) || 
         mxIsComplex(prhs[6])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input wf must be type int32.");
    }



	/* create a pointer to the real data in the input matrix  */
    H = (double*)mxGetPr(prhs[0]);				c = (double*)mxGetPr(prhs[1]);			AA = (double*)mxGetPr(prhs[2]); 
	lg = (double*)mxGetPr(prhs[3]);				lx = (double*)mxGetPr(prhs[4]);			ux = (double*)mxGetPr(prhs[5]); 
	wf = (int32_T*)mxGetPr(prhs[6]);			wl = (int32_T*)mxGetPr(prhs[7]);		x = (double*)mxGetPr(prhs[8]);
	orderPermu = (int32_T*)mxGetPr(prhs[9]);	H_ori = (double*)mxGetPr(prhs[10]);		c_ori = (double*)mxGetPr(prhs[11]);
	Af = (double*)mxGetPr(prhs[12]);			Lv = (double*)mxGetPr(prhs[13]);
	Yv = (double*)mxGetPr(prhs[14]);			Rv = (double*)mxGetPr(prhs[15]);		pvStar = (double*)mxGetPr(prhs[16]);
	p = (double*)mxGetPr(prhs[17]);				gx = (double*)mxGetPr(prhs[18]);		isInWl = (int32_T*)mxGetPr(prhs[19]);
	uv = (double*)mxGetPr(prhs[20]);			vl = (double*)mxGetPr(prhs[21]);		wv = (double*)mxGetPr(prhs[22]);
	lambdal = (double*)mxGetPr(prhs[23]);		lambdaf = (double*)mxGetPr(prhs[24]);	lambda = (double*)mxGetPr(prhs[25]);
	P = (double*)mxGetPr(prhs[26]);				G = (double*)mxGetPr(prhs[27]);			tmpVec1 = (double*)mxGetPr(prhs[28]);
	tmpVec2 = (double*)mxGetPr(prhs[29]);		tmpMat1 = (double*)mxGetPr(prhs[30]);	tmpMat2 = (double*)mxGetPr(prhs[31]);
	tmpMat3 = (double*)mxGetPr(prhs[32]);		tmpMat4 = (double*)mxGetPr(prhs[33]);	tmpMat5 = (double*)mxGetPr(prhs[34]);
	tmpMat6 = (double*)mxGetPr(prhs[35]);    
	nf_p = (int32_T*)mxGetPr(prhs[36]);			ml_p = (int32_T*)mxGetPr(prhs[37]);		iter = (int32_T*)mxGetPr(prhs[38]);
	maxIter_p = (int32_T*)mxGetPr(prhs[39]);

	ndec = mxGetM(prhs[1]);
	ngc = mxGetM(prhs[3]);
	nbc = mxGetM(prhs[4]);
	nf = nf_p[0];
	ml = ml_p[0];
	maxIter = maxIter_p[0];

	/* create the output matrix */
	plhs[0] = mxCreateDoubleMatrix(ndec,1,mxREAL);		// Creat a double matrix

	/* get a pointer to the real data in the output matrix */
    xStar = mxGetPr(plhs[0]);

	/* call the computational routine */
	wgsQP(H, c, AA, lx, ux, lg, wf, wl, nf, ml, x, ndec, nbc, ngc,

		orderPermu, H_ori, c_ori, Af, Lv, Yv, Rv,
		pvStar, p, gx, isInWl,uv,vl,wv,
		lambdal,lambdaf,lambda, P,G,
		tmpVec1, tmpVec2, tmpMat1, tmpMat2, tmpMat3, tmpMat4, tmpMat5, tmpMat6,
		xStar,iter,maxIter);


}