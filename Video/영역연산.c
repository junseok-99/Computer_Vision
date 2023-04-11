#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <math.h>
#define row 256
#define col 256

int conv(unsigned char l[][row], int y, int x, double fil[][3]) {
	int f_x = 1, f_y = 1;
	double sums = 0.0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			sums += l[y + i][x + j] * fil[f_y + i][f_x + j];
		}
	}
	return floor(sums);
}
int main() {

	FILE* fp;
	fp = fopen("baboon_before.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];
	double filter[3][3] = { {1.0/9.0,1.0/9.0,1.0/9.0 },{1.0/9.0 ,1.0/9.0 ,1.0/9.0 },{1.0/9.0 ,1.0/9.0 ,1.0/9.0 } };

	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			if (i == 0 || i == 255 || j == 0 || j == 255)
				Writebuf[i][j] = 0;
			else {
				int ret = conv(Readbuf, i, j, filter);
				if (ret > 255)
					ret = 255;
				else if (ret < 0)
					ret = 0;
				Writebuf[i][j] = ret;
			}
		}
	}
	
	fp = fopen("prac_ret.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}