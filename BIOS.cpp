 /*	
  * ������ BIOS	 4.02.08.00 52EE5.E8.E8
  * ����������� - �������� �.�.
  * Email - bps9970@gmail.com
  * ���� ������ ���������� - 18.01.2022 21.31
  * www.uos.robco.developer	Robco Corp, 2077, All Rights Reserved.
 */
#include "BIOS.H"
#include <iostream>
#include <string>
#include <iostream>
using namespace std;
// ================================================
bool BIOS_STATUS = false;
FILE *FILE_BIOS;
const char *FILE_NAME ="C:\\UOS\\bios.rom";	 // ���� BIOS - bios.rom
char bufferZ;
//=================================================

int FILE_OPEN_BIOS()
{
	FILE_BIOS = fopen(FILE_NAME, "rb");
	if (FILE_BIOS == 0)
	{
		BIOS_STATUS = false;
	}
	else
	{
		BIOS_STATUS = true;
		long size;
		cout << "Initializing Robco industries (TM) MF Boot Agent v 2.3.0" << endl;
		cout << "RETROS BIOS" << endl;
		cout << "RBTOS-4.02.08.00 52EE.E7.F8 " << endl;
		cout << "Copyright 2201-2203 Robco Ind" << endl;
		cout << "Root (5A8)" << endl;
		cout << "���� BIOS ������: "<< FILE_NAME << endl;
		fseek(FILE_BIOS, 0, SEEK_END);		//	������		||
		size = ftell(FILE_BIOS);			//	���������	||
		fseek(FILE_BIOS, 0, SEEK_SET);		//	 �����		||
		cout << "������ ����� BIOS: " << size << " ����." <<endl;
		//====================================================
		fclose(FILE_BIOS);
		BIOS_STATUS = false;
		system("pause");

	}
 return 0;
}

int Bios_Disk(char cmd, int   drive, int head, int track,
	int  sector, int nsects, char buffer)
{
 diskinfo_t* diskBios = nullptr;
	switch (cmd)

{
	case  DISK_RESET:
	{
		diskBios->drive = 0;
		diskBios->buffer = 0;
		diskBios->head = 0;
		diskBios->track = 0;
		diskBios->sector = 0;
		diskBios->nsectors = 1;
		break;
	}
	case DISK_STATUS:
	{	
		BIOS_STATUS = true;
		break;
	}
	case DISK_READ:
	{
		break;
	}
	case  DISK_WRITE:
	{
		break;
	}
	case DISK_VERIFY:
	{
		break;
	}
	case  DISK_FORMAT:
	{
		break;
	}
}
	
	
	return 0;
}

int kmain(void)
{
	const char* str = " =  M�� ������ ���� = ";
	/* ����������� ���������� � ������ 0xb8000 */
	char* vidptr1 = (char*)0xb8000;
	unsigned i = 0;
	unsigned int j = 0;
	unsigned int R = 0;
	unsigned int screensize;
	unsigned char vidptr[4000] = { 0 };
	/* ���� ���� ������� �����
    *  25 ����� � ������ �� 80 ��������; 
	*  ������ ������� �������� 2 �����   */
	screensize = 80 * 25 * 2;
	srand(time(0));
	while ( j < screensize) 
	{
		R = 1 + rand() % 255;
		// ������ ������  -> vidptr [ j ] = '\0'; 
		vidptr [ j ] = R;  // ������� ����������: ��������� ������� ��� ������. **vidptr** ���� 0x11C8112.
		cout << vidptr[ j ];
		// �������-���� 
		vidptr[ j+1 ] = 0x07;
		cout << vidptr[ j ];          // << endl;
		j = j + 2;
	}
	j = 0;
	// ���� ���� ���������� ������ � ����������� 
	while (str[ j ] != '\0') 
	{
		
		vidptr[ i ] = str[ j ];
		/* �������-����: ������� ������� ������ bg � ������-����� fg */
		vidptr [ i +1] = 0x07;
		cout << vidptr[ j ] ;
		++j;
		++i ;

	}
	cout << endl;
	return 0;
}
void BIOS_Init()
{
	typedef int �����;
	����� ����� = 0;
	Bios_Disk((DISK_RESET), 1, 1, 1, 1,1, bufferZ);
	
}
