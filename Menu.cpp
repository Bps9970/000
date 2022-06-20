#include <iostream>
#include "Menu.h"
#include "System.h"
#pragma once
using namespace std;
void MenusUOS()
{
	//  ============== Меню операционной системы ========================
	int SEL; //    Селектор выбора
	system ("cls");
	//FU.open("C:\\UOS\\UOS_USER.log", ios::out);  //  Откр.файла для записи ...
	cout << "====== ROBCO UOS 1.2 ===========" << endl;
	cout << "======Для выбора пункта меню введите число " << endl;
	cout << " [1] Тест процессора " << endl;
	cout << " [2] Тест процессора " << endl;
	cout << " [3] Тест процессора " << endl;
	cout << " [4] Тест процессора " << endl;
	cout << " [5] Тест процессора " << endl;
	cout << " [6] Тест процессора " << endl;
	cout << " [7] Тест процессора " << endl;
	cout << " [8] Тест процессора " << endl;
	cout << " [9] Тест процессора " << endl;
	cout << " [0] Завершение работы " << endl;
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

