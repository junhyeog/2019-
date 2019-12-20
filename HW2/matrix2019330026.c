#define _CRT_SECURE_NO_WARNINGS // strtok 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h> // strtok 함수가 선언된 헤더 파일
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일

typedef struct {
	int row; // 행 번호 1~
	int col; // 열 번호 1~
	int val; // 해당 행렬의 값
} element;

//list_pointer 자료구조 정의
typedef struct list_node{
	element data; // 행렬 요소 데이터
	struct list_node *next; // 다음 node를 가르키는 포인터
} *list_pointer;

//삽입 함수 Append 정의
void Append(list_pointer *pptr, element data) {
	list_pointer app_node = NULL;
	app_node = (list_pointer) malloc(sizeof(struct list_node)); //다음 노드를 가르키는 포인터 선언
	app_node->data = data; //다음 노드에 데이터 삽입
	app_node->next = NULL;
	if (*pptr == NULL) // 새 linked_list를 선언
		*pptr = app_node;
	else {// linked list가 선언되어 있다면 마지막 노드까지 탐색하여 그 다음에 다음 노드 추가
		list_pointer last_node = *pptr;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = app_node;
	}
}

//find 함수 정의
list_pointer Find(list_pointer current_node, int row, int col) {
	if (current_node == NULL) return NULL;
	while (current_node->next != NULL) {
		if (current_node->data.row == row && current_node->data.col == col)
			return current_node; // 현재 node의 행과 열이 원하는 값과 같으면 그 요소 반환
		else
			current_node = current_node->next; // 현재 node가 원하는 요소가 아니라면 다음 요소 참조
	}
	if (current_node->data.row == row && current_node->data.col == col) // 마지막 node까지 확인해서
		return current_node; // 원하는 요소 반환
	else
		return NULL; // 아니라면 0 반환
}

//printm 함수 정의
int Printm(list_pointer current_node, FILE* outfp ) {
	if (current_node == NULL) return 0;
	while (current_node->next != NULL) {
		printf("\nresult: %d %d %d\n\n", current_node->data.row, current_node->data.col, current_node->data.val);
		fprintf(outfp, "%d %d %d\n", current_node->data.row, current_node->data.col, current_node->data.val);
		current_node = current_node->next;
	}
	printf("\nresult: %d %d %d\n\n", current_node->data.row, current_node->data.col, current_node->data.val);
	fprintf(outfp, "%d %d %d\n", current_node->data.row, current_node->data.col, current_node->data.val);
}

int main() {

	// 파일 입력 받기
	FILE *infp;
	infp = fopen("matrix.in", "rb");

	// 출력할 파일 생성
	FILE* outfp;
	outfp = fopen("matrix.out", "w");

	// addition의 개수
	int n;
	fscanf(infp, "%d\n", &n);
	fprintf(outfp, "%d\n", n);

	// addition의 개수만큼 반복 실행
	while (n--) {
		// matrix를 저장할 linked list 선언
		list_pointer first_matrix = NULL;

		// 연산 결과의 non-zero element의 수
		int cnt = 0;

		// first_matrix 입력
		int noe; // Number Of non-zero Element
		fscanf(infp, "%d\n", &noe);
		for (int i = 0; i < noe; i++) { //non-zero element의 수만큼 element를 matrix에 추가
			// 공백 문자를 기준으로 문자열을 자르고 포인터 반환
			char elementdata[3005];
			fgets(elementdata, 1000, infp);
			char *ptr = strtok(elementdata, " ");
			// element 추가
			element nze; //Non-Zero Element
			nze.row = atoi(ptr); // 행 데이터
			ptr = strtok(NULL, " "); // 사용한 term 삭제
			nze.col = atoi(ptr); // 열 데이터
			ptr = strtok(NULL, " "); // 사용한 term 삭제
			nze.val = atoi(ptr); // 값 데이터
			ptr = strtok(NULL, " "); // 사용한 term 삭제
			Append(&first_matrix, nze); //element 추가
			cnt += 1;
		}
		// second_matrix 입력
		fscanf(infp, "%d\n", &noe);
		for (int i = 0; i < noe; i++) { //non-zero element의 수만큼 element를 matrix에 추가
			// 공백 문자를 기준으로 문자열을 자르고 포인터 반환
			char elementdata[3005];
			fgets(elementdata, 1000, infp);
			char *ptr = strtok(elementdata, " ");
			// element 추가
			element nze; //Non-Zero Element
			nze.row = atoi(ptr); // 행 데이터
			ptr = strtok(NULL, " "); // 사용한 term 삭제
			nze.col = atoi(ptr); // 열 데이터
			ptr = strtok(NULL, " "); // 사용한 term 삭제
			nze.val = atoi(ptr); // 값 데이터
			ptr = strtok(NULL, " "); // 사용한 term 삭제
			//Append(second_matrix, nze); //element 추가

			// 더하기 연산
			if (Find(first_matrix, nze.row, nze.col) != NULL)
				Find(first_matrix, nze.row, nze.col)->data.val += nze.val;
			else {
				Append(&first_matrix, nze);
				cnt += 1;
			}
		}

		// 연산 결과값 출력
		printf("\nresult: %d\n\n", cnt);
		fprintf(outfp, "%d\n", cnt);
		Printm(first_matrix, outfp);

	}
	// 입출력 파일 닫기
	fclose(infp);
	fclose(outfp);

	return 0;
}
