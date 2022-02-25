void addcp(Complex* x, Complex* x_hat, int num_id) {
	int i;
	Complex* gi;
	gi = new Complex[num_id];

	for (i = 0; i < num_id; i++) {
		gi[i] = x[SYNBOL_LENGTH - num_id + i];
		x_hat[i] = gi[i];
	}
	for (i = 0; i < SYNBOL_LENGTH; i++) {
		x_hat[i + num_id] = x[i];
	}

	delete[] gi;
	return;
}

void convolution(Complex* x_hat, Complex* y, Complex* h, int num_id) {
	int i, p, j, k, n;
	Complex* h_p;
	h_p = new Complex[SYNBOL_LENGTH + (2 * num_id) - 1];

	for (p = 0; p < num_id; p++) {
		for (i = 0; i < SYNBOL_LENGTH + (2 * num_id) - 1; i++) {
			h_p[i] = cmplx(0.0);
		}

		for (n = p; n < SYNBOL_LENGTH + num_id + p; n++) {
			h_p[n] = x_hat[n - p];
		}

		for (k = 0; k < SYNBOL_LENGTH + (2 * num_id) - 1; k++) {
			h_p[k] = h_p[k] * h[p];
			y[k] += h_p[k];
		}
	}


	delete[] h_p;
	return;
}


void convolution2(Complex** y_dash, Complex* y, int num_id) {
	int i, j;

	for (i = 0; i < SYNBOL_LENGTH + (2 * num_id) - 1; i++) {
		for (j = 0; j < 6; j++) {
			y[i] += y_dash[j][i];
		}
	}

	return;
}

void convolution3(Complex* h_dash, Complex** h_tiruda, int num_id) {
	int i, j;

	for (i = 0; i < SYNBOL_LENGTH; i++) {
		for (j = 0; j < 6; j++) {
			h_dash[i] += h_tiruda[j][i];
		}
	}
}

void removecp(Complex* y, Complex* y_hat, int num_id) {
	int i;

	for (i = 0; i < SYNBOL_LENGTH; i++) {
		y_hat[i] = y[i + num_id];
	}

	return;
}

Complex& zf(Complex& y, Complex& h) {
	Complex x_hat(0.0, 0.0);
	x_hat = y * (~h) / sqmag(h) / sqrt(SYNBOL_LENGTH);
	return cmplx(re(x_hat), im(x_hat));
}


Complex& make_awgn(double n0) {
	double sigma = sqrt(n0 / 2.0);
	normal_distribution<double> dist(0.0, sigma);
	return cmplx(dist(mt), dist(mt));
}


