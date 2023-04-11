#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <math.h>
#define row 256
#define col 256

int conv(unsigned char l[][row], int y, int x, int fil[][3]) {
	int f_x = 1, f_y = 1;
	int sums = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			sums += (l[y + i][x + j] * fil[f_y + i][f_x + j]);
		}
	}
	return sums;
}
int main() {

	FILE* fp;
	fp = fopen("baboon_before.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];

	int dy[row][col];
	int dx[row][col];
	int edge_power[row][col];
	

	int my[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	int mx[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };

	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			if (i == 0 || i == 255 || j == 0 || j == 255) {
				dy[i][j] = 0;
				dx[i][j] = 0;
				Writebuf[i][j] = 0;
				edge_power[i][j] = 0;
			}
			else {
				int ret = conv(Readbuf, i, j, my);
				dy[i][j] = ret;
				ret = conv(Readbuf, i, j, mx);
				dx[i][j] = ret;
				edge_power[i][j] = sqrt(pow(dy[i][j], 2) + pow(dy[i][j], 2));
				if (edge_power[i][j] > 255)
					Writebuf[i][j] = 255;
				else if (edge_power[i][j] < 0)
					Writebuf[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (dx[i][j] == 0)
				printf("0 ");
			else
					printf("%4.2lf ", atan((double)dy[i][j] / (double)dx[i][j]));
		}
		printf("\n");
	}
	fp = fopen("prac_ret.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}