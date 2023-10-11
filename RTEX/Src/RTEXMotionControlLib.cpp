#include <vector>
#include <utility>
#include <limits.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "RTEXMotionControlLib.hpp"

//------------------------HID command--------------------------------


//---------------------User command-------------------//
static int res;
static unsigned char buf[256];
#define MAX_STR 255
static wchar_t wstr[MAX_STR];
static hid_device* handle;
static int i;
struct hid_device_info* devs, * cur_dev;
static hid_device** id_device;
static int max_size;

enum task {
	ResetSystemTask = 1,
	SetAxisTask,
	ReAxisTask,
	CreateNetworkTask,
	ReStatusTask,
	ExOOServoTask,
	SetModePPTask,
	ExModePPTask,
	ExModeCPTask,
	ExModeCVTask,
	ExModeCTTask,
	GetResTask
};


//------------------Scan device--------------------------
std::vector<device_info> NhgEnum(unsigned short vendor_id, unsigned short product_id)
{
	std::vector<device_info> device;
	int count = 0, total = 0, res = 0, i = 0;
	hid_device_info* dev = NULL, * cur_dev = NULL;
	hid_device* temp_handle = NULL;
	std::vector<wchar_t*> string;
	wchar_t wstr[MAX_STR], temp[MAX_STR];
	device_info inf;
	//hid_enumerate(vendor_id, product_id);
	res = hid_init();
	dev = hid_enumerate(0x1234, 0x2345);

	for (cur_dev = dev; cur_dev != NULL; cur_dev = cur_dev->next)
	{
		memcpy(temp, cur_dev->serial_number, MAX_STR);
		wcsncpy(temp, cur_dev->serial_number, MAX_STR);
		temp[MAX_STR - 1] = L'\0';
		string.push_back(temp);
		inf.serial_num = cur_dev->serial_number;
		inf.id = count;
		device.push_back(inf);
		count++;
	}
	max_size = device.size();
	printf("There are %d devices connected\n", max_size);
	return device;

}

int32_t NhgIsOpen(wchar_t* Manufacturer, wchar_t* Product, wchar_t* SerialNumber) {
	handle = hid_open(0x1234, 0x2345, L"12110");
	if (!handle)
		return -2;
	hid_set_nonblocking(handle, 1);
	res = hid_read(handle, buf, 17);
	if (res != 0)
		return res; //non block 0, block -1.

	wchar_t KeyManufacturer[MAX_STR] = L"NHG";
	wchar_t KeyProduct[MAX_STR] = L"RTEX MOTION CONTROLLER";
	wchar_t KeySerialNumber[MAX_STR] = L"12110";

	Manufacturer[0] = 0x0000;
	res = hid_get_manufacturer_string(handle, Manufacturer, MAX_STR);
	//printf("Manufacturer:  %ls\n", Manufacturer);
	if (wcscmp(Manufacturer, KeyManufacturer) != 0)
		return -3; //Manufacturer not match

	Product[0] = 0x0000;
	res = hid_get_product_string(handle, Product, MAX_STR);
	if (wcscmp(Product, KeyProduct) != 0)
		return -4;

	SerialNumber[0] = 0x0000;
	res = hid_get_serial_number_string(handle, SerialNumber, MAX_STR);
	if (wcscmp(SerialNumber, KeySerialNumber) != 0)
		return -5; //SerialNumber not match
	return 0;
}


// -----------------Basic command-----------------------
int32_t Div32(int32_t input32, uint8_t* output8) {
	output8[0] = 0xFF & (input32 >> 24);
	output8[1] = 0xFF & (input32 >> 16);
	output8[2] = 0xFF & (input32 >> 8);
	output8[3] = 0xFF & (input32 >> 0);

	return 0;
}

uint32_t Combine32(uint8_t* data8bit) {
	uint32_t temp32;
	temp32 = data8bit[0];
	temp32 = (temp32 << 8) | data8bit[1];
	temp32 = (temp32 << 8) | data8bit[2];
	temp32 = (temp32 << 8) | data8bit[3];
	return temp32;
}

