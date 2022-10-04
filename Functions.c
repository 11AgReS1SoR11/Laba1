#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Node List;
typedef List* Listptr;
/*
* ������ ��������� Node, ������� �������� � ���� ������ (���������), ����� � ��������� �� ��������� ����
*/
struct Node {
	char* a;
	int length;
	struct Node* next;
};

/*
* ������� ��������� �� ����� �� ��������� ������ ��������� NULL (������ �� ������)
*/
int isEmpty(Listptr sPtr) {
	return sPtr == NULL;
}

/*
* ������� ������
*/
void Print(char* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%c", a[i]);
	}
	puts("");
}


/*
* ������� ��� ����� ������ (������� � �������, ������� �� ���������)
* ���� ������ ����, �� ������� ��������� �� ������
*/
void printList(Listptr currentPtr) {
	if (isEmpty(currentPtr)) {
		puts("List is empty.");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			Print(currentPtr->a, currentPtr->length);
			currentPtr = currentPtr->next;
		}
	}
}

/*
* �������� �� �����������
*/
int IsAlNum(char c) {
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
	return 0;
}


/*
* �������, ������� ���������� 1 � ������, ���� ������ ������ ������ � ������������������ �������
* ����� 0
* �����! ���������� ������ ������ ������ �����
*/
int comp(char* first, char* second, int length) {
	for (int i = 0; i < length; i++) {
		if (first[i] < second[i]) return 1;
		if (first[i] > second[i]) return 0;
	}
	return 0;
}

* ������� ������� ������ ���� � ������
* � ������� ������������ �����, � � ������ ��������� ���� � ��������� �������
*/
void Insert(char* a, int length, Listptr* Ptr) {
	Listptr new, prev, cur;

	new = (Listptr)malloc(sizeof(List));
	if (new == NULL) printf("No memory avaible.\n");
	else {
		new->a = a;
		new->length = length;
		new->next = NULL;

		prev = NULL;
		cur = *Ptr;
		while (cur != NULL && length > cur->length)  // �������� �� �����
		{
			prev = cur;
			cur = cur->next;
		}

		while ((cur != NULL) && (!comp(a, cur->a, length)) && (length == cur->length)) // �������� �� �������
		{
			prev = cur;
			cur = cur->next;
		}

		if (prev == NULL) {
			new->next = *Ptr;
			*Ptr = new;
		} else {
			prev->next = new;
			new->next = cur;
		}
	}
}


/*
* ������ ����� ������
*/
void FIRST(Listptr currentPtr) {
	int N;
	printf("������� N � ��� ��������� ����� > N:\n");
	scanf_s("%d", &N);
	while (currentPtr != NULL) {
		if (currentPtr->length > N) Print(currentPtr->a, currentPtr->length);
		currentPtr = currentPtr->next;
	}
}


/*
* ������ ����� ������
*/
void SECOND(Listptr currentPtr) {
	int N;
	printf("������� N � ��� ��������� ����� = N:\n");
	scanf_s("%d", &N);
	while (currentPtr != NULL && currentPtr->length <= N) {
		if (currentPtr->length == N) Print(currentPtr->a, currentPtr->length);
		currentPtr = currentPtr->next;
	}
}

/*
* ������� ���������� �� �����, ���������� ������
*/
Listptr* ReadText(char const* filename) {
	Listptr start = NULL; // 
	int len = 0;  // �����
	char* a = NULL; // ������
	FILE* f;
	char t;
	fopen_s(&f, filename, "r");
	if (f == NULL) return NULL;
	a = (char*)malloc(sizeof(char));
	if (a == NULL) return NULL;
	while (fscanf_s(f, "%c", &t) == 1) { // ���� ������� �������
		if (IsAlNum(t) == 1) { // �������� �� �����������
			len++;
			char* p = (char*)realloc(a, len * sizeof(char));
			if (p == NULL) return NULL;
			a = p;
			a[len - 1] = t; // ���������� ������� � ������
		}
		else {
			if (IsAlNum(a[0])) { // ���� ������ ���������, �� ��������� ����
				Insert(a, len, &start);
				len = 0;
				a = (char*)malloc(sizeof(char));
				if (a == NULL) return NULL;
			}
		}
	}
	if (IsAlNum(a[0])) { // �������� �� ��������� ������
		Insert(a, len, &start);
		len = 0;
		a = (char*)malloc(sizeof(char));
		if (a == NULL) return NULL;
	}
	fclose(f);
	return start;
}