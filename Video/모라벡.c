#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <windows.h>

int sum(unsigned char f[][12], int s[][3], int y1, int y2, int x1, int x2, int u, int v) {
	int ret = 0;
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++) {
			ret += (f[y + v][x + u] - f[y][x]) * (f[y + v][x + u] - f[y][x]);
		}
	return ret;
}
int mins(int a, int b, int c, int d) {
	int tmp1, tmp2;
	tmp1 = a > b ? b : a;
	tmp2 = c > d ? d : c;

	return min(tmp1, tmp2);
}
int main() {

	unsigned char f[12][12] = { {0,0,0,0,0,0,0,0,0,0,0,0},
								{0,0,0,0,0,0,0,0,0,0,0,0}
								,{0,0,0,0,0,0,0,0,0,0,0,0}
								,{0,0,0,1,0,0,0,0,0,0,0,0}
								,{0,0,0,1,1,0,0,0,0,0,0,0}
								,{0,0,0,1,1,1,0,0,0,0,0,0}
								,{0,0,0,1,1,1,1,0,0,0,0,0}
								,{0,0,0,1,1,1,1,1,0,0,0,0}
								,{0,0,0,0,0,0,0,0,0,0,0,0}
								,{0,0,0,0,0,0,0,0,0,0,0,0}
								,{0,0,0,0,0,0,0,0,0,0,0,0}
								,{0,0,0,0,0,0,0,0,0,0,0,0}
	};
	int s[3][3] = { 0 };
	int r[12][12] = { 0 };

	for (int k = 1; k < 11; k++) {
		for (int m = 1; m < 11; m++) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					s[1 + i][1 + j] = sum(f, s, k - 1, k + 1, m - 1, m + 1, j, i);
				}
			}
			r[k][m] = mins(s[0][1], s[1][0], s[1][2], s[2][1]);
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			printf("%d ", r[i][j]);
		printf("\n");
	}
	return 0;
}