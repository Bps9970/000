#pragma once
#include "UEFI.h"

int  EFI_SIMPLE_WINPHONE_IO_INITIALIZE(int Code)
/*
	 ������� ���������� ���� �� ��������� �������� :
		��� ���������	                                ��������
		EFI_SUCCESS	                       ������� ���������� �������.
		EFI_INVALID_PARAMETER     ������������ ��������.
		EFI_DEVICE_ERROR	               ���������� ���������� �������� �� ������.
		EFI_NOT_READY	                   ���������� ���������� ������ ��� �� ������ � ��������� ����� �������.
		EFI_TIMEOUT	                       ����� �������� ������� �� ������������ ����������.
		EFI_NO_RESPONSE	               ���������� � ����� �� ���������� ��� ���� ���������.

		  */
{
	
	int    ConnectionTimeout = 0;    // ���������� ����������� �������� ����������� � �������� ����������.
	int    ReadWriteTimeout = 0;    // ���������� �����������, � ������� ������� ��������� ���������� �������� ������ � ������.
	return 0;
}

int  _EFI_SIMPLE_WINPHONE_IO_PROTOCOL()
{

	__int32    Revision = EFI_SIMPLE_WINPHONE_IO_PROTOCOL_REVISION;
	EFI_SIMPLE_WINPHONE_IO_INITIALIZE(1);
	EFI_SIMPLE_WINPHONE_IO_READ();
	void* Reserved =0;
	EFI_SIMPLE_WINPHONE_IO_WRITE();
	//EFIAPI.EFI_SIMPLE_WINPHONE_IO_GET_MAXPACKET_SIZE =512;
	return 0;
}


int  EFI_SIMPLE_WINPHONE_IO_READ()
{
	int      NumberOfBytesToRead = 0;	                         //   ������������ ����� ������ ��� ������.
	int      NumberOfBytesRead = 0;	                              //  ����� ������, ������������ � ����� � ������.
	return 0;
}

int  EFI_SIMPLE_WINPHONE_IO_WRITE()
{
	int    NumberOfBytesToWrite = 0;	         // ����� ������, ������������ �� ����������.
	int   NumberOfBytesWritten = 0;		     // ����� ������, ���������� ���������� � ������
	if (Buffer == 0)
	{
		Buffer = Buffer++;
    }
	else 
	{
	}
	return 0;
}

int UEFI()
{
	return 0;
}