#pragma once
#include <iostream>
using namespace std;
int SYSTEM_CODE_ERROR(int ErrCode, int ErrTime,int AddErr)
{
	// ����������� ������ ������ ��������� �� ������� �������
	   // � ������� ���������� ��� ������ ErrCode [ ���� ������ 1 - 1000 ]
	   // � ����� ������ Errtime ��� ������ � ���� SystemErr.log ...
	switch (ErrCode)

	{
	   case 1:
	    {
		   cout << " ===================================================" << endl;
		   cout << "������ ����������. ��������� ���� ������� �� ������:" << AddErr << endl;
		   // �������� � ���� SystemError.log ��� ������ � �����...
		  cout << "====================================================" << endl;
		  break;
	    }
	   case 2:
	   {


	   }
	}
	return 0;
}