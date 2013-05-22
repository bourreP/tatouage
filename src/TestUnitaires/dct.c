#include "dct.h"
 
/*
void gen_dct(double **c, int N) ;
void dct1dim(double *v, double *y, int N);
void dct1dim_inv(double *vt, double *vrec, int N);
void dct2dim(double **x, double **y, int M, int N);
void dct2dim_inv(double **xt, double **xrec, int M, int N);
*/

#define M_PI 3.14159265358979

void gen_dct(double **c, int N) 
{ 
	int i,j; 
	for(j=0;j<N;j++) c[0][j] = 1.0/sqrt((double)N); 

	for(i=1;i<N;i++) 
	{
		for(j=0;j<N;j++) 
		{
			c[i][j] = (sqrt(2.0/N))*cos(M_PI*(2*j+1.0)*i/(2.0*N)); 
		}
	}		

} 
 
void dct1dim(double *v, double *y, int N) 
{ 
	double **c = alocamd(N,N); 
	gen_dct(c,N); 
	mult_mvd(c,v,y,N,N,N); 
	dalocd(c,N); 
} 
 
void dct1dim_inv(double *vt, double *vrec, int N) 
{ 
	int i,j; 
	double **c = alocamd(N,N); 
	double **ctest = alocamd(N,N); 
	double **trez = alocamd(N,N); 
	double temp; 
 
	gen_dct(c,N); 
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			ctest[i][j] = c[i][j];
		}
	}

	for(i=0;i<N;i++) 
	{
		for(j=i+1;j<N;j++) 
		{
			temp = c[i][j];c[i][j] = c[j][i];c[j][i] = temp;
		} 
	}

	mult_mvd(c,vt,vrec,N,N,N); 
	dalocd(ctest,N);
	dalocd(trez,N); 
	dalocd(c,N);
} 
 
void dct2dim(double **x, double **y, int M, int N) 
{ 
	int i,j; 
	double *v = alocavd(N+M); 
	double *w = alocavd(N+M); 
	double **c = alocamd(N,N); 
 
	gen_dct(c,N); 
	for(i=0;i<M;i++) 
	{ 
		for(j=0;j<N;j++) 	v[j]=x[i][j]; 
		mult_mvd(c,v,w,N,N,N); 
		for(j=0;j<N;j++) 	y[i][j]=w[j]; 
	} 
 
	dalocd(c,N); 
	c = alocamd(M,M); 
	gen_dct(c,M); 
	
	for(j=0;j<N;j++) 
	{ 
		for(i=0;i<M;i++) 	v[i] = y[i][j]; 
		mult_mvd(c,v,w,M,M,M); 
		for(i=0;i<M;i++) 	y[i][j] = w[i]; 
	} 

	dalocd(c,M); 
	freevd(v);freevd(w); 
} 
 
 
 
void dct2dim_inv(double **xt, double **xrec, int M, int N) 
{ 
	int i,j; 
	double *v = alocavd(N+M); 
	double *w = alocavd(N+M); 
	double **c; double temp; 
 
	c = alocamd(M,M); 
 	gen_dct(c,M); 
	for(i=0;i<M;i++) 
	{
		for(j=i+1;j<M;j++) 
		{
			temp = c[i][j];c[i][j] = c[j][i];c[j][i] = temp;
		} 
	}

	for(j=0;j<N;j++) 
	{ 
		for(i=0;i<M;i++) 	v[i] = xt[i][j]; 
		mult_mvd(c,v,w,M,M,M); 
		for(i=0;i<M;i++) 
			xrec[i][j] = w[i]; 
	} 

	dalocd(c,M); 
 	c = alocamd(N,N); 
 
	gen_dct(c,N); 
	for(i=0;i<N;i++) 
	{
		for(j=i+1;j<N;j++) 
		{
			temp = c[i][j];c[i][j] = c[j][i];c[j][i] = temp;
		} 
	}

	for(i=0;i<M;i++) 
	{ 
		for(j=0;j<N;j++)	v[j] = xrec[i][j]; 
		mult_mvd(c,v,w,N,N,N); 
		for(j=0;j<N;j++) 
			xrec[i][j]=w[j]; 
	} 
 
	dalocd(c,N); 
 	freevd(v);freevd(w); 
} 
 

 
void dct2dim_old(double **x, double **y, int M, int N) 
{ 
	int i,j; 
	double *v = alocavd(N); 
	double *w = alocavd(N); 
	
	for(i=0;i<M;i++) 
	{ 
		for(j=0;j<N;j++) 
			v[j] = x[i][j]; 
		dct1dim(v,w,N); 
		for(j=0;j<N;j++) 
			y[i][j]=w[j]; 
	} 

	for(j=0;j<N;j++) 
	{ 
		for(i=0;i<M;i++) 
			v[i] = y[i][j]; 
		dct1dim(v,w,N); 
		for(i=0;i<M;i++) 
			y[i][j] = w[i]; 
	} 
freevd(v);freevd(w); 
}

void MH_contrast_local(double **MH_y, double **MHA_y, int N, int x, int y)
{
	int i,j;

	for (j=0; j < y; ++j)
	{
		for (i=0; i < x; ++i)
		{
			MH_y[j][i]= MHA_y[j][i]/MHA_y[j-j%N][i-i%N];
		}
	}
}



