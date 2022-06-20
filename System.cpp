#include <windows.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include "System.h"
using namespace std;

// =============================================
int Disk()
{
	BOOL WINAPI GetVolumeInformation(
		LPCTSTR lpRootPathName,    //путь к сетевому или локальному
		// тому (пример: "\\MyServer\MyShare\" или "C:\".
		LPTSTR lpVolumeNameBuffer, //буфер - в котором будет храниться имя тома
		DWORD nVolumeNameSize,     //размер буфера
		LPDWORD lpVolumeSerialNumber, //серийный номер тома
		LPDWORD lpMaximumComponentLength, //размер тома
		LPDWORD lpFileSystemFlags, //тип файловой системы
		LPTSTR lpFileSystemNameBuffer, //название файловой системы
		DWORD nFileSystemNameSize //размер буфера под название ФС
	);
	return 0;
}
int OSdisk()
{
	int I = 14;
	LPCWSTR drive[14] = { L"A:\\", L"B:\\", L"C:\\", L"D:\\", L"E:\\", L"F:\\", L"G:\\",
						 L"H:\\",L"I:\\", L"J:\\", L"K:\\", L"L:\\",L"X:\\ " };
	UINT test;
	WCHAR NameBuffer[MAX_PATH] = {};
	WCHAR SysNameBuffer[MAX_PATH] = {};
	DWORD FileSystemNameSize = 0;
	DWORD VSNumber = 0;
	DWORD MCLength = 0;
	DWORD FileSF = 0;
	/*unsigned int drive_type = GetDriveType(0);  / Получаем тип носителя с которого запущена ОС
	if (GetDriveType(0) == DRIVE_FIXED)
		cout << "Robco UOS: " << DRIVE_FIXED << endl;
	cout << drive_type <<endl;
	*/

	//-------------------------------------------
	cout << " * * Список накопителей, обраруженных на устройстве:" << endl;
	for (int i = 0; i < I; i++)
	{
		test = GetDriveType(drive[i]);
		switch (test)
		{
		case 0:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S Невозможно определить данный диск ...  \n", drive[i], test);
			break;
		}
		case 1:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S  Неверный корневой путь/недоступен данный диск ...  \n", drive[i], test);
			break;
		}
		case 2:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("% S Съемный диск . \n", drive[i], test);
			break;
		}
		case 3:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf(" %S  Жесткий  диск.\n", drive[i], test);
			GetVolumeInformation(drive[i], (LPWSTR)NameBuffer, sizeof(NameBuffer),
				&VSNumber, &MCLength, &FileSF, (LPWSTR)SysNameBuffer, sizeof(SysNameBuffer));
			printf("Метка диска:  %S \n", NameBuffer);
			printf("Файловая система: %S \n", SysNameBuffer);
			printf("Серийный номер  диска : %d \n", VSNumber);
			printf("Серийный номер  диска2 : %d \n", MCLength);
			Beep(400, 100);
			break;
		}
		case 4:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S   Сетевой диск . \n", drive[i], test);
			break;
		}
		case 5:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf(" %S   Привод  CD-ROM/DVD-ROM \n", drive[i], test);
			break;
		}
		case 6:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S   Диск расположен в оперативной памяти . \n", drive[i], test);
			break;
		}
		default:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			cout << "Unknown value!" << endl;
			cout << "Тип диска невозможно определить ..." << endl;
		}

		/*GetVolumeInformation(drive[i], (LPWSTR)NameBuffer, sizeof(NameBuffer),
			&VSNumber, &MCLength, &FileSF, (LPWSTR)SysNameBuffer, sizeof(SysNameBuffer));
		  cout << NameBuffer << endl;
		  cout << SysNameBuffer << endl;
		   cout << VSNumber << endl;*/

		
		}
	}
	return 0;
}

// ================================================
int readTxtFile()
// = = = = = = = = = = = = 12:49 28.01.2020 = = = = 
{
	//  * * * * * * * * * * * * * * * * * * * * * * *

	ifstream ft;     // Файловый поток для чтения файлов (текстовых)
	string ftxt;     // Проверить
	int n = 0;       //
	int nst = 0;     //
	int np = 0;      //
	char c[256] = {};     //
	string st;       //

	// * * * * * * * * * * * * * * * * * * * * * * * * * *
	//cout << "Введите имя файла";
	//cin >> ftxt;
	setlocale(LC_CTYPE, "RUSSIAN"); // Поддержим РУССКИЙ ЯЗЫК ...
	ftxt = "C:\\UOS\\TEXTS\\DIARY1.TXT";
	system("cls");
	cout << " = = = = = = = = = = = = = = = = = = = = = = =" << endl;
	cout << " **** РЕДАКТОР ТЕКСТА UOS-TR  1.02 **** " << endl;
	cout << " Чтение из файла : " << ftxt << endl;
	cout << " = = = = = = = = = = = = = = = = = = = = = = =" << endl;
	ft.open(ftxt);
	if (ft)
	{
		// * * * * * * * * * * * * * * * * * * * * * * * * * * *
		do
		{

			getline(ft, st);
			cout << st << endl;
			n++;
			st = "";
			if (n == 20)
			{
				system("pause");
				cout << "-->" << endl;
				n = 0;
			}
		} while (!ft.eof());
		// * * * * * * * * * * * * * * * * * * * * * * * * * * *
		cout << " = = = = = = = = = = = = = = = = = = = = = = =" << endl;
		cout << "Вывод файла " << ftxt << " завершен ..." << endl;
		cout << " = = = = = = = = = = = = = = = = = = = = = = =" << endl;
		ft.close();
	}

	else
	{
		cout << " = = = = = = = = = = = = = = = = = = = = = = =" << endl;
		cout << "File not found ..." << endl;
		cout << " = = = = = = = = = = = = = = = = = = = = = = =" << endl;
		return -1;
	}
	return 0;
}
