#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <thread>
#include <cstdlib>
#include"complex.c"
#include"codebooks.h"
#include"FFT.h"
#include"IFFT.h"

random_device rd;
mt19937 mt(rd());

FILE* fp1;

#include"make_codebooks.h"
//#include"OFDM.h"
#include"OFDM_cfo.h"
//#include"OFDM_dop.h"
#include"com.h"
#include"MPA.h"

double err_check(int type, int** b, int** b_ans) {
	double a = 0.0;

	for (int j = 0; j < 1; j++) {
		for (int i = 0; i < type; i++) {
			if (b[j][i] != b_ans[j][i]) {
				a = 1.0;
				break;
			}
		}
	}
	return a;
}


double err_check2(int type, int** b, int** b_ans, int j) {
	double a = 0.0;

	
	for (int i = 0; i < type; i++) {
		if (b[j][i] != b_ans[j][i]) {
			a = 1.0;
			break;
		}
	}

	return a;
}


int scma(double n0, double snr, int type, double es, double* counter) {
	int** b, i, j, k, ** b_ans, ** b_dans;
	Complex** x, * y_con, ** s, ** h_tiruda;

	b = new int* [J];
	for (i = 0; i < J; i++) {
		b[i] = new int[type];
	}

	b_ans = new int* [J];
	for (i = 0; i < J; i++) {
		b_ans[i] = new int[type];
	}

	b_dans = new int* [J];
	for (i = 0; i < J; i++) {
		b_dans[i] = new int[type];
	}

	x = new Complex * [J];
	for (i = 0; i < J; i++) {
		x[i] = new Complex[K];
	}

	y_con = new Complex[K];

	h_tiruda = new Complex * [J];
	for (i = 0; i < J; i++) {
		h_tiruda[i] = new Complex[K];
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < type; j++) {
			b_ans[i][j] = 0;
		}
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < K; j++) {
			h_tiruda[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < K; j++) {
			x[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (i = 0; i < K; i++) {
		y_con[i] = cmplx(0.0, 0.0);
	}
	
	for (i = 0; i < J; i++) {
		make_bit(type, b[i]);
	}
	
	
	make_codebook(b, x);

	ofdm(n0, snr, type, es, x, y_con, h_tiruda);
	MPA(n0, x, y_con, h_tiruda, b_ans, type);
	counter[0] = err_check(type, b, b_ans);
	//DMPA(n0, x, y_con, h_tiruda, b_dans, type);
	for (j = 0; j < J; j++) {
		counter[j] = err_check2(type, b, b_ans,j);
	}
	
	

	for (i = 0; i < J; i++) {
		delete[] b[i];
	}
	delete[] b;

	for (i = 0; i < J; i++) {
		delete[] b_ans[i];
	}
	delete[] b_ans;

	for (i = 0; i < J; i++) {
		delete[] b_dans[i];
	}
	delete[] b_dans;

	for (i = 0; i < J; i++) {
		delete[] x[i];
	}
	delete[] x;

	for (i = 0; i < J; i++) {
		delete[] h_tiruda[i];
	}
	delete[] h_tiruda;

	delete[] y_con;

	return 0;
}



int roop(double type) {
	int i, j, k;
	double  snr, n0, pr, ebn0dB, ebn0, snrdB, p[2], pe[2], es, eb, * counter, count[J], BEL1[J], BEL[J];
	for (i = 0; i < J; i++) {
		count[i] = 0.0;
	}
	counter = new double[J];
	
	
	for (snrdB = 0.0; snrdB < 51.0; snrdB += 2.0) {
		es = 7.0 / 3.0;
		//eb = 2.0 / 3.0;
		snr = pow(10.0, (snrdB / 10.0));
		//ebn0 = snr / 4.0;
		//n0 = eb / (3.0 * snr);
		n0 = es / (3.0 * snr);		//•ªŽU
		for (k = 0; k < J; k++) {
			BEL1[k] = 0.0;
			BEL[k] = 0.0;
		}
		//printf("snr:%lf\n", snrdB);
		for (i = 0; i < 5; i++) {
			for (k = 0; k < J; k++) {
				count[k] = 0.0;
			}
			for (j = 0; j < 1000; j++) {
				for (k = 0; k < J; k++) {
					counter[k] = 0.0;
				}
				scma(n0, snr, type, es, counter);
				//printf("\n");
				count[0] += counter[0];
				/*
				for (k = 0; k < J; k++) {
					count[k] += counter[k];
				}
				*/
			}
			BEL1[0] = count[0] / 1000.0;
			BEL[0] += BEL1[0];
			/*
			for (k = 0; k < J; k++) {
				BEL1[k] = count[k] / 100.0;
				BEL[k] += BEL1[k];
			}
			*/
		}
		BEL[0] = BEL[0] / 5.0;
		/*
		for (k = 0; k < J; k++) {
			BEL[k] = BEL[k] / 5.0;
		}
		*/
		fprintf(fp1, "%lf, %lf\n", snrdB, BEL[0]);
		//printf("%lf	\n", snrdB);
		printf("%.10lf	\n", BEL[0]);
		//printf("%.10lf	%.10lf	%.10lf	%.10lf	%.10lf	%.10lf\n", BEL[0], BEL[1], BEL[2], BEL[3], BEL[4], BEL[5]);
	}

	delete[] counter;
	
	return 0;
}


int main(int argc, char* argv[]) {
	int type;
	srand((unsigned int)time(NULL));
	type = atoi(argv[1]);

	fp1 = fopen("cfo0.003.csv", "a");
	fp1 = fopen("cfo0.003.csv", "w");
	if (type == 3) {
		roop(type);
	}

	fclose(fp1);
	return 0;
}