uint8_t Combine16(uint8_t* data8bit) {
	uint8_t temp16;
	temp16 = data8bit[0];
	temp16 = (temp16 << 8) | data8bit[1];
	return temp16;
}

void ResetSystem()
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = ResetSystemTask;
	res = hid_write(handle, UsbTx, 64);
}

uint8_t SetAxis(uint8_t axis)
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = SetAxisTask;
	UsbTx[3] = 0xFF & axis;
	
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write
	
	uint8_t  UsbRx[64];
	std::fill_n(UsbRx, 64, 0);
	res = 0;
	while (res == 0) {
		res = hid_read(handle, UsbRx, 64);
		if (res == 0) {}

		if (res < 0)
			return -5;
	}

	unsigned long r_axis;
	if (UsbRx[2] == ReAxisTask)
	{
		r_axis = UsbRx[3];
		std::cout << "Axis ready: " << r_axis << "\n";
	}

	return 0;
}

uint8_t CreateNetwork()
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = CreateNetworkTask;
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write

	uint8_t  UsbRx[64];
	std::fill_n(UsbRx, 64, 0);
	res = 0;
	while (res == 0) {
		res = hid_read(handle, UsbRx, 64);
		if (res == 0) {}

		if (res < 0)
			return -5;
	}

	unsigned long status;
	if (UsbRx[2] == ReStatusTask)
	{
		status = UsbRx[3];
		switch (status)
		{
			case 0: std::cout << "INIT" << "\n";	break;
			case 1: std::cout << "WAITING" << "\n"; break;
			case 2: std::cout << "PREPARE" << "\n"; break;
			case 3: std::cout << "START" << "\n";	break;
			case 4: std::cout << "RUNNING" << "\n"; break;
			default:								break;
		}

	}

	return 0;
}

uint8_t ExOOServo(int *ID_Status, uint8_t axis)
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = ExOOServoTask;
	for (int i = 0; i < axis; i++)
	{
		UsbTx[i + 3] = ID_Status[i];
	}
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write
	
	uint8_t  UsbRx[64];
	std::fill_n(UsbRx, 64, 0);
	res = 0;
	while (res == 0) {
		res = hid_read(handle, UsbRx, 64);
		if (res == 0) {}

		if (res < 0)
			return -5;
	}

	unsigned long stt0, stt1, stt2;
	stt0 = UsbRx[2];
	stt1 = UsbRx[3];
	stt2 = UsbRx[4];
	std::cout << "stt: " << stt0 << stt1 << stt2 << "\n";
	
	

	return 0;
}

int32_t SetModePP(int32_t *CmdU1, int32_t *CmdU2, int32_t Type_Code, uint8_t axis)
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = SetModePPTask;
	UsbTx[8] = Type_Code;
	for (int i = 0; i < axis; i++) 
	{
		Div32(CmdU1[i], &UsbTx[4 + 10 * i]);
		Div32(CmdU2[i], &UsbTx[9 + 10 * i]);
	}
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write

	return 0;
}

uint8_t ExModePP(int32_t *ControlBit, uint8_t axis) 
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = ExModePPTask;
	for (int i = 0; i < axis; i++) 
	{
		UsbTx[4 + 10 * i] = ControlBit[i];
	}
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write
	return 0;
}

uint8_t ExModeCP(uint8_t macID, uint32_t CmdU1, uint32_t CmdU2, uint8_t Type)
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = ExModeCPTask;
	for (uint8_t i = 0; i < 6; i++) {
		UsbTx[3 + 10 * i] = macID;
		Div32(CmdU1, &UsbTx[4 + 10 * i]);
		UsbTx[8 + 10 * i] = Type;
		Div32(CmdU2, &UsbTx[9 + 10 * i]);
	}
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write
	return 0;
}

