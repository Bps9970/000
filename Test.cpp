#include <windows.h>
#include <winioctl.h> 
#include <iostream>
#include <tchar.h>
#include <fstream>
#include "Test.h"
using namespace std;
//*****************************************
int MemoryTest()  // Тест системной памяти ...
{
    int i;//=10;      // Счетчик столбцов
    int j;// =10;    //  счетчик строк
    int I = 100;     //  Нач.установки
    int J = 100;    //   Нач.установки
    ofstream F1;
    cout << " ==== Тест системной памяти   ========  " << "\n";
    F1.open("C:\\UOS\\memory.log", ios::out); // Откр.файла для записи ...
    F1 << "=======================================" << "\n";
    srand(time(0));   //    Инициализация гсц
    int RDT[100][100]{};  // Объявление матрицы
    for (i = 0; i < I; i++)
    {
        for (j = 0; j < J; j++)
        {
            RDT[i][j] = 1 + rand() % 1000;  // Заполняем её...
        }
    }

    for (i = 0; i < I; i++)
    {
        for (j = 0; j < J; j++)
        {

            F1 << "[#]" << "\t";
            F1 << RDT[i][j] << "\t";   //      Запись в файл ( "\t" - табуляция )
            F1 << "[ " << &RDT[i][j] << " ]" << "\n";   // Запись в файл ( Адрес элемента матрицы )
             Sleep(1);     //  Врем.задержка ...
            cout << &RDT[i][j] << "\t";   // Вывод на экран матрицы

        }
    }
    F1 << "========================================" << "\n";
    cout << " =================  Тест системной паяти закончен ================" << "\n";
    F1.close();   // Закрывает файл ( файловый поток,однако ... )
    return 0;
}
// =========================================
char* IntToStr(int  n)

// Функция преобр.числа в строку ...
{

    char s[40]{}, t, * temp;
    int i = 0;
    unsigned k = 0;
    int sign = 0;  // Знак числа 0 - полож., 1- отриц.
    i = 0;
    k = n;
    if (k < 0)
    {
        sign = 1;
        k = -k;
    }
    do
    {
        t = k % 10;
        k = k / 10;
        s[i] = t | 0x30;
        i++;
    } while (k > 0);
    if (sign == 1)
    {
        s[i] = '-';
        i++;
    }
    temp = new char[i];
    k = 0;
    i--;
    while (i >= 0)
    {
        temp[k] = s[i];
        i--;
        k++;
    }
    temp[k] = '\0';
    return (temp);
}
// =========================================
int TEST_COM()
{
    int i;
    HANDLE hCOM;
    hCOM = CreateFile(_T("COM1"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hCOM != INVALID_HANDLE_VALUE)
    {
        cout << "COM1 is open OK!" << endl;
        char buffer[30];
        char SMS[40]{}, * n = nullptr;
        memset(buffer, 0, sizeof(buffer));
        for (i = 0; i < 101; i++)
        {
            strcpy(buffer, "SAVE TO COM1");
            // IntToStr(i);
            strcpy(buffer, IntToStr(i));
            DWORD nb;
            OVERLAPPED ov;
            WriteFile(hCOM, buffer, sizeof(buffer), &nb, &ov);
            cout << "[ " << buffer << " ] ";
        }
        cout << endl;
        cout << "Close COM1" << endl;
        CloseHandle(hCOM);
    }
    else
        cout << "Error Open COM" << endl;
    return 0;
}