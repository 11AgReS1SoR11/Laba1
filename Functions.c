#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Node List;
typedef List* Listptr;
/*
* Создаю структура Node, которая содержит в себе строку (указатель), длину и указатель на следующий узел
*/
struct Node {
	char* a;
	int length;
	struct Node* next;
};

/*
* Функция проверяет не равен ли указатель первый указатель NULL (пустой ли список)
*/
int isEmpty(Listptr sPtr) {
	return sPtr == NULL;
}

/*
* Выводит строку
*/
void Print(char* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%c", a[i]);
	}
	puts("");
}


/*
* Выводит все слова списка (начиная с укателя, который мы передадим)
* Если список пуст, то выводит сообщение об ошибке
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
* Проверка на разделители
*/
int IsAlNum(char c) {
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
	return 0;
}


/*
* Функция, которая возвращает 1 в случае, если первая строка раньше в лексикографическом порядке
* Иначе 0
* Важно! передаются только строки равной длины
*/
int comp(char* first, char* second, int length) {
	for (int i = 0; i < length; i++) {
		if (first[i] < second[i]) return 1;
		if (first[i] > second[i]) return 0;
	}
	return 0;
}

/*
* Функция вставки нового узла в список
* Вставка просихдоит сразу с учётом всех условий в нужном порядке:
* В порядке возврастания длины, а в случае равенства длин в алфавтном порядке
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
		while (cur != NULL && length > cur->length)  // проверка на длины
		{
			prev = cur;
			cur = cur->next;
		}

		while ((cur != NULL) && (!comp(a, cur->a, length)) && (length == cur->length)) // проверка на алфавит
		{
			prev = cur;
			cur = cur->next;
		}

		if (prev == NULL) {
			new->next = *Ptr;
			*Ptr = new;
		}
		else {
			prev->next = new;
			new->next = cur;
		}
	}
}


/*
* Первый пункт задачи
*/
void FIRST(Listptr currentPtr) {
	int N;
	printf("Введите N и вам виведутся слова > N:\n");
	scanf_s("%d", &N);
	while (currentPtr != NULL) {
		if (currentPtr->length > N) Print(currentPtr->a, currentPtr->length);
		currentPtr = currentPtr->next;
	}
}


/*
* Второй пункт задачи
*/
void SECOND(Listptr currentPtr) {
	int N;
	printf("Введите N и вам виведутся слова = N:\n");
	scanf_s("%d", &N);
	while (currentPtr != NULL && currentPtr->length <= N) {
		if (currentPtr->length == N) Print(currentPtr->a, currentPtr->length);
		currentPtr = currentPtr->next;
	}
}

/*
* Функция считывания из файла, возвращает список
*/
Listptr* ReadText(char const* filename) {
	Listptr start = NULL; // 
	int len = 0;  // длина
	char* a = NULL; // строка
	FILE* f;
	char t;
	fopen_s(&f, filename, "r");
	if (f == NULL) return NULL;
	a = (char*)malloc(sizeof(char));
	if (a == NULL) return NULL;
	while (fscanf_s(f, "%c", &t) == 1) { // пока удалось считать
		if (IsAlNum(t) == 1) { // проверка на разделитель
			len++;
			char* p = (char*)realloc(a, len * sizeof(char));
			if (p == NULL) return NULL;
			a = p;
			a[len - 1] = t; // добавление символа в строку
		}
		else {
			if (IsAlNum(a[0])) { // если строка заполнена, то добавляем узел
				Insert(a, len, &start);
				len = 0;
				a = (char*)malloc(sizeof(char));
				if (a == NULL) return NULL;
			}
		}
	}
	if (IsAlNum(a[0])) { // проверка на последную строку
		Insert(a, len, &start);
		len = 0;
		a = (char*)malloc(sizeof(char));
		if (a == NULL) return NULL;
	}
	fclose(f);
	return start;
}

void list_free(Listptr A) {
	Listptr cur = A;
	Listptr prev = NULL;
	while (cur != NULL)
	{
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}

