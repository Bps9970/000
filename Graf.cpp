
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include "Graf.h"

using namespace std;
wstring fname = L"C:\\UOS\\IMG\\img3.bmp";  //   ��� ����� ��� ������ �����������

int RecIMG()
// ������ ����������� � ���� "C:\\UOS\\IMG\\img3.bmp"
{
    HANDLE hFile;
    DWORD RW;
    int i, j, p, px = 0;
    WORD color;
    RGBTRIPLE color2{};
    // ======== ������� ������ ��������� ===========================
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    //BYTE Palette [1024];    // �������
    RGBQUAD  Palette[1024]{};    // �������
    // ����� � ��� ����� �������� �������� 35 x 50 �������� 
    int Width = 1024;
    int Height = 1024;
    cout << "================================================" << endl;
    cout << "== ������ ������ � ����,��������� ������� ... ==" << endl;
    cout << "================================================" << endl;
    srand(time(0));
    //===================================================================
    memset(&Palette[0], 0, sizeof(RGBQUAD));   // � ������� � ��� ����-�������� �� 
    for (p = 0; p < 1023; p++)
    {
        srand(time(0));
        Palette[p].rgbBlue = (1 + rand() % 10000);
        Palette[p].rgbGreen = (1 + rand() % 10000);
        Palette[p].rgbRed = (1 + rand() % 10000);

    }
    memset(&bfh, 0, sizeof(bfh));
    bfh.bfType = 0x4D42;  // ���������, ��� ��� bmp 'BM' 
    bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + 1024; // ������� �������� 1Kb, �� �� 
                   // ��� ������������ �� ����� 
    bfh.bfSize = bfh.bfOffBits +
    sizeof(color) * Width * Height +
    Height * ((sizeof(color) * Width) % 4);    // ��������� ������ ��������� ����� 
    memset(&bih, 0, sizeof(bih));
    bih.biSize = sizeof(bih);                  // ��� �������� 
    bih.biBitCount = 16;                       // 16 ��� �� ������� 
    bih.biClrUsed = 32768;                     // �� ���������� 5-5-5 
    bih.biCompression = BI_RGB;                // ��� ������ 
    bih.biHeight = Height;
    bih.biWidth = Width;
    bih.biPlanes = 1;                          // ������ ����   
                  // � ��������� ���� �������� 0 
    hFile = CreateFile(fname.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return -1;
    // ======== ������� ��������� ================
    WriteFile(hFile, &bfh, sizeof(bfh), &RW, NULL);
    WriteFile(hFile, &bih, sizeof(bih), &RW, NULL);
    // ======== ������� ������� ===================
    WriteFile(hFile, Palette, 1024 * sizeof(RGBQUAD), &RW, NULL);
    //=============================================
    srand(time(0));
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            srand(time(0));
            color2.rgbtBlue = (1 + rand() % 10000);
            color2.rgbtGreen = (1 + rand() % 10000);
            color2.rgbtRed = (1 + rand() % 10000);
            RW = (1 + rand() % 10000);
            WriteFile(hFile, &color2, sizeof(color2), &RW, NULL);

        }
        // ========= ��������� �� ������� ===============
        color = (1 + rand() % 10000);
        RW = (1 + rand() % 10000);
        WriteFile(hFile, Palette, (sizeof(color2) * Width) % 4, &RW, NULL);
    }
    cout << "==============================================================" << endl;
    cout << "=== ���� ������ � ������� : " << " C:\\DRV\\IMG\\img3.bmp ====" << endl;
    cout << "==============================================================" << endl;
    CloseHandle(hFile);
    return 0;
}