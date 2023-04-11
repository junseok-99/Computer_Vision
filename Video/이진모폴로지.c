#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int reduce(int sam[][10], int m[3], int y, int x) {
	int q = 1;
	int a[3];
	for (int i = -1; i <= 1; i++)
		a[q + i] = sam[y][x + i] & m[q + i];

	return (a[0] & a[1] & a[2]);
}
int reduce2(int sam[][8], int m[3], int y, int x) {
	int q = 1;
	int a[3];
	for (int i = -1; i <= 1; i++)
		if (x + i < 0)
			a[0] = 0;
		else if (x + i > 7)
			a[2] = 0;
		else
			a[q + i] = sam[y][x + i] & m[q + i];

	return (a[0] & a[1] & a[2]);
}
int extend(int sam[][10], int m[3], int y, int x) {
	int q = 1,ret;
	int a[3];
	for (int i = -1; i <= 1; i++) 
		a[q + i] = sam[y][x + i] & m[q + i];
	
	return (a[0] | a[1] | a[2]);
}
int extend2(int sam[][8], int m[3], int y, int x) {
	int q = 1;
	int a[3];
	for (int i = -1; i <= 1; i++)
		if (x+i < 0)
			a[0] = 0;
		else if (x+i > 7)
			a[2] = 0;
		else
			a[q + i] = sam[y][x + i] & m[q + i];

	return (a[0] | a[1] | a[2]);
}

int main() {
	
	int sam[10][10] = { {0,0,0,0,0,0,0,0,0,0}, {0,0,1,1,0,0,0,1,0,0},{0,0,1,1,0,0,0,1,0,0},
	{0,0,1,1,1,0,0,1,0,0},{0,0,1,1,1,0,0,1,0,0},{0,0,1,1,1,1,1,1,0,0},{0,0,0,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0} };
	int sam2[8][8] = { {0,0,0,0,0,0,0,0}, {0,1,1,0,0,0,1,0},{0,1,1,0,0,0,1,0},
	{0,1,1,1,0,0,1,0},{0,1,1,1,0,0,1,0},{0,1,1,1,1,1,1,0},{0,0,0,0,1,1,1,0},{0,0,0,0,0,0,0,0} };
	int out[8][8];
	int out2[8][8];
	int m[3] = { 1,1,1 };

	for(int i=0;i<8;i++)
		for (int j = 0; j <8; j++) {
			out[i][j] = reduce2(sam2, m, i, j);
		}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			out2[i][j] = extend2(out, m, i, j);
		}
		
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			printf("%d ", out2[i][j]);
		printf("\n");
	}
	return 0;
}