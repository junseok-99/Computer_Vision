#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

int comp(const void* a, const void* b)
{
	if (*(int*)a > *(int*)b) return  1;
	if (*(int*)a < *(int*)b) return -1;
	return 0;
}

int main() {

	FILE* fp;
	unsigned char Readbuf[256][256];
	unsigned char Writebuf[256][256];
	double M[3][3] = {0,-1,0, -1,5,-1,0,-1,0}; //마스크


	fp = fopen("salt_before.raw", "rb");
	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp);
	fclose(fp);

	// 컨볼루션
	/*
	for (int i = 0; i<256; i++)
		for (int j = 0; j < 256; j++) {
			if (j == 0 || i == 0 || j == 255 || i == 255) 
				Writebuf[i][j] = 0;
			else if ((i > 0 && j > 0) && (j<255 && i<255)) {
				int ret = (Readbuf[i - 1][j - 1] * M[0][0]) + (Readbuf[i - 1][j] * M[0][1]) + (Readbuf[i - 1][j + 1] * M[0][2])
					+ (Readbuf[i][j - 1] * M[1][0]) + (Readbuf[i][j] * M[1][1]) + (Readbuf[i][j + 1] * M[1][2])
					+ (Readbuf[i + 1][j - 1] * M[2][0]) + (Readbuf[i + 1][j] * M[2][1]) + (Readbuf[i + 1][j + 1] * M[2][2]);
				if (ret < 0)
					Writebuf[i][j] = 0;
				else
					Writebuf[i][j] = ret;
			}
		}
	*/

	//메디안
	
	int tmp[20];
	int sums=0, cnt=0;
	int l=0, r;
	for (int i = 0; i < 256; i++) {
		l = 0;
		for (int j = 0; j < 256; j++)
			if (j == 0 || j % 9 != 0) {
				tmp[cnt++] = Readbuf[i][j];
			}
			else if (j % 9 == 0 || j == 255) {
				r = j;
				qsort(tmp, cnt, sizeof(int), comp);
				Readbuf[i][(r - l) / 2] = tmp[cnt / 2];
				l = j + 1;
				cnt = 0;
				printf("%d ", Readbuf[i][j]);
			}
	}
	
	//영상 편집
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			Writebuf[i][j] = Readbuf[i][j];

	//영상 저장
	fp = fopen("Result.raw", "wb");
	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp);
	fclose(fp);

	return 0;
}