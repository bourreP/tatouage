#if !defined(DCT_H__408B48CA_1F71_4B7A_92A6_48E48ABC81FC__INCLUDED_)
#define DCT_H__408B48CA_1F71_4B7A_92A6_48E48ABC81FC__INCLUDED_

void gen_dct(double **c, int N) ;
void dct1dim(double *v, double *y, int N);
void dct1dim_inv(double *vt, double *vrec, int N);
void dct2dim(double **x, double **y, int M, int N);
void dct2dim_inv(double **xt, double **xrec, int M, int N);

#endif // !defined(AFX_STDAFX_H__408B48CA_1F71_4B7A_92A6_48E48ABC81FC__INCLUDED_)