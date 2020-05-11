#include "ftd2xx.h"
#include "WinTypes.h"
#include <iostream>
#include <cstring>

int main(int argc, char **argv)
{
	DWORD i = 0;
	FT_STATUS status;
/*
	DWORD num = 0;
	status = FT_CreateDeviceInfoList(&num);
	std::cout << "status : " << status << " num = " << num << std::endl;

	FT_DEVICE_LIST_INFO_NODE * devInfo = new FT_DEVICE_LIST_INFO_NODE[num];
	if (FT_GetDeviceInfoList(devInfo, &num) == FT_OK)
	{
		for (i=0; i<num; ++i)
		{
			std::cout << devInfo[i].Description << std::endl;
			std::cout << devInfo[i].SerialNumber << std::endl;

	FT_HANDLE _handle = devInfo[i].ftHandle;
*/
	FT_HANDLE _handle;
	status = FT_Open(i, &_handle);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_Open !" << std::endl;
		return -1;
	}

	status = FT_ResetDevice(_handle);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_ResetDevice !" << std::endl;
		return -1;
	}

	status = FT_SetDataCharacteristics(_handle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_NONE);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_SetDataCharacteristics !" << std::endl;
		return -1;
	}

	status = FT_SetBaudRate(_handle, 250000);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_SetBaudRate !" << std::endl;
		return -1;
	}

	status = FT_SetFlowControl(_handle, 0, 0, 0);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_SetFlowControl !" << std::endl;
		return -1;
	}

	status = FT_SetBreakOn(_handle);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_SetBreakOn !" << std::endl;
		return -1;
	}

	status = FT_SetBreakOff(_handle);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_SetBreakOff !" << std::endl;
		return -1;
	}

	DWORD written = 0;
	DWORD data_length = 16 * 3 + 1;
	char data[data_length];
	memset(data, 0, data_length);
	data[1] = 0xFF;
	status = FT_Write(_handle, data, data_length, &written);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_Write !" << std::endl;
		return -1;
	}

	status = FT_Close(_handle);
	if (status != FT_OK)
	{
		std::cerr << "erreur FT_Close !" << std::endl;
		return -1;
	}
/*
		}
	}
	delete[] devInfo;
*/
	return 0;
}

