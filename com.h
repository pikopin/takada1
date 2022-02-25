
void make_com(Complex**** codeword_pair_set) {
	int counter, i, j, k, p, t, n, m, l, counter2, s;
	Complex com_sub[2][8][4];
	t = 0;
	n = 0;

	for (k = 0; k < 4; k++) {
		counter = 0;
		for (p = 0; p < 3; p++) {
			s = 0;
			t = 0;
			counter2 = 0;
			for (j = 0; j < 6; j++) {
				if (factor_graph[k][j] == 1) {
					if (counter != counter2) {
						for (m = 0; m < 8; m++) {
							for (l = 0; l < 4; l++) {
								com_sub[t][m][l] = X[j][m][l];
							}
						}
						t++;
					}
					counter2++;
				}
			}
			counter++;

			for (i = 0; i < 8; i++) {
				for (j = 0; j < 8; j++) {
					for (l = 0; l < 4; l++) {
						codeword_pair_set[n][s][0][l] = com_sub[0][i][l];
						codeword_pair_set[n][s][1][l] = com_sub[1][j][l];
					}
					s++;
				}
			}
			n++;
		}
	}

	return;
}

void show_com(Complex**** codeword_pair_set) {
	int l, k, i;
	for (l = 0; l < 12; l++) {
		printf("No.%d\n", l);
		for (k = 0; k < 64; k++) {
			printf("%d\n", k);
			//for (j = 0; j < 2; j++) {
			for (i = 0; i < 4; i++) {
				printf("%lf|%lf	|	%lf|%lf", re(codeword_pair_set[l][k][0][i]), im(codeword_pair_set[l][k][0][i]), re(codeword_pair_set[l][k][1][i]), im(codeword_pair_set[l][k][1][i]));
				printf("\n");
				/*
				printf("%lf|%lf", re(codeword_pair_set[l][k][1][i]), im(codeword_pair_set[l][k][1][i]));
				printf("\n");
				*/
			}
			printf("\n");
			//}
			printf("\n");
		}
		printf("\n");
	}
	return;
}
