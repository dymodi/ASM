// Interface function between C and MATLAB via MEX
// Primal Active Set Method
// Mar. 27,  2016
// Yi Ding

#include "mex.h"
#include "mathlib_double.c"

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    double *H, *c, *invH, *x, *xStar; 
    int32_T *w, *iter_p, *wSize_p, *maxIter_p;
    mwSize mc, ndec, maxIter, wSize;
    double *H_ori, *c_ori, *invH_ori, *A, *b, *Aw, *bw, *p, *gx; 
    double *lambda, *tmpVec1, *tmpVec2;
    double *tmpMat1, *tmpMat2, *tmpMat3, *tmpMat4;
    int32_T iter, flag;
    mwSignedIndex dims[2];
    
    size_t i;
    
    /* check for proper number of arguments */
    if(nrhs!= 24) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","24 inputs required.");
    }
    
    /* check for type errors */
    if( !mxIsDouble(prhs[1]) || 
         mxIsComplex(prhs[1])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type double.");
    }
    
    /* create a pointer to the real data in the input matrix  */
    H = (double*)mxGetPr(prhs[0]);
    invH = (double*)mxGetPr(prhs[1]);
    c = (double*)mxGetPr(prhs[2]);
    A = (double*)mxGetPr(prhs[3]); 
    b = (double*)mxGetPr(prhs[4]);
    x = (double*)mxGetPr(prhs[5]);
    w = (int32_T*)mxGetPr(prhs[6]);
    wSize_p = (int32_T*)mxGetPr(prhs[7]);
    Aw = (double*)mxGetPr(prhs[8]);
    bw = (double*)mxGetPr(prhs[9]);
    H_ori = (double*)mxGetPr(prhs[10]);
    invH_ori = (double*)mxGetPr(prhs[11]);
    c_ori = (double*)mxGetPr(prhs[12]);
    p = (double*)mxGetPr(prhs[13]);
    gx = (double*)mxGetPr(prhs[14]);
    lambda = (double*)mxGetPr(prhs[15]);
    tmpVec1 = (double*)mxGetPr(prhs[16]);
    tmpVec2 = (double*)mxGetPr(prhs[17]);
    tmpMat1 = (double*)mxGetPr(prhs[18]);
    tmpMat2 = (double*)mxGetPr(prhs[19]);
    tmpMat3 = (double*)mxGetPr(prhs[20]);
    tmpMat4 = (double*)mxGetPr(prhs[21]);
    iter_p = (int32_T*)mxGetPr(prhs[22]);
    maxIter_p = (int32_T*)mxGetPr(prhs[23]);
    
    ndec = mxGetM(prhs[2]);
    mc = mxGetM(prhs[4]);
    maxIter = maxIter_p[0];
    wSize = wSize_p[0];
    
    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix(ndec,1,mxREAL);		// Creat a double matrix
    dims[0] = 1;
    dims[1] = 1;
    plhs[1] = mxCreateNumericArray(2,dims,mxUINT32_CLASS,mxREAL);
    
    /* get a pointer to the real data in the output matrix */
    xStar = mxGetPr(plhs[0]);  
    iter_p = mxGetPr(plhs[1]);
    
    /* call the computational routine */
    flag = ASM (H, invH, c, A, b, 
		x, ndec, mc, w, wSize,
		Aw, bw,
		H_ori, invH_ori, c_ori, p, gx, 
		lambda, tmpVec1, tmpVec2, 
		tmpMat1, tmpMat2, tmpMat3,tmpMat4,
		xStar, iter_p, maxIter);
}