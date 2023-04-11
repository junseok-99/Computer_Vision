#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

#define row 256
#define col 256

int main() {

	FILE* fp;
	fp = fopen("baboon_before.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];
	
	double div = row * col;

	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			//Writebuf[i][j] = min(Readbuf[i][j] + 32, row-1); //¹à°Ô
			//Writebuf[i][j] = max(Readbuf[i][j] - 40, 0); //¾îµÓ°Ô
			Writebuf[i][j] = (row - 1) - Readbuf[i][j]; //¹ÝÀü
	
	fp = fopen("prac_ret.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}