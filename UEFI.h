#pragma once
// {BDE900DD-190A-4c7d-9663-16BA8ED88B55}
#define EFI_SIMPLE_WINPHONE_IO_PROTOCOL_GUID \
   { 0xbde900dd, 0x190a, 0x4c7d, 0x96, 0x63, 0x16, 0xba, 0x8e, \
   0xd8, 0x8b, 0x55 };
#define EFI_SIMPLE_WINPHONE_IO_PROTOCOL_REVISION   0x00010001
//===============================================================
typedef struct EFIAPI
{
	bool   Initialize;
	bool   Read;
	bool   Write;
	int EFI_SIMPLE_WINPHONE_IO_GET_MAXPACKET_SIZE ;
}EFIAPI;

int  Buffer = 0;  //  Буфер данных для ввода/вывода

int  _EFI_SIMPLE_WINPHONE_IO_PROTOCOL();
int EFI_SIMPLE_WINPHONE_IO_INITIALIZE(int Code);
int  EFI_SIMPLE_WINPHONE_IO_READ();
int EFI_SIMPLE_WINPHONE_IO_WRITE();

//================================================================
int UEFI();