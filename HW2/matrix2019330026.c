#define _CRT_SECURE_NO_WARNINGS // strtok ���� ���� ���� ������ ���� ����
#include <stdio.h>
#include <string.h> // strtok �Լ��� ����� ��� ����
#include <stdlib.h>    // malloc, free �Լ��� ����� ��� ����

typedef struct {
	int row; // �� ��ȣ 1~
	int col; // �� ��ȣ 1~
	int val; // �ش� ����� ��
} element;

//list_pointer �ڷᱸ�� ����
typedef struct list_node{
	element data; // ��� ��� ������
	struct list_node *next; // ���� node�� ����Ű�� ������
} *list_pointer;

//���� �Լ� Append ����
void Append(list_pointer *pptr, element data) {
	list_pointer app_node = NULL;
	app_node = (list_pointer) malloc(sizeof(struct list_node)); //���� ��带 ����Ű�� ������ ����
	app_node->data = data; //���� ��忡 ������ ����
	app_node->next = NULL;
	if (*pptr == NULL) // �� linked_list�� ����
		*pptr = app_node;
	else {// linked list�� ����Ǿ� �ִٸ� ������ ������ Ž���Ͽ� �� ������ ���� ��� �߰�
		list_pointer last_node = *pptr;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = app_node;
	}
}

//find �Լ� ����
list_pointer Find(list_pointer current_node, int row, int col) {
	if (current_node == NULL) return NULL;
	while (current_node->next != NULL) {
		if (current_node->data.row == row && current_node->data.col == col)
			return current_node; // ���� node�� ��� ���� ���ϴ� ���� ������ �� ��� ��ȯ
		else
			current_node = current_node->next; // ���� node�� ���ϴ� ��Ұ� �ƴ϶�� ���� ��� ����
	}
	if (current_node->data.row == row && current_node->data.col == col) // ������ node���� Ȯ���ؼ�
		return current_node; // ���ϴ� ��� ��ȯ
	else
		return NULL; // �ƴ϶�� 0 ��ȯ
}

//printm �Լ� ����
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

	// ���� �Է� �ޱ�
	FILE *infp;
	infp = fopen("matrix.in", "rb");

	// ����� ���� ����
	FILE* outfp;
	outfp = fopen("matrix.out", "w");

	// addition�� ����
	int n;
	fscanf(infp, "%d\n", &n);
	fprintf(outfp, "%d\n", n);

	// addition�� ������ŭ �ݺ� ����
	while (n--) {
		// matrix�� ������ linked list ����
		list_pointer first_matrix = NULL;

		// ���� ����� non-zero element�� ��
		int cnt = 0;

		// first_matrix �Է�
		int noe; // Number Of non-zero Element
		fscanf(infp, "%d\n", &noe);
		for (int i = 0; i < noe; i++) { //non-zero element�� ����ŭ element�� matrix�� �߰�
			// ���� ���ڸ� �������� ���ڿ��� �ڸ��� ������ ��ȯ
			char elementdata[3005];
			fgets(elementdata, 1000, infp);
			char *ptr = strtok(elementdata, " ");
			// element �߰�
			element nze; //Non-Zero Element
			nze.row = atoi(ptr); // �� ������
			ptr = strtok(NULL, " "); // ����� term ����
			nze.col = atoi(ptr); // �� ������
			ptr = strtok(NULL, " "); // ����� term ����
			nze.val = atoi(ptr); // �� ������
			ptr = strtok(NULL, " "); // ����� term ����
			Append(&first_matrix, nze); //element �߰�
			cnt += 1;
		}
		// second_matrix �Է�
		fscanf(infp, "%d\n", &noe);
		for (int i = 0; i < noe; i++) { //non-zero element�� ����ŭ element�� matrix�� �߰�
			// ���� ���ڸ� �������� ���ڿ��� �ڸ��� ������ ��ȯ
			char elementdata[3005];
			fgets(elementdata, 1000, infp);
			char *ptr = strtok(elementdata, " ");
			// element �߰�
			element nze; //Non-Zero Element
			nze.row = atoi(ptr); // �� ������
			ptr = strtok(NULL, " "); // ����� term ����
			nze.col = atoi(ptr); // �� ������
			ptr = strtok(NULL, " "); // ����� term ����
			nze.val = atoi(ptr); // �� ������
			ptr = strtok(NULL, " "); // ����� term ����
			//Append(second_matrix, nze); //element �߰�

			// ���ϱ� ����
			if (Find(first_matrix, nze.row, nze.col) != NULL)
				Find(first_matrix, nze.row, nze.col)->data.val += nze.val;
			else {
				Append(&first_matrix, nze);
				cnt += 1;
			}
		}

		// ���� ����� ���
		printf("\nresult: %d\n\n", cnt);
		fprintf(outfp, "%d\n", cnt);
		Printm(first_matrix, outfp);

	}
	// ����� ���� �ݱ�
	fclose(infp);
	fclose(outfp);

	return 0;
}
