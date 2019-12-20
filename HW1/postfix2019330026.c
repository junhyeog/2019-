#define _CRT_SECURE_NO_WARNINGS // strtok ���� ���� ���� ������ ���� ����
#include <stdio.h>
#include <string.h> // strtok �Լ��� ����� ��� ����

//stack �ڷᱸ�� ����
typedef struct {
	int item[1000];
	int top;
}stack;
//������ �� á�°�?
int IsFull(stack* ps) {
	return (ps->top == 999);
}
//������ ����°�?
int IsEmpty(stack* ps) {
	return (ps->top < 0);
}
//������ ���� ���� in ����
int Push(stack* ps, int in) {
	if (IsFull(ps) > 0) return 0;
	ps->item[++ps->top] = in;
	return 1;
}
//������ ���� �� �� ����
int Pop(stack* ps, int* out) {
	if (IsEmpty(ps) > 0) return 0;
	*out = ps->item[ps->top--];
	return 1;
}

int main() {
	// ���ڸ� ������ ���� s ����
	stack s;
	//���� �ʱ�ȭ
	s.top = -1;

	// ���� �Է� �ޱ�
	FILE *infp;
	infp = fopen("postfix.in", "rb");

	// ����� ���� ����
	FILE* outfp;
	outfp = fopen("postfix.out", "w");

	// expression�� ����
	int n;
	fscanf(infp, "%d\n", &n);
	fprintf(outfp, "%d\n", n);

	// expression�� ������ŭ �ݺ� ����
	while (n--) {
		// expression �Է�
		char expression[1001];
		fgets(expression, 1000, infp);

		// ���� ���ڸ� �������� ���ڿ��� �ڸ��� ������ ��ȯ
		char *ptr = strtok(expression, " ");

		// expression�� ���� �� ���� �ݺ�
		while (ptr != NULL) {
			if (48 <= ptr[0] && ptr[0] <= 57) {
				// ������ �� ���ÿ� ����
				int term = atoi(ptr);
				Push(&s, term);
				printf("term= %d\n", term);
			}
			else if (ptr[0] == '+') {
				// ������ ���� �� ���� a, b�� ���ؼ� ������ ��, ����� ����
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b + a;
				Push(&s, c);
				printf("%d + %d = %d\n", b, a, c);
			}
			else if (ptr[0] == '-') {
				// ������ ���� �� ���� a, b�� ���ؼ� ������ ��, ����� ����
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b - a;
				Push(&s, c);
				printf("%d - %d = %d\n", b, a, c);
			}
			else if (ptr[0] == '*') {
				// ������ ���� �� ���� a, b�� ���ؼ� ������ ��, ����� ����
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b * a;
				Push(&s, c);
				printf("%d * %d = %d\n", b, a, c);
			}
			else if (ptr[0] == '/') {
				// ������ ���� �� ���� a, b�� ���ؼ� ������ ��, ����� ����
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b / a;
				Push(&s, c);
				printf("%d / %d = %d\n", b, a, c);
			}
			else {
				// ���ڳ� �����ڰ� �ƴ� �ٸ� ���ڰ� �Էµ� ��� ���� 
				ptr = strtok(NULL, " "); // ����� term ����
			}
			ptr = strtok(NULL, " "); // ����� term ����
		}

		// ���� ����� ���
		printf("\nresult: %d\n\n", s.item[s.top]);
		fprintf(outfp, "%d\n", s.item[s.top]);

		// ���� �ʱ�ȭ
		s.top = -1;
	}
	// ����� ���� �ݱ�
	fclose(infp);
	fclose(outfp);

	return 0;
}