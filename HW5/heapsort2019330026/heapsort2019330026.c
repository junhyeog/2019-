#define _CRT_SECURE_NO_WARNINGS // strtok ���� ���� ���� ������ ���� ����
#include <stdio.h>
#include <stdlib.h>    // malloc, free �Լ��� ����� ��� ����
#include <string.h> // strtok �Լ��� ����� ��� ����

typedef struct node{
	int val; // �ش� node�� ��
	struct node *parent; // �ش� node�� ��
	struct node *left; // �ش� node�� ���� �ڽ��� �ּ�
	struct node *right; // �ش� node�� ������ �ڽ��� �ּ�
} *node_pointer;

typedef struct min_heap {
	struct node *root;
	int size; // �ش� min heap�� ���� node�� ����
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


//���� �Լ� Insert ����
void Insert(min_heap_pointer *pptr, int val) {
	//node_pointer new_node = NULL;
	node_pointer new_node = (node_pointer)malloc(sizeof(struct node)); //���� ��带 ����Ű�� ������ ����
	new_node->val = val; //���� ��忡 ������ ����
	new_node->parent = NULL;
	new_node->left= NULL;
	new_node->right = NULL;
	if ((*pptr)->root == NULL) { // ���ο� min heap�� ����
		(*pptr)->root = new_node;
		(*pptr)->size = 1;
	}
	else {// min heap�� ����Ǿ� �ִٸ�
		// ���Ե� ��ġ ã��
		int position = (*pptr)->size + 1;
		int direction[100] = { 0, }; // ������ ����
		int cnt = 0; // ������ �ڿ��� ���� �о���ϱ� ������ ������ ���� ����
		while (position != 1) {
			direction[cnt] = position % 2;
			cnt += 1;
			position /= 2;
		}
		node_pointer *temp_node = (node_pointer)malloc(sizeof(struct node));
		*temp_node = (*pptr)->root;
		for (int i = cnt - 1; i > 0; i--) {
			// �ڸ��� ã�ư��� ���� �� �θ�� ���� ���ؼ� swap
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
		// �ڸ��� ã�ư��� ���� �� �θ�� ���� ���ؼ� swap
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
	if ((*pptr)->size == 0) { // �� heap�̸� 0 ����
		return 0;
	}
	else if ((*pptr)->size == 1) { // ������ ���� �����ϰ� 0 ����
		*out = (*pptr)->root->val;
		(*pptr)->root = NULL;
		(*pptr)->size = 0;
		return 0;
	}
	*out = (*pptr)->root->val;
	int position = (*pptr)->size;
	int direction[100] = { 0, }; // ������ ����
	int cnt = 0; // ������ �ڿ��� ���� �о���ϱ� ������ ������ ���� ����
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
	// ���� �Է� �ޱ�
	FILE *infp;
	infp = fopen("heapsort.in", "rb");

	// ����� ���� ����
	FILE* outfp;
	outfp = fopen("heapsort.out", "w");

	int n;
	fscanf(infp, "%d\n", &n); // ������ �迭 ���� �Է�
	fprintf(outfp, "%d\n", n); // ������ �迭 ���� ���
	// �迭 ������ŭ �ݺ�
	while (n--) {
		// instances �Է�
		char instances[10001];
		fgets(instances, 10000, infp);

		// ���� ���ڸ� �������� ���ڿ��� �ڸ��� ������ ��ȯ
		char *ptr = strtok(instances, " ");
		// ���ڿ��� ���� ������ �ݺ�
		while (ptr != NULL) {
			int val = atoi(ptr);
			Insert(&heap, val);
			ptr = strtok(NULL, " "); // ����� term ����
		}
		// inorder ���
		fprintf(outfp, "I");
		inorder(heap->root, outfp);
		fprintf(outfp, "\n");
		// preorder ���
		fprintf(outfp, "P");
		preorder(heap->root, outfp);
		fprintf(outfp, "\n");
		int out;
		while (Delete(&heap, &out) != 0) { // heap���� ���� ���� node�� �����ϸ鼭
			fprintf(outfp, "%d ", out); // �� ���
		}
		fprintf(outfp, "%d\n", out); // ������ �� ���
	}
	// ����� ���� �ݱ�
	fclose(infp);
	fclose(outfp);
	return 0;
}
