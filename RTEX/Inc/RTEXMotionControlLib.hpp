#pragma once
#ifndef _RTEXMotionController_library_h
#define _RTEXMotionController_library_h

#ifdef RTEXMOTIONCONTROLLER_EXPORTS
#define NHGMOTIONCONTROLLER_API __declspec(dllexport)
#else
#define  __declspec(dllimport)
#endif

#endif

#pragma once
#include <hidapi/hidapi.h>
#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>  

struct device_info
{
	wchar_t* serial_num;
	int id;
};


 std::vector<device_info> NhgEnum(unsigned short vendor_id, unsigned short product_id);

extern "C" {
	//must run first for get USB infos
	
	 int32_t NhgIsOpen(wchar_t* Manufacturer, wchar_t* Product, wchar_t* SerialNumber);

	 void ResetSystem();

	 uint8_t SetAxis(uint8_t axis);

	 uint8_t CreateNetwork();

	 uint8_t ExOOServo(int* ID_Status, uint8_t axis);

	 int32_t SetModePP(int32_t* CmdU1, int32_t* CmdU2, int32_t Type_Code, uint8_t axis);

	 uint8_t ExModePP(int32_t* ControlBit, uint8_t axis);

	 uint8_t ExModeCP(uint8_t macID, uint32_t CmdU1, uint32_t CmdU2, uint8_t Type);

	 uint8_t ExModeCV(uint8_t macID, uint32_t CmdU1, uint32_t CmdU2, uint8_t Type);

	 uint8_t ExModeCT(uint8_t macID, uint32_t CmdU1, uint32_t CmdU2, uint8_t Type);

	 uint8_t GetRes(int32_t* data1, int32_t* data2, uint8_t* data3, uint8_t* data4, uint8_t axis);

	 uint8_t CheckFlag1(uint8_t* a, uint8_t b, uint8_t* c, uint8_t axis);
}
