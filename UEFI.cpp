#pragma once
#include "UEFI.h"

int  EFI_SIMPLE_WINPHONE_IO_INITIALIZE(int Code)
/*
	 Функция возвращает одно из следующих значений :
		Код состояния	                                Описание
		EFI_SUCCESS	                       Функция возвращена успешно.
		EFI_INVALID_PARAMETER     Недопустимый параметр.
		EFI_DEVICE_ERROR	               Физическое устройство сообщило об ошибке.
		EFI_NOT_READY	                   Физическое устройство занято или не готово к обработке этого запроса.
		EFI_TIMEOUT	                       Время ожидания истекло до установления соединения.
		EFI_NO_RESPONSE	               Соединение с узлом не существует или было завершено.

		  */
{
	
	int    ConnectionTimeout = 0;    // Количество миллисекунд ожидания подключения с главного компьютера.
	int    ReadWriteTimeout = 0;    // Количество миллисекунд, в течение которых ожидается завершение операций чтения и записи.
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
	int      NumberOfBytesToRead = 0;	                         //   Максимальное число байтов для чтения.
	int      NumberOfBytesRead = 0;	                              //  Объем данных, возвращаемых в буфер в байтах.
	return 0;
}

int  EFI_SIMPLE_WINPHONE_IO_WRITE()
{
	int    NumberOfBytesToWrite = 0;	         // Число байтов, записываемых на устройство.
	int   NumberOfBytesWritten = 0;		     // Объем данных, фактически записанных в байтах
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