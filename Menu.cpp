#include <iostream>
#include "Menu.h"
#include "System.h"
#pragma once
using namespace std;
void MenusUOS()
{
	//  ============== ���� ������������ ������� ========================
	int SEL; //    �������� ������
	system ("cls");
	//FU.open("C:\\UOS\\UOS_USER.log", ios::out);  //  ����.����� ��� ������ ...
	cout << "====== ROBCO UOS 1.2 ===========" << endl;
	cout << "======��� ������ ������ ���� ������� ����� " << endl;
	cout << " [1] ���� ���������� " << endl;
	cout << " [2] ���� ���������� " << endl;
	cout << " [3] ���� ���������� " << endl;
	cout << " [4] ���� ���������� " << endl;
	cout << " [5] ���� ���������� " << endl;
	cout << " [6] ���� ���������� " << endl;
	cout << " [7] ���� ���������� " << endl;
	cout << " [8] ���� ���������� " << endl;
	cout << " [9] ���� ���������� " << endl;
	cout << " [0] ���������� ������ " << endl;
	cout << "->";
	cin >> SEL;
	//FU << SEL;
	switch (SEL)
	{
	case 1: readTxtFile(); break;
	case 2: readTxtFile(); break;
	case 0: system("Exit");break;
	default:cout << "ERROR !" << endl;

	}
	//FU.close();
	system("pause");
}

