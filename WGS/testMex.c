//*
// *	C code used to test mex funtion in MATLAB
// *	
// *
// *
// *
// *	Sep. 10
// *
// */

#include <stdio.h>
#include "mex.h"
#include "mathlib.h"

void computeTest(float *a, float *b, float *c, mwSize n) {

	mwSize i;
	for (i = 0; i < n; i++) {
		printf("a[%d] is %f\n",i,a[i]);
		printf("b[%d] is %f\n",i,b[i]);
		c[i] = a[i] + b[i];
	}

	vec_sub(a,b,n,c);

		

	printf("n is: %d\n",n);
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

	float *inVec1;
	float *inVec2;
	size_t ncols;
	float *outVec;

	/* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output required.");
    }

	/* make sure the first input argument is type double */
    if( !mxIsSingle(prhs[0]) || 
         mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type double.");
    }

	/* make sure the second input argument is type double */
    if( !mxIsSingle(prhs[1]) || 
         mxIsComplex(prhs[1])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type double.");
    }

	/* create a pointer to the real data in the input matrix  */
    inVec1 = mxGetPr(prhs[0]);

	/* get dimensions of the input matrix */
    ncols = mxGetN(prhs[0]);

	/* create a pointer to the real data in the input matrix  */
    inVec2 = mxGetPr(prhs[1]);

	/* create the output matrix */
    //plhs[0] = mxCreateDoubleMatrix(1,(mwSize)ncols,mxREAL);	// Create a double matrix
	plhs[0] = mxCreateNumericMatrix(1,(mwSize)ncols,mxSINGLE_CLASS,mxREAL); // Creat a single matrix


	/* get a pointer to the real data in the output matrix */
    outVec = mxGetPr(plhs[0]);

	/* call the computational routine */
    computeTest(inVec1,inVec2,outVec,(mwSize)ncols);

}