uint8_t ExModeCV(uint8_t macID, uint32_t CmdU1, uint32_t CmdU2, uint8_t Type)
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = ExModeCVTask;
	for (uint8_t i = 0; i < 6; i++) {
		UsbTx[3 + 10 * i] = macID;
		Div32(CmdU1, &UsbTx[4 + 10 * i]);
		UsbTx[8 + 10 * i] = Type;
		Div32(CmdU2, &UsbTx[9 + 10 * i]);
	}
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write
	return 0;
}

uint8_t ExModeCT(uint8_t macID, uint32_t CmdU1, uint32_t CmdU2, uint8_t Type)
{
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = ExModeCTTask;
	for (uint8_t i = 0; i < 6; i++) {
		UsbTx[3 + 10 * i] = macID;
		Div32(CmdU1, &UsbTx[4 + 10 * i]);
		UsbTx[8 + 10 * i] = Type;
		Div32(CmdU2, &UsbTx[9 + 10 * i]);
	}
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write
	return 0;
}

uint8_t GetRes(int32_t* data1, int32_t* data2, uint8_t* data3, uint8_t* data4, uint8_t axis)
{	
	uint8_t  UsbTx[64];
	std::fill_n(UsbTx, 64, 0); 	//clear TX buffer
	UsbTx[0] = 0x00;
	UsbTx[1] = 0x00;
	UsbTx[2] = GetResTask;
	
	res = hid_write(handle, UsbTx, 64);
	if (res < 0) return -5; //can't write

	uint8_t temp1[4];
	uint8_t temp2[4];
	uint8_t temp3[4];
	uint8_t temp4[4];

	int32_t temp_pos;
	int32_t temp_optional;
	uint8_t temp_macID;
	uint8_t temp_flag1;

	uint8_t  UsbRx[64];

	uint8_t  size;

	uint8_t n, j;

	std::fill_n(UsbRx, 64, 0);

	res = 0;
	while (res == 0) {
		res = hid_read(handle, UsbRx, 64);
		if (res == 0) {}

		if (res < 0)
			return -5;
	}

	j = 0;

	for (int i = 0; i < axis; i++)
	{
			j = 3 + i * 10;

			temp1[0] = UsbRx[j];

			temp2[0] = UsbRx[j + 1];
			temp2[1] = UsbRx[j + 2];
			temp2[2] = UsbRx[j + 3];
			temp2[3] = UsbRx[j + 4];

			temp1[2] = UsbRx[j+5];

			temp4[0] = UsbRx[j + 6];
			temp4[1] = UsbRx[j + 7];
			temp4[2] = UsbRx[j + 8];
			temp4[3] = UsbRx[j + 9];

			temp_pos = Combine32(&temp2[0]);

			temp_optional = Combine32(&temp4[0]);

			temp_macID = temp1[0];

			temp_flag1 = temp1[2];

			data1[i] = temp_pos;
			data2[i] = temp_optional;
			data3[i] = temp_macID;
			data4[i] = temp_flag1;

		
	}
	return 0;
}

uint8_t CheckFlag1(uint8_t* a, uint8_t b, uint8_t* c, uint8_t axis)
{
	uint8_t temp;

	uint8_t temp_choose;
	uint8_t temp_InProgess  = 00000010;
	uint8_t temp_InPosition = 00000001;

	switch (b)
	{
		case 1:
		temp_choose = temp_InProgess;
		break;

		case 2:
		temp_choose = temp_InPosition;
		break;

		default:
		//No support
		return 1;
	}

	for (int i = 0; i < axis; i++)
	{
		temp = a[i] & temp_choose;

		if (temp == temp_choose)
		{
			c[i] = 1;
		}
		else
		{
			c[i] = 0;
		}
	}
	return 0;
}


//r_axis = UsbRx[3];
//r_axis = (r_axis << 8) | UsbRx[1];
//r_axis = (r_axis << 8) | UsbRx[2];
//r_axis = (r_axis << 8) | UsbRx[3];