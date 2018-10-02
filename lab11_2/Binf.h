#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <cstring>

struct Group {
	long numog; //����� ������
	char discipline[10]; //�������� ����������
	short numos; //����
	short numow; //������
	short numod; //����
	short numoc; //�������
};

void create(char *namefile) { //�������� �����
	ofstream fout(namefile, ios::binary | ios::out);
	Group r;
	int i;
	cout << "������� ������� ��������� ������?: ";
	cin >> i; getchar();
	for (i; i>0; i--) {
		cout << i << ": " << endl;
		cout << "����� ������: "; cin >> r.numog; cin.get();
		cout << "�������� ����������:"; cin.getline(r.discipline, 10);
		cout << "����: "; cin >> r.numos;
		cout << "������: "; cin >> r.numow;
		cout << "����: "; cin >> r.numod;
		cout << "�������: "; cin >> r.numoc;
		fout.write((char *)&r, sizeof(r));
		cout << endl;
	}
	fout.flush();
	fout.close();
}

void vivod(char *namefile) { //������ �����
	ifstream fin(namefile, ios::binary | ios::in);
	Group r; int i = 1;
	while (fin.read((char *)&r, sizeof r)) {
		cout << i << ": " << endl;
		cout << "����� ������: " << r.numog << "; ";
		cout << "�������� ����������: ";
		unsigned int j;
		for (j = 0; j<strlen(r.discipline); j++)
			cout << r.discipline[j] << "; ";
		cout << "����: " << r.numos << "; ";
		cout << "������: " << r.numow << "; ";
		cout << "����: " << r.numod << "; ";
		cout << "�������: " << r.numoc << endl;
		i++;
	}
	fin.close();
}

void schedule(char *namefile, char *newnamefile, long group, short week) { //���������� ������� ������
	ifstream fin(namefile, ios::binary | ios::in);
	fstream finout(newnamefile, ios::binary | ios::in | ios::out);
	Group r;
	Group r1;
	int pos = 0;
	while (fin.read((char *)&r, sizeof r)) { //�������� ������ ����������
		if ((r.numog == group) && (r.numow == week))
		{
			finout.write((char *)&r, sizeof(r));
		}
	}
	//���������� ���������� �� ������ ����
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

void collision(char *namefile) { //��������� ����������
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
				cout << "������� ���������� � ����������, �������� � ������" << r2.numog << " �������: "; cin >> r2.numoc;
				f2.write((char *)&r2, sizeof(r2));
			}
		}
		pos++;
	}
	cout << "���������� ���������!" << endl;
}
