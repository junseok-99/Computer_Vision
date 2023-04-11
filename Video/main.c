#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>


int main() {

	FILE* fp;
	unsigned char Readbuf[512][512];
	unsigned char Writebuf[512][512];
	unsigned int His[256] = { 0, }; //������׷�
	double N[256]; //����ȭ

	double w0 = 0.0, w1 = 0.0;
	double u0 = 0.0, u1 = 0.0;
	double v0 = 0.0, v1 = 0.0;

	int t;
	int T; //�Ӱ谪
	int min_value = INT_MAX;//�ּڰ�

	fp = fopen("SemiconductNoise512_before.raw", "rb");
	for (int i = 0; i < 512; i++)
		fread(Readbuf[i], 1, 512, fp);
	fclose(fp);

	for (int i = 0; i < 512; i++) //������׷�
		for (int j = 0; j < 512; j++) 
			His[Readbuf[i][j]]++;

	for (int i = 0; i < 256; i++) //����ȭ
		N[i] = His[i] / 262144.0;

	
	for (int k = 0; k < 256; k++) { //�ּڰ� ã��

		t = k;

		for (int i = 0; i <= t; i++) //����ȭ�� ��
			w0 += N[i];
		for (int i = t+1; i <= 255; i++)
			w1 += N[i];

		for (int i = 0; i <= t; i++) // i x h'(i)
			u0 += i * N[i];
		for (int i = t+1; i <= 255; i++)
			u1 += i * N[i];
		
		u0 /= w0;	//����ȭ ���
		u1 /= w1;	//����ȭ ���
		
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

		//�� �ʱ�ȭ
		w0 = 0.0;
		w1 = 0.0;
		u0 = 0.0;
		u1 = 0.0;
		v0 = 0.0;
		v1 = 0.0;
	}
	
	for (int i = 0; i < 512; i++) //����ȭ
		for (int j = 0; j < 512; j++) {
			if (Readbuf[i][j] >= T)
				Readbuf[i][j] = 255;
			else
				Readbuf[i][j] = 0;
		}

	//���� ����
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; j++)
			Writebuf[i][j] = Readbuf[i][j];

	//���� ����
	fp = fopen("SemiconductNoise512_after.raw", "wb");
	for (int i = 0; i < 512; i++)
		fwrite(Writebuf[i], 1, 512, fp);
	fclose(fp);

	return 0;
}