//const double  pi = 3.14159265358979;


/*IFFTによる逆拡散*/
/*N:次数*/
/*F:IFFT出力、f:IFFT入力、N:次数*/
void Miz_IFFT(Complex *f, Complex *F, int N){
  int n,k,i,l,j,m;
  Complex a,b;
  int *x,*y;  //ソート用配列
  x = new int [N];
  y = new int [N];

  /*ソート*/
  x[0] = 0;
  x[1] = 1;
  for(k=2;k<=N/2;k*=2){
    for(i=0;i<k;i++){
      y[i] = x[i]*2;
      y[i+k] = x[i]*2+1;
    }
    for(i=0;i<N;i++){
      x[i] = y[i];
      F[i] = 0;
    }
  }
  for(i=0;i<N;i++){
    F[i] = ~f[y[i]];
  }
  /*butterfly-diagram*/
  for(n=1,i=0;n<=N/2;n*=2,i++){
    for(k=0,l=0,j=0,m=0;m<N/2;k++,l++,m++){
	     if(l==n){k+=n;l=0;}
       F[k+n] *= cmplx(cos(-2*M_PI*j/(pow(2,(i+1)))), sin(-2*M_PI*j/(pow(2,(i+1)))));
       a = F[k] + F[k+n];
       F[k+n] = F[k] - F[k+n];
       F[k] = a;
       if(j<=n-1)j++;
       if(j>n-1)j=0;
     }
   }

   for(i=0;i<N;i++){F[i] = ~F[i];}
   for(i=0;i<N;i++){F[i]=cmplx(re(F[i])/sqrt(N),(im(F[i])/sqrt(N)));}

  delete [] x;
  delete [] y;
}
