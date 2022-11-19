#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba1.h"
#pragma warning(disable:4996)

/*
* The function of finding the length of the string
*/
int LEN(char* a) {
	int i = 0;
	while (a[i++] != '\0');
	return --i;
}

/*
* The function checks whether the pointer is equal to the first pointer NULL (whether the list is empty)
*/
int isEmpty(Listptr sPtr) {
	return sPtr == NULL;
}

/*
* Outputs all the words of the list (starting with the pointer that we will pass)
* If the list is empty, it outputs an error message
*/
void PrintList(Listptr currentPtr) {
	if (isEmpty(currentPtr)) {
		puts("List is empty.");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			printf("%s\n", currentPtr->a);
			currentPtr = currentPtr->next;
		}
	}
}

/*
* A function that returns 1 if the first line is earlier in lexicographic order
* Otherwise 0
* Important! only strings of equal length are passed
*/
int comp(char* first, char* second, int length) {
	for (int i = 0; i < length; i++) {
		if (first[i] < second[i]) return 1;
		if (first[i] > second[i]) return 0;
	}
	return 0;
}

/*
* Function of inserting a new node into the list
* The insertion will take place immediately, taking into account all the conditions in the right order:
* In the order of increasing length, and in case of equality of lengths in alphabetical order
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
* The first item of the task
*/
void FIRST(Listptr currentPtr) {
	int N;
	printf("¬ведите N и вам виведутс€ слова > N: ");
	scanf("%d", &N);
	while (currentPtr != NULL) {
		if (currentPtr->length > N) printf("%s\n", currentPtr->a);
		currentPtr = currentPtr->next;
	}
}

/*
* The second point of the task
*/
void SECOND(Listptr currentPtr) {
	int N;
	printf("¬ведите N и вам виведутс€ слова = N: ");
	scanf("%d", &N);
	while (currentPtr != NULL && currentPtr->length <= N) {
		if (currentPtr->length == N) printf("%s\n", currentPtr->a);
		currentPtr = currentPtr->next;
	}
}

/*
* The function of reading from a file returns a list
*/
Listptr ReadText(char const* filename) {
	Listptr start = NULL;
	char a[1000];         // buffer for reading from a file
	FILE* f = fopen(filename, "r");
	if (f == NULL) return NULL;
	while (fscanf(f, "%s", a) == 1) {
		char* word = (char*)malloc(sizeof(char) * (LEN(a)+1));
		if (word == NULL) return NULL;
		for (int i = 0; i <= LEN(a); i++)
			word[i] = a[i];
		Insert(word, LEN(a), &start);
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