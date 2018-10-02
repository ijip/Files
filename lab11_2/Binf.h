#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <cstring>

struct Group {
	long numog; //номер группы
	char discipline[10]; //название дисциплины
	short numos; //пара
	short numow; //неделя
	short numod; //день
	short numoc; //кабинет
};

void create(char *namefile) { //создание файла
	ofstream fout(namefile, ios::binary | ios::out);
	Group r;
	int i;
	cout << "Сколько записей требуется ввести?: ";
	cin >> i; getchar();
	for (i; i>0; i--) {
		cout << i << ": " << endl;
		cout << "номер группы: "; cin >> r.numog; cin.get();
		cout << "название дисциплины:"; cin.getline(r.discipline, 10);
		cout << "пара: "; cin >> r.numos;
		cout << "неделя: "; cin >> r.numow;
		cout << "день: "; cin >> r.numod;
		cout << "кабинет: "; cin >> r.numoc;
		fout.write((char *)&r, sizeof(r));
		cout << endl;
	}
	fout.flush();
	fout.close();
}

void vivod(char *namefile) { //чтение файла
	ifstream fin(namefile, ios::binary | ios::in);
	Group r; int i = 1;
	while (fin.read((char *)&r, sizeof r)) {
		cout << i << ": " << endl;
		cout << "номер группы: " << r.numog << "; ";
		cout << "название дисциплины: ";
		unsigned int j;
		for (j = 0; j<strlen(r.discipline); j++)
			cout << r.discipline[j] << "; ";
		cout << "пара: " << r.numos << "; ";
		cout << "неделя: " << r.numow << "; ";
		cout << "день: " << r.numod << "; ";
		cout << "кабинет: " << r.numoc << endl;
		i++;
	}
	fin.close();
}

void schedule(char *namefile, char *newnamefile, long group, short week) { //расписание занятий группы
	ifstream fin(namefile, ios::binary | ios::in);
	fstream finout(newnamefile, ios::binary | ios::in | ios::out);
	Group r;
	Group r1;
	int pos = 0;
	while (fin.read((char *)&r, sizeof r)) { //создание списка расписания
		if ((r.numog == group) && (r.numow == week))
		{
			finout.write((char *)&r, sizeof(r));
		}
	}
	//сортировка расписания по номеру пары
	fin.close();
	finout.seekg(pos * sizeof(r), ios::beg);
	fstream f(newnamefile, ios::binary | ios::in | ios::out);
	while (finout.read((char *)&r, sizeof r) && f.seekg((pos + 1) * sizeof(r1), ios::beg)) {
		while (f.read((char *)&r1, sizeof r1)) {
			if (r.numos > r1.numos) {
				finout.seekg(pos * sizeof(r), ios::beg);
				f.seekg(-sizeof(r1), ios::cur);
				finout.write((char *)&r1, sizeof(r1));
				f.write((char *)&r, sizeof(r));
			}
		}
		pos++;
	}
	f.close();
	fin.close();
	finout.close();
}

void collision(char *namefile) { //изменение расписания
	Group r1, r2; int pos = 0, i = -1;
	fstream f1(namefile, ios::binary | ios::in | ios::out);
	fstream f2(namefile, ios::binary | ios::in | ios::out);
	while (f1.read((char *)&r1, sizeof r1) && f2.seekg((pos + 1) * sizeof(r2), ios::beg))
	{
		while (f2.read((char *)&r2, sizeof r2))
		{
			if ((r1.numos == r2.numos) && (r1.numoc == r2.numoc) && (r1.numod == r2.numod))
			{
				f2.seekg(i * sizeof(r2), ios::cur);
				cout << "Найдено совпадение в расписании, замените у группы" << r2.numog << " кабинет: "; cin >> r2.numoc;
				f2.write((char *)&r2, sizeof(r2));
			}
		}
		pos++;
	}
	cout << "Расписание обновлено!" << endl;
}
