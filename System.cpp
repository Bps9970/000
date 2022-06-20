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
		LPCTSTR lpRootPathName,    //���� � �������� ��� ����������
		// ���� (������: "\\MyServer\MyShare\" ��� "C:\".
		LPTSTR lpVolumeNameBuffer, //����� - � ������� ����� ��������� ��� ����
		DWORD nVolumeNameSize,     //������ ������
		LPDWORD lpVolumeSerialNumber, //�������� ����� ����
		LPDWORD lpMaximumComponentLength, //������ ����
		LPDWORD lpFileSystemFlags, //��� �������� �������
		LPTSTR lpFileSystemNameBuffer, //�������� �������� �������
		DWORD nFileSystemNameSize //������ ������ ��� �������� ��
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
	/*unsigned int drive_type = GetDriveType(0);  / �������� ��� �������� � �������� �������� ��
	if (GetDriveType(0) == DRIVE_FIXED)
		cout << "Robco UOS: " << DRIVE_FIXED << endl;
	cout << drive_type <<endl;
	*/

	//-------------------------------------------
	cout << " * * ������ �����������, ������������ �� ����������:" << endl;
	for (int i = 0; i < I; i++)
	{
		test = GetDriveType(drive[i]);
		switch (test)
		{
		case 0:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S ���������� ���������� ������ ���� ...  \n", drive[i], test);
			break;
		}
		case 1:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S  �������� �������� ����/���������� ������ ���� ...  \n", drive[i], test);
			break;
		}
		case 2:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("% S ������� ���� . \n", drive[i], test);
			break;
		}
		case 3:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf(" %S  �������  ����.\n", drive[i], test);
			GetVolumeInformation(drive[i], (LPWSTR)NameBuffer, sizeof(NameBuffer),
				&VSNumber, &MCLength, &FileSF, (LPWSTR)SysNameBuffer, sizeof(SysNameBuffer));
			printf("����� �����:  %S \n", NameBuffer);
			printf("�������� �������: %S \n", SysNameBuffer);
			printf("�������� �����  ����� : %d \n", VSNumber);
			printf("�������� �����  �����2 : %d \n", MCLength);
			Beep(400, 100);
			break;
		}
		case 4:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S   ������� ���� . \n", drive[i], test);
			break;
		}
		case 5:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf(" %S   ������  CD-ROM/DVD-ROM \n", drive[i], test);
			break;
		}
		case 6:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			printf("%S   ���� ���������� � ����������� ������ . \n", drive[i], test);
			break;
		}
		default:
		{
			cout << " * * * * * * * * * * * * * * * * * * * *" << endl;
			cout << "Unknown value!" << endl;
			cout << "��� ����� ���������� ���������� ..." << endl;
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

	ifstream ft;     // �������� ����� ��� ������ ������ (���������)
	string ftxt;     // ���������
	int n = 0;       //
	int nst = 0;     //
	int np = 0;      //
	char c[256] = {};     //
	string st;       //

	// * * * * * * * * * * * * * * * * * * * * * * * * * *
	//cout << "������� ��� �����";
	//cin >> ftxt;
	setlocale(LC_CTYPE, "RUSSIAN"); // ��������� ������� ���� ...
	ftxt = "C:\\UOS\\TEXTS\\DIARY1.TXT";
	system("cls");
	cout << " = = = = = = = = = = = = = = = = = = = = = = =" << endl;
	cout << " **** �������� ������ UOS-TR  1.02 **** " << endl;
	cout << " ������ �� ����� : " << ftxt << endl;
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
		cout << "����� ����� " << ftxt << " �������� ..." << endl;
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
