void V_update(double*** U, double*** V) {
	int m;

	for (m = 0; m < 8; m++) {
		V[0][0][m] = U[1][0][m];
		V[0][1][m] = U[0][0][m];

		V[1][0][m] = U[2][0][m];
		V[1][1][m] = U[0][1][m];

		V[2][0][m] = U[3][0][m];
		V[2][1][m] = U[0][2][m];

		V[3][0][m] = U[2][1][m];
		V[3][1][m] = U[1][1][m];

		V[4][0][m] = U[3][1][m];
		V[4][1][m] = U[1][2][m];

		V[5][0][m] = U[3][2][m];
		V[5][1][m] = U[2][2][m];
	}

	return;
}

void V_norm(double*** V, double** V_up) {
	int j, k, m;

	for (j = 0; j < 6; j++) {
		for (k = 0; k < 2; k++) {
			for (m = 0; m < 8; m++) {
				V_up[j][k] += V[j][k][m];
			}
		}
	}

	/*
	for (j = 0; j < 6; j++) {
		for (k = 0; k < 2; k++) {
			printf("%lf\n", V_up[j][k]);
		}
		printf("\n");
	}
	*/

	for (j = 0; j < 6; j++) {
		for (k = 0; k < 2; k++) {
			for (m = 0; m < 8; m++) {
				V[j][k][m] = V[j][k][m] / V_up[j][k];
			}
		}
	}

	return;
}

void U_update(Complex**** codeword_pair_set, double*** U, double*** V, Complex** h_tiruda, Complex** C, int type, double n0, Complex* y_con) {
	int i, j, m, t, p, k, l, c, n, s, counter, counter2, x, q, a, b;
	Complex sum1;
	double V_sub[2], sum2;
	n = 0;
	sum1 = cmplx(0.0, 0.0);
	counter = 0;
	counter2 = 0;
	a = 0;
	b = 0;

	for (i = 0; i < 2; i++) {
		V_sub[i] = 0.0;
	}


	for (k = 0; k < K; k++) {
		counter = 0;
		for (j = 0; j < J; j++) {
			if (factor_graph[k][j] == 1) {
				if (counter2 == 4) {
					a = 1;
				}
				if (counter2 == 8) {
					b = 1;
				}
				for (m = 0; m < M; m++) {
					p = 0;
					s = 0;
					x = 0;
					for (c = 0; c < 64; c++) {
						sum1 = cmplx(0.0, 0.0);
						//printf("%d|%d|%d|%d\n", k, j, m, c);

						for (i = 0; i < 2; i++) {
							for (l = 0; l < 4; l++) {
								C[i][l] = codeword_pair_set[n][c][i][l];
								//printf("%d|%d|%d|%d\n", n, c, i, l);
							}
						}

						if (s == 8) {
							s = 0;
							p++;
						}

						for (i = 0; i < 6; i++) {
							if (factor_graph[k][i] == 1) {
								if (i != j) {
									q = i;
									V_sub[0] = V[i][a][p];
									//printf("%d|%d|%d\n", i, a, p);
									//printf("%lf|", V_sub[0]);
									break;
								}
							}
						}
						for (i = 0; i < 6; i++) {
							if (factor_graph[k][i] == 1) {
								if (i != j && i != q) {
									V_sub[1] = V[i][b][s];
									//printf("%d|%d|%d\n", i, b, s);
									//printf("%lf\n", V_sub[1]);
									break;
								}
							}
						}
						s++;

						//printf("%d|%d|%d|%d\n", k, j, m, c);
						for (l = 0; l < 6; l++) {
							if (factor_graph[k][l] == 1) {
								if (l != j) {
									sum1 += C[x][k] * h_tiruda[l][k];
									//printf("%lf|%lf\n", re(sum1), im(sum1));
									//printf("%d|%d|%d\n", x, k, l);
									x++;
								}
							}
						}
						x = 0;
						//printf("%lf|%lf\n", re(sum1), im(sum1));
						//printf("\n");

						//printf("%d|%d|%d|%d\n", k, j, m, c);
						//printf("%lf|%lf\n", re(sum1), im(sum1));
						sum2 = (-1.0 / n0) * sqmag(y_con[k] - h_tiruda[j][k] * X[j][m][k] - sum1);
						//printf("%lf|%lf\n", re(h_tiruda[j][k]*X[j][m][k]), im(h_tiruda[j][k]*X[j][m][k]));
						//printf("%lf\n", sqmag(y_con[k] - h_tiruda[j][k] * X[j][m][k] - sum1));
						//printf("%d|%d|%d|%d\n", k, j, m, c);

						//U[k][counter][m] += log(1.0 / (M_PI * n0)) + sum2 + log(V_sub[0]) + log(V_sub[1]);

						U[k][counter][m] += 1.0 / (M_PI * n0) * exp(sum2) * V_sub[0] * V_sub[1];
						//printf("%lf\n", U[k][counter][m]);
						//printf("%d|%d|%d|%d\n", k, j, m, c);
					}

					//printf("\n");
				}
				counter++;
				counter2++;
				n++;
			}
			//n++;
		}
	}


	return;
}

void make_can(double** V_can, double*** U, int* ans) {
	int m, j, i;
	double tmp;

	for (m = 0; m < 8; m++) {
		V_can[0][m] = U[0][0][m] * U[1][0][m];
		V_can[1][m] = U[0][1][m] * U[2][0][m];
		V_can[2][m] = U[0][2][m] * U[3][0][m];
		V_can[3][m] = U[1][1][m] * U[2][1][m];
		V_can[4][m] = U[1][2][m] * U[3][1][m];
		V_can[5][m] = U[2][2][m] * U[3][2][m];
	}

	for (j = 0; j < 6; j++) {
		tmp = V_can[j][0];
		ans[j] = 0;
		for (m = 0; m < 8; m++) {
			if (tmp < V_can[j][m]) {
				tmp = V_can[j][m];
				ans[j] = m;
			}
		}
	}

	
	
	

	return;
}

