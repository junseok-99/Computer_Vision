#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

int len(char* ptr) {
	int cnt = 0;
	for (int i = 0; *(ptr + i) != '\0'; i++)
		cnt++;

	return cnt;
}
int main() {

	char in[6];
	scanf("%s", in);

	char* ptr = in;
	int i;

	for (i = 0; i < len(ptr); i++) {
		if (*(ptr + i) >= 'a' && *(ptr + i) <= 'z')
			*(ptr + i) -= 32;
		else {
			printf("�ҹ��ڰ� �ƴϹǷ� ��ȯ�� �Ұ����մϴ�.");
			break;
		}
	}
	if (i == len(ptr))
		printf("%s", ptr);
	
	return 0;
}