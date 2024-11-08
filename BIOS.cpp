 /*	
  * Модуль BIOS	 4.02.08.00 52EE5.E8.E8
  * Программист - Помазков М.В.
  * Email - bps9970@gmail.com
  * Дата начала разработки - 18.01.2022 21.31 [ 18.01.2077 ]
  * www.uos.robco.developer	Robco Corp, 2077, All Rights Reserved.
 */
#include "BIOS.H"
#include <iostream>
#include <iostream>
#include <string>
using namespace std;
// ================================================
bool BIOS_STATUS = false;
FILE *FILE_BIOS;
const char *FILE_NAME ="C:\\UOS\\bios.rom";	 // Файл BIOS - bios.rom
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
		cout << "Файл BIOS открыт: "<< FILE_NAME << endl;
		fseek(FILE_BIOS, 0, SEEK_END);		 //	  Размер	||
		size = ftell(FILE_BIOS);			//	 открытого	||
		fseek(FILE_BIOS, 0, SEEK_SET);	   //	  файла		||
		cout << "Размер файла BIOS: " << size << " байт." <<endl;
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
		diskBios -> drive = 0;
		diskBios -> buffer = 0;
		diskBios -> head = 0;
		diskBios -> track = 0;
		diskBios -> sector = 0;
		diskBios -> nsectors = 1;
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


static void BIOS_Init()
{
	typedef int Лунгу;
	Лунгу лунгу = 0;
	Bios_Disk((DISK_RESET), 1, 1, 1, 1,1, bufferZ);
	лунгу = лунгу + 1;
	лунгу = лунгу++;
	cout << "Лунгу: " << лунгу << endl;
}
//-------------------------------------------------------
int Kernel(void)
// processor: x86
{
	// Naked functions must provide their own prolog...
	__asm 
	{
		push ebp
		mov ebp, esp
		sub esp, __LOCAL_SIZE
		mov al, 4
		mov dx, 0xD007
		out dx, al
		; -------------------
		nop; Выравнивание
		nop;     по
		nop;   стеку
		; -------------------
		pop ebp
		mov al, 2
		mov dx, 0xD007
		out dx, al
		; ------------------
		nop; Выравнивание
		nop;      по
		nop;    стеку
		;-------------------
		bits 32
		section.text
		; multiboot spec
		align 4
		dd 0x1BADB002; magic
		dd 0x00; flags
		dd - (0x1BADB002 + 0x00); checksum.m + f + c should be zero
		; -----------------------------
		global start
		extern kmain x; this is defined in the c file
		; ----------------------------
		start :
		cli; block interrupts
			mov esp, stack_space; set stack pointer
			call kmain
			hlt; halt the CPU
			; ------------------------------
			section.bss
			resb 8192; 8KB for stack
			stack_space :
		ret
	}

	// ... and epilog
	__asm 
	{
		ret
	}
	//-----------------------------------------------
	const char* str = " =  Mое первое ядро = ";
	/* видеопамять начинается с адреса 0xb8000 */
	char* vidptr1 = (char*)0xb8000;
	unsigned i = 0;
	unsigned int j = 0;
	unsigned int R = 0;
	unsigned int screensize;
	unsigned char vidptr[4000] = { 0 };
	/* Этот цикл очищает экран
	*  25 строк в каждой из 80 столбцов;
	*  каждый элемент занимает 2 байта   */
	screensize = 80 * 25 * 2;
	srand(time(0));
	while (j < screensize)
	{
		R = 1 + rand() % 255;
		// пустой символ  -> vidptr [ j ] = '\0'; 
		vidptr[j] = R;  // Вызвано исключение: нарушение доступа для записи. **vidptr** было 0x11C8112.
		cout << vidptr[j];
		// атрибут-байт 
		vidptr[j + 1] = 0x07;
		cout << vidptr[j];          // << endl;
		j = j + 2;
	}
	j = 0;
	// этот цикл записывает строку в видеопамять 
	while (str[j] != '\0')
	{

		vidptr[i] = str[j];
		/* атрибут-байт: придать символу черный bg и светло-серый fg */
		vidptr[i + 1] = 0x07;
		cout << vidptr[j];
		++j;
		++i;

	}
	cout << endl;
	return 0;
}
//-----------------------------------------------------------

void __declspec(naked) main()
// Copyright(C) 2014  Arjun Sreedharan
// License: GPL version 2 or higher 
// http : www.gnu.org/licenses/gpl.htm

{
	_asm
	{
	
	}
}

