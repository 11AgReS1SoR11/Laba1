#pragma once

typedef struct Node List;
typedef List* Listptr;

struct Node {
	char* a;
	int length;
	struct Node* next;
};

void list_free(MyList);
void printList(Listptr currentPtr);
void FIRST(Listptr currentPtr);
void SECOND(Listptr currentPtr);
Listptr* ReadText(char const* filename);
