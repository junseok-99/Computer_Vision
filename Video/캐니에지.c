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

int quan(float num) {
	int tmp = (int)floor(num);

	if (tmp >= 0 && tmp <= 45)
		return 1;
	else if (tmp > 45 && tmp <= 90)
		return 2;
	else if (tmp > 90 && tmp <= 135)
		return 3;
	else if (tmp > 135 && tmp <= 180)
		return 4;
	else if (tmp > 180 && tmp <= 225)
		return 5;
	else if (tmp > 225 && tmp <= 270)
		return 6;
	else if (tmp > 270 && tmp <= 315)
		return 7;
	else if (tmp > 315 && tmp <= 360)
		return 0;
	else
		return -1;
}
void neibohbor1(int tmp,int i, int j ,int* x, int* y) {
	if (tmp == 0 || tmp == 4) {
		*x = j;
		*y = i - 1;
	}
	else if (tmp == 1 || tmp == 5) {
		*x = j + 1;
		*y = i - 1;
	}
	else if (tmp == 2 || tmp == 6) {
		*x = j - 1;
		*y = i;
	}
	else if (tmp == 3 || tmp == 7) {
		*x = j - 1;
		*y = i - 1;
	}
	else
		return;
}
void neibohbor2(int tmp, int i, int j, int* x, int* y) {
	if (tmp == 0 || tmp == 4) {
		*x = j;
		*y = i + 1;
	}
	else if (tmp == 1 || tmp == 5) {
		*x = j - 1;
		*y = i + 1;
	}
	else if (tmp == 2 || tmp == 6) {
		*x = j + 1;
		*y = i;
	}
	else if (tmp == 3 || tmp == 7) {
		*x = j + 1;
		*y = i + 1;
	}
	else
		return;
}

void follow_edge(unsigned char w[][256],int e[][256], char v[][col],int y, int x) {
	v[y][x] = 1;
	w[y][x] = 0;
	int t_l = 50;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (e[y + i][x + j] > t_l && v[y + i][x + i] == 0 && (y+i) != y && (x+j) != x) 
				follow_edge(w, e, v, y + i, x + i);
}

int main() {

	FILE* fp;
	fp = fopen("baboon_before.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];

	int dy;
	int dx;
	int edge_power[row][col];
	int dir_map[row][col];


	int my[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	int mx[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	char visited[row][col]={0,};

	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			if (i == 0 || i == 255 || j == 0 || j == 255) {
				Writebuf[i][j] = 0;
				edge_power[i][j] = 0;
				dir_map[i][j] = 0;
			}
			else {
				int ret = conv(Readbuf, i, j, my);
				dy = ret;
				ret = conv(Readbuf, i, j, mx);
				dx = ret;
				edge_power[i][j] = sqrt(pow(dy, 2) + pow(dy, 2));
				dir_map[i][j] = quan(dx == 0 ? 0 : 90.0 - fabs((atan((double)dy / (double)dx))));
				if (edge_power[i][j] >= 124)
					Writebuf[i][j] = 0;
				else if (edge_power[i][j] < 124)
					Writebuf[i][j] = 255;
			}
		}
	}

	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			int x1, x2, y1, y2;
			neibohbor1(dir_map[i][j], i, j, &x1, &y1);
			neibohbor2(dir_map[i][j], i, j, &x2, &y2);
			if (edge_power[y1][x1] >= edge_power[i][j] || edge_power[y2][x2] >= edge_power[i][j])
				edge_power[i][j] = 0;
		}
	}

	int t_h = 150;

	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			if (edge_power[i][j] > t_h && visited[i][j] == 0)
				follow_edge(Writebuf,edge_power,visited,i, j);
		}
	}

	fp = fopen("prac_ret.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}