#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double double64;
#define EPSILON 2e-16
#define alloc(T,len) (T*)malloc(len*sizeof(T))
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define bool(x) (((x)==0) ? "False" : "True")

double64 conv(double64 (*seq)(int), double64 e);
double64 sum(double64 (*seq)(int), int n);
double64* find_roots(double64 a, double64 b, double64 c);
double64* roots;

double64 a_n(int n){ return (pow(roots[0],n)-pow(roots[1],n))/(roots[0]-roots[1]); }
double64 b_n(int n){ return a_n(n-1) + a_n(n+1); }
double64 a_u10_n(int n){ return a_n(n)/pow(10,n); }
double64 b_u10_n(int n){ return b_n(n)/pow(10,n); }

int main(){
	
	roots = find_roots(1, -1, -1);
	
	// Verifying option A for different values of n
	char* boolA = bool(1);
	for (int i=1; i<40; i++){
		if (abs(sum(a_n,i) - (a_n(i+2)-1)) > 0.000001){
			boolA = bool(0); // False
			break;
		}
	}
	printf("Option A is %s\n", boolA);
	
	// Verifying option B
	double64 b = conv(a_u10_n, EPSILON);
	char* boolB = bool(abs(b-(10.0/89.0)) < EPSILON);
	printf("Option B is %s : (a/10) + (a/10)^2 + ... = %Lf\n", boolB, b);
	
	// Verifying option C for different values of n
	char* boolC = bool(1);
	for (int i=1; i<50; i++){
		double64 rhs = pow(roots[0],i)+pow(roots[1],i);
		if (abs(b_n(i) - rhs) > 0.000001){
			boolC = bool(0); // False
			break;
		}
	}
	printf("Option C is %s\n", boolC);
	
	// Verifying option D
	double64 d = conv(b_u10_n, EPSILON);
	char* boolD = bool(abs(d-(8.0/89.0)) < EPSILON);
	printf("Option D is %s : (b/10) + (b/10)^2 + ... = %Lf %s %f\n", boolD, d, *boolD == 'T' ? "=" : "!=", 8.0/89.0);
	
	return 0;
}

double64* find_roots(double64 a, double64 b, double64 c){
	double64* ret = alloc(double64,2);
	double64 dis = sqrt((b*b) - (4*a*c));
	ret[0] = (-b + dis)/(2*a);
	ret[1] = (-b - dis)/(2*a);
	return ret;
}

double64 sum(double64 (*seq)(int), int n){
	double64 ret=0;
	for (int i=1; i <= n; i++) ret += seq(i);
	return ret;
}
double64 conv(double64 (*seq)(int), double64 e){
	double64 prev=1e300, s = 0;
	int i = 1;
	while (abs(prev-s) > e){
		prev = s;
		s += seq(i++);
	}
	return s;
}
