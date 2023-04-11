#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>


int main() {

	FILE* fp;
	unsigned char Readbuf[512][512];
	unsigned char Writebuf[512][512];
	unsigned int His[256] = { 0, }; //히스토그램
	double N[256]; //정규화

	double w0 = 0.0, w1 = 0.0;
	double u0 = 0.0, u1 = 0.0;
	double v0 = 0.0, v1 = 0.0;

	int t;
	int T; //임계값
	int min_value = INT_MAX;//최솟값

	fp = fopen("SemiconductNoise512_before.raw", "rb");
	for (int i = 0; i < 512; i++)
		fread(Readbuf[i], 1, 512, fp);
	fclose(fp);

	for (int i = 0; i < 512; i++) //히스토그램
		for (int j = 0; j < 512; j++) 
			His[Readbuf[i][j]]++;

	for (int i = 0; i < 256; i++) //정규화
		N[i] = His[i] / 262144.0;

	
	for (int k = 0; k < 256; k++) { //최솟값 찾기

		t = k;

		for (int i = 0; i <= t; i++) //정규화의 합
			w0 += N[i];
		for (int i = t+1; i <= 255; i++)
			w1 += N[i];

		for (int i = 0; i <= t; i++) // i x h'(i)
			u0 += i * N[i];
		for (int i = t+1; i <= 255; i++)
			u1 += i * N[i];
		
		u0 /= w0;	//정규화 평균
		u1 /= w1;	//정규화 평균
		
		for (int i = 0; i <= t; i++) //h'(i)( i-u(t))^2
			v0 += (N[i]) * ((i - u0) * (i - u0));
		for (int i = t+1; i <= 255; i++)
			v1 += (N[i]) * ((i - u1) * (i - u1));

		v0 /= w0; //v0
		v1 /= w1; //v1
		
		double v_sum = (w0 * v0) + (w1 * v1);
		
		if (v_sum <= min_value) {
			min_value = v_sum;
			T = k;
		}

		//값 초기화
		w0 = 0.0;
		w1 = 0.0;
		u0 = 0.0;
		u1 = 0.0;
		v0 = 0.0;
		v1 = 0.0;
	}
	
	for (int i = 0; i < 512; i++) //이진화
		for (int j = 0; j < 512; j++) {
			if (Readbuf[i][j] >= T)
				Readbuf[i][j] = 255;
			else
				Readbuf[i][j] = 0;
		}

	//영상 편집
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; j++)
			Writebuf[i][j] = Readbuf[i][j];

	//영상 저장
	fp = fopen("SemiconductNoise512_after.raw", "wb");
	for (int i = 0; i < 512; i++)
		fwrite(Writebuf[i], 1, 512, fp);
	fclose(fp);

	return 0;
}