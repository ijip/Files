// lab11_2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <cstring>
#include "Binf.h"
int main() {
	char file1[10];
	char file2[10];
	long group;
	short week;
	cout << "Введите имя создаваемого файла: "; cin.getline(file1, 10);
	create(file1);
	cout << "Данные файла ";
	unsigned int j;
	for (j = 0; j<strlen(file1); j++)
		cout << file1[j];
	cout << ": " << endl;
	vivod(file1); cin.get();
	cout << "Введите имя создаваемого файла для расписания: ";
	cin.getline(file2, 10);
	cout << "Введите номер группы и номер недели: ";
	cin >> group;
	getchar();
	cin >> week;
	getchar();
	schedule(file1, file2, group, week);
	cout << "Данные файла ";
	for (j = 0; j<strlen(file2); j++)
		cout << file2[j];
	cout << ": " << endl;
	vivod(file2);
	cout << "Произведём обновение расписания!" << endl;
	collision(file1);
	cout << "Данные обновленного файла "; for (int i = 0; i < 10; i++) cout << file1[i]; cout << ": " << endl;
	vivod(file1);
	system("pause");
	return 0;
}