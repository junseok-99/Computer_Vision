#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <float.h>
#include <windows.h>

#define row 256
#define col 256

int main() {

	FILE* fp;
	fp = fopen("numbers_before.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];
	unsigned int His[256] = { 0 };
	double N[256];
	double Sum_N[256];
	unsigned int out[256];
	int T;
	double min_n = DBL_MAX;

	double w0, w1, u0, u1, v0, v1;

	double div = row * col;

	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			His[Readbuf[i][j]]++;
		}
	}

	for (int i = 0; i < 256; i++) 
		N[i] = His[i] / div;
	
	for (int t = 0; t < 256; t++) {
		w0 = 0.0, w1 = 0.0, u0 = 0.0, u1 = 0.0, v0 = 0.0, v1 = 0.0;

		for (int i = 0; i <= t; i++)
			w0 += N[i];
		for (int i = t + 1; i < 256; i++)
			w1 += N[i];

		for (int i = 0; i <= t; i++)
			u0 += i*N[i];
		for (int i = t + 1; i < 256; i++)
			u1 += i*N[i];

		u0 = w0 == 0 ? 0 : u0 / w0;
		u1 = w1 == 0 ? 0 : u1 / w1;

		for (int i = 0; i <= t; i++)
			v0 += N[i]*(i-u0) * (i - u0);
		for (int i = t + 1; i < 256; i++)
			v1 += N[i] * (i - u1) * (i - u1);

		v0 = w0 == 0 ? 0 : v0 / w0;
		v1 = w1 == 0 ? 0 : v1 / w1;

		double ret = (w0 * v0) + (w1 * v1);
		if (ret < min_n) {
			min_n = ret;
			T = t;
		}
	}
	printf("%d", T);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			Writebuf[i][j] = Readbuf[i][j] > T ? 255 : 0;
		}
	}
	fp = fopen("prac_ret.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}