void MPA(double n0, Complex * *x, Complex * y_con, Complex * *h_tiruda, int** b_ans, int type) {
	int i, j, m, t, p, k, l, c, n, s, counter, counter2;
	Complex** C, sum1;
	//Complex codeword_pair_set[12][64][2][4];
	Complex**** codeword_pair_set;
	double** V_can, ** U_can, U_other, U_dash;
	double*** V, ** V_up, V_sub[2]; //V3[2][8], V4[2][8], V5[2][8], V6[2][8];
	double*** U;//U1[3][8], U2[3][8], U3[3][8], U4[3][8];
	int* ans;

	V_can = new double* [J];
	for (j = 0; j < J; j++) {
		V_can[j] = new double[M];
	}

	U_can = new double* [J];
	for (j = 0; j < J; j++) {
		U_can[j] = new double[M];
	}

	ans = new int[J];

	codeword_pair_set = new Complex * **[J * dv];
	for (i = 0; i < J * dv; i++) {
		codeword_pair_set[i] = new Complex * *[64];
		for (j = 0; j < 64; j++) {
			codeword_pair_set[i][j] = new Complex * [dv];
			for (k = 0; k < dv; k++) {
				codeword_pair_set[i][j][k] = new Complex[K];
			}
		}
	}

	C = new Complex * [df - 1];
	for (i = 0; i < df - 1; i++) {
		C[i] = new Complex[K];
	}

	U = new double** [4];
	for (i = 0; i < 4; i++) {
		U[i] = new double* [3];
		for (j = 0; j < 3; j++) {
			U[i][j] = new double[8];
		}
	}

	V = new double** [6];
	for (i = 0; i < 6; i++) {
		V[i] = new double* [2];
		for (j = 0; j < 2; j++) {
			V[i][j] = new double[8];
		}
	}

	V_up = new double* [6];
	for (i = 0; i < 6; i++) {
		V_up[i] = new double[2];
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			for (m = 0; m < 8; m++) {
				U[i][j][m] = 0.0;
			}
		}
	}

	make_com(codeword_pair_set);
	//show_com(codeword_pair_set);

	for (j = 0; j < J; j++) {
		counter = 0;
		for (k = 0; k < K; k++) {
			if (factor_graph[k][j] == 1) {
				for (m = 0; m < M; m++) {
					V[j][counter][m] = 1.0 / M;
				}
				counter++;
			}
		}
	}

	for (t = 0; t < t_max; t++) {
		U_update(codeword_pair_set, U, V, h_tiruda, C, type, n0, y_con);

		/*
		for (i = 0; i < 4; i++) {
			for (k = 0; k < 3; k++) {
				for (m = 0; m < M; m++) {
					printf("%.40lf", U[i][k][m]);
					printf("\n");
				}
				printf("\n");
			}
			printf("\n");
		}
		*/

		V_update(U, V);		//m個のコードワードに対して式(3)

		for (i = 0; i < 6; i++) {
			for (j = 0; j < 2; j++) {
				V_up[i][j] = 0.0;
			}
		}

		V_norm(V, V_up);	//式(4)で正規化

	}
	make_can(V_can, U, ans);	//確率の判定

	for (j = 0; j < J; j++) {
		if (ans[j] == 0) {
			b_ans[j][0] = 0;
			b_ans[j][1] = 0;
			b_ans[j][2] = 0;
		}
		else if (ans[j] == 1) {
			b_ans[j][0] = 0;
			b_ans[j][1] = 0;
			b_ans[j][2] = 1;
		}
		else if (ans[j] == 2) {
			b_ans[j][0] = 0;
			b_ans[j][1] = 1;
			b_ans[j][2] = 0;
		}
		else if (ans[j] == 3) {
			b_ans[j][0] = 0;
			b_ans[j][1] = 1;
			b_ans[j][2] = 1;
		}
		else if (ans[j] == 4) {
			b_ans[j][0] = 1;
			b_ans[j][1] = 0;
			b_ans[j][2] = 0;
		}
		else if (ans[j] == 5) {
			b_ans[j][0] = 1;
			b_ans[j][1] = 0;
			b_ans[j][2] = 1;
		}
		else if (ans[j] == 6) {
			b_ans[j][0] = 1;
			b_ans[j][1] = 1;
			b_ans[j][2] = 0;
		}
		else {
			b_ans[j][0] = 1;
			b_ans[j][1] = 1;
			b_ans[j][2] = 1;
		}
	}


	for (i = 0; i < J; i++) {
		delete[] V_can[i];
	}
	delete[] V_can;

	for (i = 0; i < J; i++) {
		delete[] U_can[i];
	}
	delete[] U_can;

	for (i = 0; i < 12; i++) {
		for (j = 0; j < 64; j++) {
			for (k = 0; k < 2; k++) {
				delete[] codeword_pair_set[i][j][k];
			}
			delete[] codeword_pair_set[i][j];
		}
		delete[] codeword_pair_set[i];
	}
	delete[] codeword_pair_set;

	for (i = 0; i < df - 1; i++) {
		delete[] C[i];
	}
	delete[] C;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			delete[] U[i][j];
		}
		delete[] U[i];
	}
	delete[] U;

	for (i = 0; i < 6; i++) {
		for (j = 0; j < 2; j++) {
			delete[] V[i][j];
		}
		delete[] V[i];
	}
	delete[] V;

	for (i = 0; i < 6; i++) {
		delete[] V_up[i];
	}
	delete[] V_up;
	delete[] ans;

	return;
}
