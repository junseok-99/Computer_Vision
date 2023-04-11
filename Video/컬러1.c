#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int main() {

	FILE* fp;
	unsigned char ReadBuf[3][256][366];
	int r_c = 0, g_c = 0, b_c = 0, cnt=0;

	fp = fopen("ansisung2.raw", "rb");
	
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 3000; j++) {
			if (cnt == 0)
				fread(ReadBuf[cnt++][i][r_c++], 1, 1, fp);
			else if (cnt == 1)
				fread(ReadBuf[cnt++][i][g_c++], 1, 1, fp);
			else if (cnt == 2)
				fread(ReadBuf[cnt++][i][b_c++], 1, 1, fp);
			else
				cnt = 0;
		}
		r_c = 0, g_c = 0, b_c = 0, cnt = 0;
	}
				
	fclose(fp);

	printf("%d", ReadBuf[0][0][0]);
	return 0;
}