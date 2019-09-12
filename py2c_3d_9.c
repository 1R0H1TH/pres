
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coeffs.h"

typedef double** MATRIX; typedef double** VECTOR;

MATRIX meshgrid(int len, int start, int stepX, int stepY);
void saveMat(MATRIX mat, char*str, int m, int n);
MATRIX *createPlane(VECTOR n, double c, int meshLen);
VECTOR foot(VECTOR n, double c_, VECTOR p);

int main(){
	
	// Assigning point p = (1 -2 4)^T, x = (1 2 2)^T (x is point on plane)
	MATRIX p = createMat(3,1); MATRIX x = createMat(3,1);
	*p[0] = 1; *p[1] = -2; *p[2] = 4;
	*x[0] = 1; *x[1] =  2; *x[2] = 2;
	
	// Assigning normal vectors of given planes
	VECTOR n1 = createMat(3,1); VECTOR n2 = createMat(3,1);
	*n1[0] = 1; *n1[1] = -1; *n1[2] = 2;
	*n2[0] = 2; *n2[1] = -2; *n2[2] = 1;
	double c1 = 3; double c2 = -12;
	
	// Matrix for cross product
	MATRIX n1o = createMat(3,3);
	n1o[0][0] = 0;         n1o[0][1] = -(*n1[2]); n1o[0][2] = *n1[1];
	n1o[1][0] = *n1[2];    n1o[1][1] = 0;         n1o[1][2] = -(*n1[0]);
	n1o[2][0] = -(*n1[1]); n1o[2][1] = *n1[0];    n1o[2][2] = 0;
	
	// Normal vector of the required plane
	VECTOR n = matmul(n1o, n2, 3,3,1);
	
	double c = **matmul(transpose(x,3,1), n, 1,3,1);
	
	// Finding distance by applying formula
	double dist = abs(**matmul(transpose(linalg_sub(p,x,3,1),3,1), n, 1,3,3)) / linalg_norm(n,3);
	
	printf("Plane equation : (%d %d %d)x = %d\n", (int)*n[0], (int)*n[1], (int)*n[2], (int)c);
	printf("Distace = %lf\n\n",dist);
	
	MATRIX foo = foot(n, c, p);
	print(foo,3,1);
	
	int meshLen = 10;
	
	MATRIX *plane1 = createPlane(n1, c1, meshLen);
	saveMat(plane1[0], "data/meshX1.dat", meshLen, meshLen);
	saveMat(plane1[1], "data/meshY1.dat", meshLen, meshLen);
	saveMat(plane1[2], "data/meshZ1.dat", meshLen, meshLen);
	
	MATRIX *plane2 = createPlane(n2, c2, meshLen);
	saveMat(plane2[0], "data/meshX2.dat", meshLen, meshLen);
	saveMat(plane2[1], "data/meshY2.dat", meshLen, meshLen);
	saveMat(plane2[2], "data/meshZ2.dat", meshLen, meshLen);
	
	*n[1] += *n[2]; *n[2] = *n[1] - *n[2]; *n[1] -= *n[2]; meshLen += 10;
	
	MATRIX *plane3 = createPlane(n, c, meshLen);
	saveMat(plane3[0], "data/meshX3.dat", meshLen, meshLen);
	saveMat(plane3[1], "data/meshZ3.dat", meshLen, meshLen);
	saveMat(plane3[2], "data/meshY3.dat", meshLen, meshLen);
	
	// Disposing resources
	free(p); free(x); free(n1); free(n2); free(n1o); free(n); free(plane1); free(plane2); free(plane3);
	return 0;
}

MATRIX meshgrid(int len, int start, int stepX, int stepY){
	double ** ret = createMat(len, len);
	for (int i=0; i<len; i++)
		for (int j=0; j<len; j++){
			ret[i][j] = start + i*stepY + j*stepX;
		}
	return ret;
}
MATRIX *createPlane(VECTOR n, double c, int meshLen){
	MATRIX* ret = (MATRIX*)malloc(3*sizeof(MATRIX));
	ret[0] = meshgrid(meshLen, -meshLen/2, 2, 0);
	ret[1] = meshgrid(meshLen, -meshLen/2, 0, 2);
	ret[2] = meshgrid(meshLen, -meshLen/2, 0, 0);
	
	for (int i=0; i<meshLen; i++)
		for (int j=0; j<meshLen; j++)
			ret[2][i][j] = ((c-*n[0]*ret[0][i][j]-*n[1]*ret[1][i][j])*1.0) / (*n[2]); //z = ((c-n[0]*x-n[1]*y)*1.0)/(n[2])
	return ret;
}

void saveMat(MATRIX mat, char *str, int m, int n){
	FILE *fp;
	fp = fopen(str,"w");
	for (int i=0; i < m; i++){
		for (int j=0; j < n; j++){
			fprintf(fp, "%lf ", mat[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

VECTOR foot(VECTOR n, double c_, VECTOR p){
	double a=*n[0]; double b=*n[1]; double c=*n[2]; double d = -c_;
	double x1=*p[0]; double y1=*p[1]; double z1=*p[2];
    double k = (-a * x1 - b * y1 - c * z1 - d) / (double)(a * a + b * b + c * c);
    VECTOR ret = createMat(3,1);
    *ret[0] = a * k + x1;
    *ret[1] = b * k + y1;
    *ret[2] = c * k + z1;
    return ret;
}