void ofdm(double n0, double snr, int type, double es, Complex * *x, Complex * y_con, Complex * *h_tiruda) {
	int i, j, b[4], k;
	Complex** s, ** s_hat, ** y_dash, * y, * y_hat, * r, ** h, noise, * h_dash, ** r_dash, ** y_con2, ** y_hat_dash;
	int num_id = 4;
	double ganma = 1.0;
	double noru = 0.0;


	s = new Complex * [J];
	for (i = 0; i < J; i++) {
		s[i] = new Complex[K];
	}

	s_hat = new Complex * [J];
	for (i = 0; i < J; i++) {
		s_hat[i] = new Complex[SYNBOL_LENGTH + num_id];
	}

	y_dash = new Complex * [J];
	for (i = 0; i < J; i++) {
		y_dash[i] = new Complex[SYNBOL_LENGTH + (2 * num_id) - 1];
	}

	r_dash = new Complex * [J];
	for (i = 0; i < J; i++) {
		r_dash[i] = new Complex[SYNBOL_LENGTH];
	}

	y_con2 = new Complex * [J];
	for (i = 0; i < J; i++) {
		y_con2[i] = new Complex[SYNBOL_LENGTH];
	}

	y_hat_dash = new Complex * [J];
	for (i = 0; i < J; i++) {
		y_hat_dash[i] = new Complex[SYNBOL_LENGTH];
	}

	y = new Complex[SYNBOL_LENGTH + (2 * num_id) - 1];
	y_hat = new Complex[SYNBOL_LENGTH];
	r = new Complex[SYNBOL_LENGTH];
	h_dash = new Complex[SYNBOL_LENGTH];
	//h = new Complex[SYNBOL_LENGTH];
	//h_tiruda = new Complex[SYNBOL_LENGTH];



	h = new Complex * [J];
	for (i = 0; i < J; i++) {
		h[i] = new Complex[K];
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < K; j++) {
			s[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < SYNBOL_LENGTH + num_id; j++) {
			s_hat[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < SYNBOL_LENGTH + (2 * num_id) - 1; j++) {
			y_dash[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (i = 0; i < SYNBOL_LENGTH; i++) {
		r[i] = cmplx(0.0, 0.0);
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < SYNBOL_LENGTH; j++) {
			r_dash[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < SYNBOL_LENGTH; j++) {
			y_con2[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (k = 0; k < SYNBOL_LENGTH + (2 * num_id) - 1; k++) {
		y[k] = cmplx(0.0,0.0);
	}
	for (k = 0; k < SYNBOL_LENGTH; k++) {
		y_hat[k] = cmplx(0.0,0.0);
	}

	for (i = 0; i < J; i++) {
		for (j = 0; j < K; j++) {
			h[i][j] = cmplx(0.0, 0.0);
		}
	}

	for (i = 0; i < SYNBOL_LENGTH; i++) {
		h_dash[i] = cmplx(0.0, 0.0);
	}

	noru = 0.0;
	
	for (i = 0; i < K; i++) {
		y_con[i] = cmplx(0.0, 0.0);
	}
	
	
	for (j = 0; j < J; j++) {
		for (i = 0; i < num_id; i++) {
			h[j][i] = cmplx(pow(ganma, i));
			noru += sqmag(h[j][i]);
			h[j][i] *= make_awgn(1.0);
		}
		noru = sqrt(noru);

		for (i = 0; i < SYNBOL_LENGTH - num_id; i++) {
			h[j][i + num_id] = cmplx(0.0,0.0);
		}

		for (i = 0; i < num_id; i++) {
			h[j][i] = h[j][i] / noru;
		}

	}
	
	/*
	h[0][0] = cmplx(0.1, 0.0);
	h[0][1] = cmplx(0.0, 0.0);
	h[0][2] = cmplx(0.0, 0.0);
	h[0][3] = cmplx(0.0, 0.0);

	h[1][0] = cmplx(0.2, 0.0);
	h[1][1] = cmplx(0.0, 0.0);
	h[1][2] = cmplx(0.0, 0.0);
	h[1][3] = cmplx(0.0, 0.0);

	h[2][0] = cmplx(0.4, 0.0);
	h[2][1] = cmplx(0.0, 0.0);
	h[2][2] = cmplx(0.0, 0.0);
	h[2][3] = cmplx(0.0, 0.0);

	h[3][0] = cmplx(0.8, 0.0);
	h[3][1] = cmplx(0.0, 0.0);
	h[3][2] = cmplx(0.0, 0.0);
	h[3][3] = cmplx(0.0, 0.0);

	h[4][0] = cmplx(1.6, 0.0);
	h[4][1] = cmplx(0.0, 0.0);
	h[4][2] = cmplx(0.0, 0.0);
	h[4][3] = cmplx(0.0, 0.0);

	h[5][0] = cmplx(3.2, 0.0);
	h[5][1] = cmplx(0.0, 0.0);
	h[5][2] = cmplx(0.0, 0.0);
	h[5][3] = cmplx(0.0, 0.0);
	*/
	/*
	h[0][0] = cmplx(1.0, 0.0);
	h[0][1] = cmplx(0.0, 0.0);
	h[0][2] = cmplx(0.0, 0.0);
	h[0][3] = cmplx(0.0, 0.0);

	h[1][0] = cmplx(1.0, 0.0);
	h[1][1] = cmplx(0.0, 0.0);
	h[1][2] = cmplx(0.0, 0.0);
	h[1][3] = cmplx(0.0, 0.0);

	h[2][0] = cmplx(1.0, 0.0);
	h[2][1] = cmplx(0.0, 0.0);
	h[2][2] = cmplx(0.0, 0.0);
	h[2][3] = cmplx(0.0, 0.0);

	h[3][0] = cmplx(1.0, 0.0);
	h[3][1] = cmplx(0.0, 0.0);
	h[3][2] = cmplx(0.0, 0.0);
	h[3][3] = cmplx(0.0, 0.0);

	h[4][0] = cmplx(1.0, 0.0);
	h[4][1] = cmplx(0.0, 0.0);
	h[4][2] = cmplx(0.0, 0.0);
	h[4][3] = cmplx(0.0, 0.0);

	h[5][0] = cmplx(1.0, 0.0);
	h[5][1] = cmplx(0.0, 0.0);
	h[5][2] = cmplx(0.0, 0.0);
	h[5][3] = cmplx(0.0, 0.0);
	*/
	

	for (i = 0; i < J; i++) {
		Miz_IFFT(x[i], s[i], 4);
	}


	for (i = 0; i < J; i++) {
		addcp(s[i], s_hat[i], num_id);
	}

	/*
	//noise = make_awgn(n0);
	for (i = 0; i < J; i++) {
		for (j = 0; j < SYNBOL_LENGTH + (2 * num_id) - 1; j++) {
			noise = make_awgn(n0);
			s_hat[i][j] = s_hat[i][j] + noise;
		}
	}
	*/




	for (i = 0; i < J; i++) {
		convolution(s_hat[i], y_dash[i], h[i], num_id);
	}

	/*
	//noise = make_awgn(n0);
	for (i = 0; i < J; i++) {
		//noise = make_awgn(n0);
		for (j = 0; j < SYNBOL_LENGTH + (2 * num_id) - 1; j++) {
			noise = 0.0;// make_awgn(n0);
			y_dash[i][j] = y_dash[i][j] + noise;
		}
	}
	*/



	convolution2(y_dash, y, num_id);

	//noise = make_awgn(n0);
	for (i = 0; i < SYNBOL_LENGTH + (2 * num_id) - 1; i++) {
		//noise = cmplx(0.0, 0.0);
		noise = make_awgn(n0);
		y[i] = y[i] + noise;
	}

	removecp(y, y_hat, num_id);

	Miz_FFT(y_hat, r, 4);


	/*
	for (i = 0; i < J; i++) {
		removecp(y_dash[i], y_hat_dash[i], num_id);
		Miz_FFT(y_hat_dash[i], r_dash[i], 4);
	}
	*/

	Complex w;
	w = cmplx(2.0, 0.0);

	for (j = 0; j < J; j++) {
		Miz_FFT(h[j], h_tiruda[j], 4);
	}

	for (j = 0; j < J; j++) {
		for (i = 0; i < K; i++) {
			h_tiruda[j][i] = h_tiruda[j][i] * w;
		}
	}

	/*
	for (j = 0; j < J; j++) {
		Miz_IFFT(h_tiruda[j], h[j], 4);
	}
	
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			printf("%lf|%lf	|	%lf|%lf\n", re(h[i][j]), im(h[i][j]), re(h_tiruda[i][j]), im(h_tiruda[i][j]));
		}
		printf("\n");
	}
	*/
	/*
	for (i = 0; i < 4; i++) {
		printf("%lf|%lf", re(r[i]), im(r[i]));
		printf("\n");
	}
	*/
	for (i = 0; i < 4; i++) {
		y_con[i] = r[i];
	}
	


	/*
	convolution3(h_dash, h_tiruda, num_id);
	for (i = 0; i < SYNBOL_LENGTH; i++) {
		y_con[i] = zf(r[i], h_dash[i]);
	}
	*/

	/*
	for (j = 0; j < J; j++) {
		for (i = 0; i < SYNBOL_LENGTH; i++) {
			//y_con2[j][i] = zf(r_dash[j][i], h_tiruda[j][i]);
			y_con2[j][i] = r_dash[j][i];
		}
	}
	*/
	/*
	for (i = 0; i < 4; i++) {
		printf("%lf|%lf", re(y_con[i]), im(y_con[i]));
		printf("\n");
	}
	*/


	/*
	for (j = 0; j < J; j++) {
		for (i = 0; i < 4; i++) {
			printf("%lf|%lf", re(y_con2[j][i]), im(y_con2[j][i]));
			printf("\n");
		}
		printf("\n");
	}
	*/


	for (i = 0; i < J; i++) {
		delete[] s[i];
	}
	delete[] s;
	for (i = 0; i < J; i++) {
		delete[] s_hat[i];
	}
	delete[] s_hat;
	for (i = 0; i < J; i++) {
		delete[] y_dash[i];
	}
	delete[] y_dash;
	delete[] y;
	delete[] y_hat;
	delete[] r;
	delete[] h_dash;

	for (i = 0; i < J; i++) {
		delete[] h[i];
	}
	delete[] h;

	for (i = 0; i < J; i++) {
		delete[] r_dash[i];
	}
	delete[] r_dash;

	for (i = 0; i < J; i++) {
		delete[] y_con2[i];
	}
	delete[] y_con2;

	for (i = 0; i < J; i++) {
		delete[] y_hat_dash[i];
	}
	delete[] y_hat_dash;

	return;
}
