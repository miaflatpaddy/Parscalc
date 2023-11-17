#include "Mathh.h"
#include "Pars.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void main() {
	char* arr = new char[128]{};
	bool redo = 0;
	do {
		printf_s("\nInput your math-line: ");
		gets_s(arr, 128);
		if (error(arr)) {
			printf_s("\nUnacceptable symbols.");
			redo = 1;
		}
		else if (!error(arr)) {
			double num = pars(arr);
			system("cls");
			cout << arr << " = " << num << endl;
			printf_s("\nWanna other?(0-No,1-Yes)");
			scanf_s("%d", &redo);
			cin.ignore();
		}
	} while (redo);
	delete[] arr;
}