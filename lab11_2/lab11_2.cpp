// lab11_2.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	cout << "������� ��� ������������ �����: "; cin.getline(file1, 10);
	create(file1);
	cout << "������ ����� ";
	unsigned int j;
	for (j = 0; j<strlen(file1); j++)
		cout << file1[j];
	cout << ": " << endl;
	vivod(file1); cin.get();
	cout << "������� ��� ������������ ����� ��� ����������: ";
	cin.getline(file2, 10);
	cout << "������� ����� ������ � ����� ������: ";
	cin >> group;
	getchar();
	cin >> week;
	getchar();
	schedule(file1, file2, group, week);
	cout << "������ ����� ";
	for (j = 0; j<strlen(file2); j++)
		cout << file2[j];
	cout << ": " << endl;
	vivod(file2);
	cout << "��������� ��������� ����������!" << endl;
	collision(file1);
	cout << "������ ������������ ����� "; for (int i = 0; i < 10; i++) cout << file1[i]; cout << ": " << endl;
	vivod(file1);
	system("pause");
	return 0;
}