#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coeffs.h"

typedef double** Matrix; typedef double** Vector;
Matrix meshgrid(int len, int start, int stepX, int stepY);
Matrix *createPlane(Vector n, double c, int meshLen);
Vector foot(Vector n, double c_, Vector p);
Vector createVec(double x,double y,double z);
Vector cross_pdt(Vector a, Vector b);
void set(Matrix mat, int row, double x,double y,double z);

int main(){
	// p = (1 -2 4)^T, x = (1 2 2)^T (x is point on plane)
	Vector p = createVec(1,-2,4);
	Vector x = createVec(1,2,2);
	
	// Assigning normal vectors of given planes
	Vector n1 = createVec(1,-1,2);
	Vector n2 = createVec(2,-2,1);
	double c1 = 3; double c2 = -12;
	
	Vector n = cross_pdt(n1, n2);
	
	double c = **matmul(transpose(x,3,1), n, 1,3,1);
	
	// Finding distance by applying formula
	double dist = abs(**matmul(transpose(linalg_sub(p,x,3,1),3,1), n, 1,3,3)) / linalg_norm(n,3);
	
	printf("Plane equation : (%d %d %d)x = %d\n", (int)*n[0], (int)*n[1], (int)*n[2], (int)c);
	printf("Distace = %lf\n\n",dist);
	
	Vector foot_ = foot(n, c, p);
	
	int meshLen = 10;
	
	Matrix *plane1 = createPlane(n1, c1, meshLen);
	savetxt(plane1[0], "data/meshX1.dat", meshLen, meshLen);
	savetxt(plane1[1], "data/meshY1.dat", meshLen, meshLen);
	savetxt(plane1[2], "data/meshZ1.dat", meshLen, meshLen);
	
	Matrix *plane2 = createPlane(n2, c2, meshLen);
	savetxt(plane2[0], "data/meshX2.dat", meshLen, meshLen);
	savetxt(plane2[1], "data/meshY2.dat", meshLen, meshLen);
	savetxt(plane2[2], "data/meshZ2.dat", meshLen, meshLen);
	
	*n[1] += *n[2]; *n[2] = *n[1] - *n[2]; *n[1] -= *n[2]; meshLen += 10;
	
	Matrix *plane3 = createPlane(n, c, meshLen);
	savetxt(plane3[0], "data/meshX3.dat", meshLen, meshLen);
	savetxt(plane3[1], "data/meshZ3.dat", meshLen, meshLen);
	savetxt(plane3[2], "data/meshY3.dat", meshLen, meshLen);
	
	savetxt(p,"data/P.dat",3,1);
	savetxt(foot_,"data/foot.dat",3,1);
	return 0;
}

Matrix meshgrid(int len, int start, int stepX, int stepY){
	Matrix ret = createMat(len, len);
	for (int i=0; i<len; i++)
		for (int j=0; j<len; j++){
			ret[i][j] = start + i*stepY + j*stepX;
		}
	return ret;
}
Matrix *createPlane(Vector n, double c, int meshLen){
	Matrix* ret = (Matrix*)malloc(3*sizeof(Matrix));
	ret[0] = meshgrid(meshLen, -meshLen/2, 2, 0);
	ret[1] = meshgrid(meshLen, -meshLen/2, 0, 2);
	ret[2] = meshgrid(meshLen, -meshLen/2, 0, 0);
	
	for (int i=0; i<meshLen; i++)
		for (int j=0; j<meshLen; j++)
			ret[2][i][j] = ((c-*n[0]*ret[0][i][j]-*n[1]*ret[1][i][j])*1.0) / (*n[2]); //z = ((c-n[0]*x-n[1]*y)*1.0)/(n[2])
	return ret;
}

Vector foot(Vector n, double c_, Vector p){
	double a=*n[0]; double b=*n[1]; double c=*n[2]; double d = -c_;
	double x1=*p[0]; double y1=*p[1]; double z1=*p[2];
    double k = (-a * x1 - b * y1 - c * z1 - d) / (double)(a * a + b * b + c * c);
    return createVec(a * k + x1, b * k + y1, c * k + z1);
}
Vector createVec(double x,double y,double z){
	Vector vec = createMat(3,1);
	*vec[0]=x; *vec[1]=y; *vec[2]=z;
	return vec;
}
Vector cross_pdt(Vector a, Vector b){
	Matrix n1o = createMat(3,3);
	set(n1o, 0,      0, -*a[2],  *a[1]);
	set(n1o, 1,  *a[2],      0, -*a[0]);
	set(n1o, 2, -*a[1],  *a[0],      0);
	return matmul(n1o, b, 3,3,1);
}
void set(Matrix mat, int row, double x,double y,double z){
	mat[row][0]=x; mat[row][1]=y; mat[row][2]=z;
}
