#define _CRT_SECURE_NO_WARNINGS // strtok 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일
#include <string.h> // strtok 함수가 선언된 헤더 파일

typedef struct node{
	int val; // 해당 node의 값
	struct node *parent; // 해당 node의 값
	struct node *left; // 해당 node의 왼쪽 자식의 주소
	struct node *right; // 해당 node의 오른쪽 자식의 주소
} *node_pointer;

typedef struct min_heap {
	struct node *root;
	int size; // 해당 min heap에 속한 node의 개수
} *min_heap_pointer;
void inorder(node_pointer ptr, FILE *outfp) {
	if (ptr == NULL) {
		return;
	}
	inorder(ptr->left, outfp);
	fprintf(outfp, " %d", ptr->val);
	inorder(ptr->right, outfp);
}
void preorder(node_pointer ptr, FILE *outfp) {
	if (ptr == NULL) {
		return;
	}
	fprintf(outfp, " %d", ptr->val);
	preorder(ptr->left, outfp);
	preorder(ptr->right, outfp);
}

void swap(node_pointer *a, node_pointer *b) {
	int temp = (*a)->val;
	(*a)->val = (*b)->val;
	(*b)->val = temp;
	return;
}


//삽입 함수 Insert 정의
void Insert(min_heap_pointer *pptr, int val) {
	//node_pointer new_node = NULL;
	node_pointer new_node = (node_pointer)malloc(sizeof(struct node)); //다음 노드를 가르키는 포인터 선언
	new_node->val = val; //다음 노드에 데이터 삽입
	new_node->parent = NULL;
	new_node->left= NULL;
	new_node->right = NULL;
	if ((*pptr)->root == NULL) { // 새로운 min heap을 선언
		(*pptr)->root = new_node;
		(*pptr)->size = 1;
	}
	else {// min heap이 선언되어 있다면
		// 삽입될 위치 찾기
		int position = (*pptr)->size + 1;
		int direction[100] = { 0, }; // 방향을 저장
		int cnt = 0; // 방향을 뒤에서 부터 읽어야하기 때문에 방향의 개수 저장
		while (position != 1) {
			direction[cnt] = position % 2;
			cnt += 1;
			position /= 2;
		}
		node_pointer *temp_node = (node_pointer)malloc(sizeof(struct node));
		*temp_node = (*pptr)->root;
		for (int i = cnt - 1; i > 0; i--) {
			// 자리를 찾아가는 동안 그 부모와 값을 비교해서 swap
			if ((*temp_node)->val > new_node->val)
				swap(temp_node, &new_node);
			if (direction[i] == 0) {
				*temp_node = (*temp_node)->left;
			}
			else if (direction[i] == 1) {
				*temp_node = (*temp_node)->right;
			}
			else {
				printf("direction error");
				return;
			}
		}
		new_node->parent = *temp_node;
		// 자리를 찾아가는 동안 그 부모와 값을 비교해서 swap
		if ((*temp_node)->val > new_node->val)
			swap(temp_node, &new_node);
		if (direction[0] == 0) {
			(*temp_node)->left = new_node;
		}
		else if (direction[0] == 1) {
			(*temp_node)->right = new_node;
		}
		else {
			printf("direction error");
			return;
		}
		(*pptr)->size = (*pptr)->size + 1;
	}
	return;
}

int Delete(min_heap_pointer *pptr, int* out) {
	if ((*pptr)->size == 0) { // 빈 heap이면 0 리턴
		return 0;
	}
	else if ((*pptr)->size == 1) { // 마지막 값을 삭제하고 0 리턴
		*out = (*pptr)->root->val;
		(*pptr)->root = NULL;
		(*pptr)->size = 0;
		return 0;
	}
	*out = (*pptr)->root->val;
	int position = (*pptr)->size;
	int direction[100] = { 0, }; // 방향을 저장
	int cnt = 0; // 방향을 뒤에서 부터 읽어야하기 때문에 방향의 개수 저장
	while (position != 1) {
		direction[cnt] = position % 2;
		cnt += 1;
		position /= 2;
	}
	node_pointer *temp_node = (node_pointer)malloc(sizeof(struct node));
	node_pointer *last_node = (node_pointer)malloc(sizeof(struct node));
	*temp_node = (*pptr)->root;
	for (int i = cnt - 1; i > 0; i--) {
		if (direction[i] == 0) {
			*temp_node = (*temp_node)->left;
		}
		else if (direction[i] == 1) {
			*temp_node = (*temp_node)->right;
		}
		else {
			printf("direction error");
			return;
		}
	}
	if (direction[0] == 0) {
		*last_node = (*temp_node)->left;
		(*temp_node)->left = NULL;
	}
	else if (direction[0] == 1) {
		*last_node = (*temp_node)->right;
		(*temp_node)->right = NULL;
	}
	else {
		printf("direction error");
		return;
	}
	(*pptr)->size = (*pptr)->size - 1;
	(*pptr)->root->val = (*last_node)->val;
	*last_node = (*pptr)->root;
	while ((*last_node)->left!=NULL || (*last_node)->right != NULL) {
		int direction;
		if ((*last_node)->left == NULL) {
			direction = 1;
		}
		else if ((*last_node)->right == NULL) {
			direction = 0;
		}
		else {
			direction = (*last_node)->left->val < (*last_node)->right->val ? 0 : 1;
		}
		if (direction == 0) {
			int temp = (*pptr)->root->left->val;
			if (temp > (*last_node)->val)
				break;
			swap(last_node, &((*last_node)->left));
			*last_node = (*last_node)->left;
		}
		else if (direction == 1) {
			int temp = (*pptr)->root->right->val;
			if (temp > (*last_node)->val)
				break;
			swap(last_node, &((*last_node)->right));
			*last_node = (*last_node)->right;
		}
		else {
			printf("delete error");
			break;
		}
	}
	return 1;
}

int main() {
	//min_heap_pointer new_heap = NULL;
	min_heap_pointer heap = (min_heap_pointer)malloc(sizeof(struct min_heap));
	heap->root = NULL;
	heap->size = 0;
	// 파일 입력 받기
	FILE *infp;
	infp = fopen("heapsort.in", "rb");

	// 출력할 파일 생성
	FILE* outfp;
	outfp = fopen("heapsort.out", "w");

	int n;
	fscanf(infp, "%d\n", &n); // 정렬할 배열 개수 입력
	fprintf(outfp, "%d\n", n); // 정렬할 배열 개수 출력
	// 배열 개수만큼 반복
	while (n--) {
		// instances 입력
		char instances[10001];
		fgets(instances, 10000, infp);

		// 공백 문자를 기준으로 문자열을 자르고 포인터 반환
		char *ptr = strtok(instances, " ");
		// 문자열이 끝날 때까지 반복
		while (ptr != NULL) {
			int val = atoi(ptr);
			Insert(&heap, val);
			ptr = strtok(NULL, " "); // 사용한 term 삭제
		}
		// inorder 출력
		fprintf(outfp, "I");
		inorder(heap->root, outfp);
		fprintf(outfp, "\n");
		// preorder 출력
		fprintf(outfp, "P");
		preorder(heap->root, outfp);
		fprintf(outfp, "\n");
		int out;
		while (Delete(&heap, &out) != 0) { // heap에서 가장 작은 node를 삭제하면서
			fprintf(outfp, "%d ", out); // 값 출력
		}
		fprintf(outfp, "%d\n", out); // 마지막 값 출력
	}
	// 입출력 파일 닫기
	fclose(infp);
	fclose(outfp);
	return 0;
}
