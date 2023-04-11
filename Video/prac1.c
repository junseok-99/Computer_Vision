#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

#define row 256
#define col 256

int main() {

	FILE* fp;
	fp = fopen("air_before.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];
	unsigned int His[256]={0};
	double N[256];
	double Sum_N[256];
	unsigned int out[256];

	double w0, w1, u0, u1, v0, v1;

	double div = row * col;

	for(int i=0;i<256;i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j <256; j++) {
			His[Readbuf[i][j]]++;
		}
	}
	
	for (int i = 0; i < 256; i++) {
		N[i] = His[i] / div;
		
		if (i == 0)
			Sum_N[i] = N[i];
		else
			Sum_N[i] = Sum_N[i - 1] + N[i];
	}
	
	for (int i = 0; i < 256; i++) {
		out[i] = Sum_N[i] * (row - 1);
	}

	for (int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			Writebuf[i][j] = out[Readbuf[i][j]];
		}
	}
	fp = fopen("prac_ret.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}