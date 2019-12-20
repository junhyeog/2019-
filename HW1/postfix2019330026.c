#define _CRT_SECURE_NO_WARNINGS // strtok 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h> // strtok 함수가 선언된 헤더 파일

//stack 자료구조 정의
typedef struct {
	int item[1000];
	int top;
}stack;
//스택이 다 찼는가?
int IsFull(stack* ps) {
	return (ps->top == 999);
}
//스택이 비었는가?
int IsEmpty(stack* ps) {
	return (ps->top < 0);
}
//스택의 가장 위에 in 삽입
int Push(stack* ps, int in) {
	if (IsFull(ps) > 0) return 0;
	ps->item[++ps->top] = in;
	return 1;
}
//스택의 가장 위 값 방출
int Pop(stack* ps, int* out) {
	if (IsEmpty(ps) > 0) return 0;
	*out = ps->item[ps->top--];
	return 1;
}

int main() {
	// 숫자를 저장할 스택 s 선언
	stack s;
	//스택 초기화
	s.top = -1;

	// 파일 입력 받기
	FILE *infp;
	infp = fopen("postfix.in", "rb");

	// 출력할 파일 생성
	FILE* outfp;
	outfp = fopen("postfix.out", "w");

	// expression의 개수
	int n;
	fscanf(infp, "%d\n", &n);
	fprintf(outfp, "%d\n", n);

	// expression의 개수만큼 반복 실행
	while (n--) {
		// expression 입력
		char expression[1001];
		fgets(expression, 1000, infp);

		// 공백 문자를 기준으로 문자열을 자르고 포인터 반환
		char *ptr = strtok(expression, " ");

		// expression이 끝날 때 까지 반복
		while (ptr != NULL) {
			if (48 <= ptr[0] && ptr[0] <= 57) {
				// 숫자일 때 스택에 저장
				int term = atoi(ptr);
				Push(&s, term);
				printf("term= %d\n", term);
			}
			else if (ptr[0] == '+') {
				// 스택의 상위 두 원소 a, b를 더해서 연산한 후, 결과값 저장
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b + a;
				Push(&s, c);
				printf("%d + %d = %d\n", b, a, c);
			}
			else if (ptr[0] == '-') {
				// 스택의 상위 두 원소 a, b를 더해서 연산한 후, 결과값 저장
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b - a;
				Push(&s, c);
				printf("%d - %d = %d\n", b, a, c);
			}
			else if (ptr[0] == '*') {
				// 스택의 상위 두 원소 a, b를 더해서 연산한 후, 결과값 저장
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b * a;
				Push(&s, c);
				printf("%d * %d = %d\n", b, a, c);
			}
			else if (ptr[0] == '/') {
				// 스택의 상위 두 원소 a, b를 더해서 연산한 후, 결과값 저장
				int a, b;
				Pop(&s, &a);
				Pop(&s, &b);
				int c = b / a;
				Push(&s, c);
				printf("%d / %d = %d\n", b, a, c);
			}
			else {
				// 숫자나 연산자가 아닌 다른 문자가 입력된 경우 삭제 
				ptr = strtok(NULL, " "); // 사용한 term 삭제
			}
			ptr = strtok(NULL, " "); // 사용한 term 삭제
		}

		// 연산 결과값 출력
		printf("\nresult: %d\n\n", s.item[s.top]);
		fprintf(outfp, "%d\n", s.item[s.top]);

		// 스택 초기화
		s.top = -1;
	}
	// 입출력 파일 닫기
	fclose(infp);
	fclose(outfp);

	return 0;
}