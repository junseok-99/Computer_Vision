#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int reduce(int sam[][8], int m[3], int y, int x) {
	int q = 1;
	int a[3];
	for (int i = -1; i <= 1; i++)
		if (x + i < 0)
			a[0] = 0 - m[0];
		else if (x + i > 7)
			a[2] = 0 - m[2];
		else
			a[q + i] = sam[y][x + i] - m[q + i];

	return mins(a);
}

int extend(int sam[][8], int m[3], int y, int x) {
	int q = 1;
	int a[3];
	for (int i = -1; i <= 1; i++)
		if (x + i < 0)
			a[0] = 0 + m[0];
		else if (x + i > 7)
			a[2] = 0 + m[2];
		else
			a[q + i] = sam[y][x + i] + m[q + i];
	
	return maxs(a);
}

int maxs(int a[3]) {
	int max_n = a[0];
	for (int i = 1; i <= 2; i++)
		if (max_n < a[i])
			max_n = a[i];

	return max_n;
}
int mins(int a[3]) {
	int min_n = a[0];
	for (int i = 1; i <= 2; i++)
		if (min_n > a[i])
			min_n = a[i];

	return min_n;
}

int main() {

	int sam[8][8] = { {0,0,0,0,0,0,0,0}, {0,1,1,0,0,0,1,0},{0,1,2,0,0,0,1,0},
	{0,1,3,1,0,0,2,0},{0,1,3,1,0,0,2,0},{0,1,2,3,4,4,3,0},{0,0,0,0,1,3,1,0},{0,0,0,0,0,0,0,0}};
	int out[8][8];
	int out2[8][8];
	int m[3] = { 0,0,0 };

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			out[i][j] = reduce(sam, m, i, j);
		}
	/*for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			out2[i][j] = extend(out, m, i, j);
		}
	*/
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			printf("%d ", out[i][j]);
		printf("\n");
	}
	return 0;
}