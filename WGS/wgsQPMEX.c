
#define Print mexPrintf

#include "mex.h"
#include "mathlib.c"


/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {


	float *H, *c; 
	float *AA, *lg;
	float *lx, *ux;  
	int32_T *wf, *wl; 
	int32_T *nf_p, *ml_p, *maxIter_p; 
	mwSize nf, ml, maxIter; 
	float *x; 
	mwSize ndec, nbc, ngc; 
	float *xStar;
	float *H_ori, *c_ori, *Af, *Lv, *Yv, *Rv, *pvStar, *p, *gx, *uv, *vl, *wv, *P, *G; 
	float *lambdaf, *lambdal, *lambda, *tmpVec1, *tmpVec2;
	float *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4, *tmpMat5, *tmpMat6;
	int32_T *isInWl, *orderPermu, *iter;

	size_t i;


	/* check for proper number of arguments */
    if(nrhs!= 40) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","40 inputs required.");
    }

	/* make sure the first input argument is type single */
	for (i = 0; i < 6; i++)
    if( !mxIsSingle(prhs[i]) || 
         mxIsComplex(prhs[i])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type single.");
    }

	if( !mxIsSingle(prhs[8]) || 
         mxIsComplex(prhs[8])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type single.");
    }

	if( !mxIsInt32(prhs[6]) || 
         mxIsComplex(prhs[6])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input wf must be type int32.");
    }

	/* create a pointer to the real data in the input matrix  */
    H = (float*)mxGetPr(prhs[0]);				c = (float*)mxGetPr(prhs[1]);		AA = (float*)mxGetPr(prhs[2]); 
	lg = (float*)mxGetPr(prhs[3]);				lx = (float*)mxGetPr(prhs[4]);		ux = (float*)mxGetPr(prhs[5]); 
	wf = (int32_T*)mxGetPr(prhs[6]);			wl = (int32_T*)mxGetPr(prhs[7]);	x = (float*)mxGetPr(prhs[8]);
	orderPermu = (int32_T*)mxGetPr(prhs[9]);	H_ori = (float*)mxGetPr(prhs[10]);	c_ori = (float*)mxGetPr(prhs[11]);
	Af = (float*)mxGetPr(prhs[12]);		Lv = (float*)mxGetPr(prhs[13]);
	Yv = (float*)mxGetPr(prhs[14]);				Rv = (float*)mxGetPr(prhs[15]);		pvStar = (float*)mxGetPr(prhs[16]);
	p = (float*)mxGetPr(prhs[17]);				gx = (float*)mxGetPr(prhs[18]);		isInWl = (int32_T*)mxGetPr(prhs[19]);
	uv = (float*)mxGetPr(prhs[20]);				vl = (float*)mxGetPr(prhs[21]);		wv = (float*)mxGetPr(prhs[22]);
	lambdal = (float*)mxGetPr(prhs[23]);		lambdaf = (float*)mxGetPr(prhs[24]);lambda = (float*)mxGetPr(prhs[25]);
	P = (float*)mxGetPr(prhs[26]);				G = (float*)mxGetPr(prhs[27]);		tmpVec1 = (float*)mxGetPr(prhs[28]);
	tmpVec2 = (float*)mxGetPr(prhs[29]);		tmpMat1 = (float*)mxGetPr(prhs[30]);tmpMat2 = (float*)mxGetPr(prhs[31]);
	tmpMat3 = (float*)mxGetPr(prhs[32]);		tmpMat4 = (float*)mxGetPr(prhs[33]);tmpMat5 = (float*)mxGetPr(prhs[34]);
	tmpMat6 = (float*)mxGetPr(prhs[35]);    
	nf_p = (int32_T*)mxGetPr(prhs[36]);			ml_p = (int32_T*)mxGetPr(prhs[37]);	iter = (int32_T*)mxGetPr(prhs[38]);
	maxIter_p = (int32_T*)mxGetPr(prhs[39]);

	ndec = mxGetM(prhs[1]);
	ngc = mxGetM(prhs[3]);
	nbc = mxGetM(prhs[4]);
	nf = nf_p[0];
	ml = ml_p[0];
	maxIter = maxIter_p[0];

	//Print("AA (Before enter function) is:\n");
	//for (i = 0; i < ndec; i++)
	//	Print("%f  ",AA[i]);

	/* create the output matrix */
	plhs[0] = mxCreateNumericMatrix(ndec,1,mxSINGLE_CLASS,mxREAL); // Creat a single matrix

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