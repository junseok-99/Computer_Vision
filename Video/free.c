#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

#define x 256
#define y 256
#define Q_SIZE 65536

int Q[Q_SIZE];
int front = -1;
int rear = -1;
void Add(int num) {
    rear = (rear + 1) % Q_SIZE;
    Q[rear] = num;
}
int Del() {
    front = (front + 1) % Q_SIZE;
    return Q[front];
}
int isEmpty() {
    if (front == rear)
        return 1;
    else
        return 0;
}
void efficient_floodfill4(int[][256], int, int, int);

int main() {

    FILE* fp;
    unsigned char Readbuf[256][256];
    unsigned char Writebuf[256][256];
    unsigned int His[256] = { 0, }; //������׷�
    double N[256]; //����ȭ

    double w0 = 0.0, w1 = 0.0;
    double u0 = 0.0, u1 = 0.0;
    double v0 = 0.0, v1 = 0.0;

    int t;
    int T; //�Ӱ谪
    int min_value = INT_MAX;//�ּڰ�

    fp = fopen("lena_before.raw", "rb");
    for (int i = 0; i < 256; i++)
        fread(Readbuf[i], 1, 256, fp);
    fclose(fp);

    for (int i = 0; i < 256; i++) //������׷�
        for (int j = 0; j < 256; j++)
            His[Readbuf[i][j]]++;

    for (int i = 0; i < 256; i++) //����ȭ
        N[i] = His[i] / 262144.0;


    for (int k = 0; k < 256; k++) { //�ּڰ� ã��

        t = k;

        for (int i = 0; i <= t; i++) //����ȭ�� ��
            w0 += N[i];
        for (int i = t + 1; i <= 255; i++)
            w1 += N[i];

        for (int i = 0; i <= t; i++) // i x h'(i)
            u0 += i * N[i];
        for (int i = t + 1; i <= 255; i++)
            u1 += i * N[i];

        u0 /= w0;   //����ȭ ���
        u1 /= w1;   //����ȭ ���

        for (int i = 0; i <= t; i++) //h'(i)( i-u(t))^2
            v0 += (N[i]) * ((i - u0) * (i - u0));
        for (int i = t + 1; i <= 255; i++)
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

    for (int i = 0; i < 256; i++) //����ȭ
        for (int j = 0; j < 256; j++) {
            if (Readbuf[i][j] >= T)
                Readbuf[i][j] = 255;
            else
                Readbuf[i][j] = 0;
        }

    //--------------------------------------------------

    int copy[x][y]; //���纻
    unsigned int label = 1;

    for (int i = 0; i < 256; i++) //�������� ����
        for (int j = 0; j < 256; j++) {
            if (i == 0 || i == 255 || j == 0 || j == 255)
                copy[i][j] = 0;
            else
                copy[i][j] = Readbuf[i][j] == 255 ? -1 : 0;
        }

    for (int i = 0; i < 255; i++) //����ä��
        for (int j = 0; j < 255; j++)
            if (copy[i][j] == -1) {
                efficient_floodfill4(copy, i, j, label);
                label++;
            }

    //----------------------------------------------------
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++)
            printf("%d ", copy[i][j]);
        printf("\n");
    }

    //���� ����
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[i][j] = Readbuf[i][j];

    //���� ����
    fp = fopen("lena_after.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}
void efficient_floodfill4(int L[][256], int i, int j, int label) {
    int point_x, point_y;
    Add(i);
    Add(j);

    while (!isEmpty()) {
        point_x = Del();
        point_y = Del();


        if (L[point_x][point_y] == -1) {
            int left = point_y;
            int right = point_y;

            while (L[point_x][left - 1] == -1)
                left--;
            while (L[point_x][right + 1] == -1)
                right++;

            for (int c = left; c <= right; c++) {
                L[point_x][c] = label;
                if (L[point_x - 1][c] == -1 && (c == left || L[point_x - 1][c - 1] != -1)) {
                    Add(point_x - 1);
                    Add(c);
                }
                if (L[point_x + 1][c] == -1 && (c == left || L[point_x + 1][c - 1] != -1)) {
                    Add(point_x + 1);
                    Add(c);
                }
            }

        }
    }
}