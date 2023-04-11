#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

#define row 256
#define col 256

void sort(unsigned char a[9]) {

	int key, i, j;
	for (i = 1; i < 9; i++) {
		key = a[i];
		for (j = i-1; j >= 0 && a[j] > key; j--)
			a[j+1] = a[j];
		a[++j] = key;
	}
}
unsigned int median(unsigned char read[][256], int a, int b) {
	unsigned char tmp[9];
	int cnt = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			tmp[cnt++] = read[a + i][b + j];
		}
	}
	sort(tmp);
	
	return tmp[cnt / 2];
}
int main() {

	FILE* fp;
	fp = fopen("prac_ret.raw", "rb");

	unsigned char Readbuf[row][col];
	unsigned char Writebuf[row][col];

	

	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++) {
			if (i == 0 || i == 255 || j == 0 || j == 255)
				Writebuf[i][j] = 0;
			else {
				Writebuf[i][j] = median(Readbuf, i, j);
			}
		}
	
	fp = fopen("prac_ret2.raw", "wb");

	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}