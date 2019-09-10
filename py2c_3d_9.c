
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coeffs.h"

int main(){
	
	// Assigning point p = (1 -2 4)^T, x = (1 2 2)^T (x is point on plane)
	double** p = createMat(3,1); double** x = createMat(3,1);
	*p[0] = 1; *p[1] = -2; *p[2] = 4;
	*x[0] = 1; *x[1] =  2; *x[2] = 2;
	
	// Assigning normal vectors of given planes
	double** n1 = createMat(3,1); double** n2 = createMat(3,1);
	*n1[0] = 1; *n1[1] = -1; *n1[2] = 2;
	*n2[0] = 2; *n2[1] = -2; *n2[2] = 1;
	
	// Matrix for cross product
	double** n1o = createMat(3,3);
	n1o[0][0] = 0;         n1o[0][1] = -(*n1[2]); n1o[0][2] = *n1[1];
	n1o[1][0] = *n1[2];    n1o[1][1] = 0;         n1o[1][2] = -(*n1[0]);
	n1o[2][0] = -(*n1[1]); n1o[2][1] = *n1[0];    n1o[2][2] = 0;
	
	// Normal vector of the required plane
	double** n = matmul(n1o, n2, 3,3,1);
	
	// Finding distance by applying formula
	double dist = abs(**matmul(transpose(linalg_sub(p,x,3,1),3,1), n, 1,3,3)) / linalg_norm(n,3);
	
	// Disposing resources
	free(p); free(x); free(n1); free(n2); free(n1o); free(n);
	
	printf("Distace = %lf",dist);
	
	return 0;
}
