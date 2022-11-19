#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba1.h"
#pragma warning(disable:4996)

int main() {
	setlocale(LC_ALL, "Rus");
	char* f = "Text.txt";
	Listptr MyList = ReadText(f);
	PrintList(MyList);
	FIRST(MyList);
	SECOND(MyList);
	list_free(MyList);
	return 0;
}
