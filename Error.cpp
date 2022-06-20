#pragma once
#include <iostream>
using namespace std;
int SYSTEM_CODE_ERROR(int ErrCode, int ErrTime,int AddErr)
{
	// Стандартный модуль вывода сообщений об ошибках системы
	   // В функцию передается код ошибки ErrCode [ коды ошибок 1 - 1000 ]
	   // и время ошибки Errtime для записи в файл SystemErr.log ...
	switch (ErrCode)

	{
	   case 1:
	    {
		   cout << " ===================================================" << endl;
		   cout << "Ошибка процессора. Нарушение прав доступа на чтение:" << AddErr << endl;
		   // Записать в файл SystemError.log код ошибки и время...
		  cout << "====================================================" << endl;
		  break;
	    }
	   case 2:
	   {


	   }
	}
	return 0;
}