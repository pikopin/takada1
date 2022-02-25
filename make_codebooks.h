void make_bit(int type, int* b) {
	uniform_int_distribution<int> dist(0, 1);
	if (type == 3) {
		b[0] = dist(mt);
		b[1] = dist(mt);
		b[2] = dist(mt);
	}
	else {
		cout << "ERR TYPE" << endl;
		exit(1);
	}

	return;
}

void make_codebook1(int* b, Complex* x, int j) {
	if (b[1] == 0) {
		if (b[2] == 0) {
			x[j] = S2; // cmplx(-1.0 / sqrt(2.0), 1.0 / sqrt(2.0));
		}
		else {
			x[j] = S1; // cmplx(1.0 / sqrt(2.0), 1.0 / sqrt(2.0));
		}
	}
	else {
		if (b[2] == 0) {
			x[j] = S4; // cmplx(-1.0 / sqrt(2.0), -1.0 / sqrt(2.0));
		}
		else {
			x[j] = S3; // cmplx(1.0 / sqrt(2.0), -1.0 / sqrt(2.0));
		}
	}
	return;
}


void make_codebook2(int* b, Complex * x, int j) {
	if (b[0] == 0) {
		if (b[2] == 0) {
			x[j] = S2; // cmplx(-1.0 / sqrt(2.0), 1.0 / sqrt(2.0));
		}
		else {
			x[j] = S1; // cmplx(1.0 / sqrt(2.0), 1.0 / sqrt(2.0));
		}
	}
	else {
		if (b[2] == 0) {
			x[j] = S4; // cmplx(-1.0 / sqrt(2.0), -1.0 / sqrt(2.0));
		}
		else {
			x[j] = S3; // cmplx(1.0 / sqrt(2.0), -1.0 / sqrt(2.0));
		}
	}
	return;
}

void make_codebook(int** b, Complex * *x) {
	int i;
	for (i = 0; i < 3; i++) {
		make_codebook1(b[i], x[i], 0);
	}
	for (i = 3; i < 5; i++) {
		make_codebook1(b[i], x[i], 1);
	}
	make_codebook1(b[5], x[5], 2);


	make_codebook2(b[0], x[0], 1);
	make_codebook2(b[1], x[1], 2);
	make_codebook2(b[2], x[2], 3);
	make_codebook2(b[3], x[3], 2);
	for (i = 4; i < 6; i++) {
		make_codebook2(b[i], x[i], 3);
	}
	return;
}
