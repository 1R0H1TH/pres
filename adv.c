#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 2e-15
#define alloc(T,len) (T*)malloc(len*sizeof(T))
#define abs(x) ((x) >= 0 ? x : -(x))
#define bool(x) (x==0 ? "False" : "True")

double conv(double (*seq)(int), double e);
double sum(double (*seq)(int), int n);
double* find_roots(double a, double b, double c);
double* roots;

double a_n(int n){ return (pow(roots[0],n)-pow(roots[1],n))/(roots[0]-roots[1]); }
double b_n(int n){ return a_n(n-1) + a_n(n+1); }
double a_u10_n(int n){ return a_n(n)/pow(10,n); }
double b_u10_n(int n){ return b_n(n)/pow(10,n); }

int main(){
	roots = find_roots(1, -1, -1);
	printf("%lf, %lf, %lf, %lf", sum(a_n,20), a_n(22)-1, conv(a_u10_n, EPSILON), conv(b_u10_n, EPSILON));
	return 0;
}

double* find_roots(double a, double b, double c){
	double* ret = alloc(double,2);
	double dis = sqrt((b*b) - (4*a*c));
	ret[0] = (-b + dis)/(2*a);
	ret[1] = (-b - dis)/(2*a);
	return ret;
}

double sum(double (*seq)(int), int n){
	double ret=0;
	for (int i=1; i <= n; i++) ret += seq(i);
	return ret;
}
double conv(double (*seq)(int), double e){
	double prev=1e300, s = 0;
	int i = 1;
	while (abs(prev-s) > e){
		prev = s;
		s += seq(i++);
	}
	return s;
}
