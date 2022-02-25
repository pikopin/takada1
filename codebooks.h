Complex ZR = cmplx(0.0, 0.0);
Complex S1 = cmplx(1.0 / sqrt(2.0), 1.0 / sqrt(2.0));
Complex S2 = cmplx(-1.0 / sqrt(2.0), 1.0 / sqrt(2.0));
Complex S3 = cmplx(1.0 / sqrt(2.0), -1.0 / sqrt(2.0));
Complex S4 = cmplx(-1.0 / sqrt(2.0), -1.0 / sqrt(2.0));

Complex X[6][8][4] = { { {S2,S2,ZR,ZR},{S1,S1,ZR,ZR},{S4,S2,ZR,ZR},{S3,S1,ZR,ZR},{S2,S4,ZR,ZR},{S1,S3,ZR,ZR},{S4,S4,ZR,ZR},{S3,S3,ZR,ZR} },
							{ {S2,ZR,S2,ZR},{S1,ZR,S1,ZR},{S4,ZR,S2,ZR},{S3,ZR,S1,ZR},{S2,ZR,S4,ZR},{S1,ZR,S3,ZR},{S4,ZR,S4,ZR},{S3,ZR,S3,ZR} },
							{ {S2,ZR,ZR,S2},{S1,ZR,ZR,S1},{S4,ZR,ZR,S2},{S3,ZR,ZR,S1},{S2,ZR,ZR,S4},{S1,ZR,ZR,S3},{S4,ZR,ZR,S4},{S3,ZR,ZR,S3} },
							{ {ZR,S2,S2,ZR},{ZR,S1,S1,ZR},{ZR,S4,S2,ZR},{ZR,S3,S1,ZR},{ZR,S2,S4,ZR},{ZR,S1,S3,ZR},{ZR,S4,S4,ZR},{ZR,S3,S3,ZR} },
							{ {ZR,S2,ZR,S2},{ZR,S1,ZR,S1},{ZR,S4,ZR,S2},{ZR,S3,ZR,S1},{ZR,S2,ZR,S4},{ZR,S1,ZR,S3},{ZR,S4,ZR,S4},{ZR,S3,ZR,S3} },
							{ {ZR,ZR,S2,S2},{ZR,ZR,S1,S1},{ZR,ZR,S4,S2},{ZR,ZR,S3,S1},{ZR,ZR,S2,S4},{ZR,ZR,S1,S3},{ZR,ZR,S4,S4},{ZR,ZR,S3,S3} } };

int factor_graph[4][6] = { {1,1,1,0,0,0},{1,0,0,1,1,0},{0,1,0,1,0,1},{0,0,1,0,1,1} };

const int SYNBOL_LENGTH = 4;
using namespace std;

int M = 8;
int J = 6;
int K = 4;
int df = 3;
int dv = 2;
int t_max = 3;

//double es = 1.0;


