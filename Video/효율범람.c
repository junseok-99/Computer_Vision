#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

#define row 256
#define col 256
int q[65000];
int front=0, rear=-1;
int cnt = 0;

void add(int data) {
	rear = (rear + 1) % 65000;
	q[rear] = data;
	cnt++;
}
int remove() {
	int num = q[front];
	front = (front + 1) % 65000;
	cnt--;
	return num;
}
bool isempty() {
	if (cnt == 0)
		return true;
	else if (cnt > 0)
		return false;
}
void effi_floor(int a[][col], int i, int j, int label) {
	add(j);
	add(i);
	int x, y, left, right;
	while (!isempty()) {
		
		x = remove();
		y = remove();
		
		if (a[y][x] == -1) {
			left = x, right = x; 
			while (a[y][left - 1] == -1) left--;
			while (a[y][right + 1] == -1) right++;

			for (int c = left; c <= right; c++) {
				a[y][c] = label;
				if (a[y - 1][c] == -1&& (c==left || a[y-1][c-1] != -1)) {
					add(c);
					add(y - 1);
				}
				if (a[y + 1][c] == -1 && (c == left || a[y + 1][c - 1] != -1)) {
					add(c);
					add(y + 1);
				}
				if (a[y - 1][c - 1] == -1) {
					add(c - 1);
					add(y - 1);
				}
				if (a[y - 1][c + 1] == -1) {
					add(c + 1);
					add(y - 1);
				}
				if (a[y + 1][c - 1] == -1) {
					add(c - 1);
					add(y + 1);
				}
				if (a[y + 1][c + 1] == -1) {
					add(c + 1);
					add(y + 1);
				}
				
			}
		}
	}
}
int main() {

	FILE* fp;
	fp = fopen("lena_before.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];
	unsigned int Hist[row]={0};
	double N[row];
	int T;
	double min_dbl = DBL_MAX;
	double div = row * col;
	double w0, w1, u0, u1, v0, v1;

	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < row; i++)
		for(int j=0;j<row;j++)
			Hist[Readbuf[i][j]]++;

	for (int i = 0; i < row; i++)
		N[i] = Hist[i] / (double)(row * col);
	
	for (int t = 0; t < row; t++) {
		w0 = 0.0, w1 = 0.0, u0 = 0.0, u1 = 0.0, v0 = 0.0, v1 = 0.0;

		for (int i = 0; i <= t; i++)
			w0 += N[i];
		for (int i = t+1; i <= row-1; i++)
			w1 += N[i];

		for (int i = 0; i <= t; i++)
			u0 += (i*N[i]);
		for (int i = t+1; i <= row-1; i++)
			u1 += (i * N[i]);

		u0 = w0 == 0 ? 0 : u0 / w0;
		u1 = w1 == 0 ? 0 : u1 / w1;

		for (int i = 0; i <= t; i++)
			v0 += (N[i])*((i-u0) * (i - u0));
		for (int i = t + 1; i <= row - 1; i++)
			v1 += (N[i]) * ((i - u1) * (i - u1));

		v0 = w0 == 0 ? 0 : v0 / w0;
		v1 = w1 == 0 ? 0 : v1 / w1;

		double ret = (w0 * v0) + (w1 * v1);

		if (ret < min_dbl) {
			min_dbl = ret;
			T = t;
		}
	}

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			Writebuf[i][j] = Readbuf[i][j] > T ? 255 : 0;

	int tmp[row][col];
	int label=1;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++) {
			if (i == 0 || i == row - 1 || j == 0 || j == row - 1)
				tmp[i][j] = 0;
			else
				tmp[i][j] = Writebuf[i][j] > 0 ? -1 : 0;
		}

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++) {
			if (tmp[i][j] == -1) {
				effi_floor(tmp, i, j, label);
				label++;
			}
		}
	for (int i = 0; i < row; i++) {
		for (int j = 31; j < 75; j++)
			printf("%3d ", tmp[i][j]);
		printf("\n");
	}
	
	fp = fopen("prac_ret.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(tmp[i], 1, 256, fp);
	fclose(fp);

	return 0;
}