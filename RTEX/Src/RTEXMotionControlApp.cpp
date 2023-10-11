#include "RTEXMotionControlLib.hpp"
using namespace std;
#define MAX_STR 255
static uint8_t k = 0;
static int      RunCmd = 0;
static int      MovFlag = 0;
static int      CmdFlag = 1;
static int      axis = 0;
static int      mode = 0;
static int      ID_Status[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static int      macID[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static int32_t    CmdU1[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static int32_t    CmdU2[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static int32_t    Type_Code = 0;
static int      choose[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

static uint8_t a[6] = { 1,1,1,1,1,1 };
static int32_t data1[6];
static int32_t data2[6];
static uint8_t data3[6];
static uint8_t data4[6] = {0,0,0,0,0,0};
static uint8_t c[6] = { 0,0,0,0,0,0 };
static int re = 0;

int32_t Cmd1Temp[32] = { 150000,210311,-143459,0,-23115,168750,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int32_t Cmd2Temp[32] = { 30000,40000,20000,0,5000,20000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int32_t Cmd3Temp[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int32_t Cmd4Temp[32] = { 30000,40000,20000,0,5000,20000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

static uint8_t size;

int32_t ErrPromt(int32_t ErrCode) {
    if (ErrCode == 0) return 0;
    std::wcout << "ErrCode: " << ErrCode << "\n";
    std::wcout << "Check USB connection" << "\n";
    return ErrCode;
}

void thread_Transmit_CommandData()
{

    while (1)
    {
        std::wcout << "Input RunCmd: ";
        std::cin >> RunCmd;

        if (CmdFlag == 1) //CmdFlag
        {
            switch (RunCmd) {
            case 1:
                std::cout << "Reset System" << "\n";
                ResetSystem();
                break;

            case 2:
                std::cout << "Set number of axis: ";
                std::cin >> axis;
                SetAxis(axis);
                break;

            case 3:
                std::wcout << "Create network" << "\n";
                CreateNetwork();
                break;

            case 4:
                std::wcout << "Excute On/Off Servo" << "\n";
                for (int i = 0; i < axis; i++)
                {
                    std::cout << "Status ID " << i << ": ";
                    std::cin >> ID_Status[i];
                }
                ExOOServo(ID_Status, axis);
                break;

            case 5:
                std::wcout << "Set Mode PP" << "\n";
                for (int i = 0; i < axis; i++)
                {
                    std::wcout << "Target_Position ID " << i << ": ";
                    std::cin >> CmdU1[i];
                    std::wcout << "Target_Speed ID " << i << ": ";
                    std::cin >> CmdU2[i];
                    std::wcout << "\n";
                }
                std::wcout << "Type Abs/Rel/Cons(16/17/...): ";
                std::cin >> Type_Code;
                SetModePP(CmdU1, CmdU2, Type_Code, axis);
                break;

            case 6:
                std::wcout << "Excute Mode PP" << "\n";
                for (int i = 0; i < axis; i++)
                {
                    //std::wcout << "\n" << "Choose Function ID " << i << ": ";
                    //std::cin >> choose[i];
                    choose[i] = 1;
                }
                ExModePP(choose, axis);
                break;

            case 7: //vl
                k ^= 1;
                break;
            
            case 8:

                
                SetModePP(Cmd1Temp, Cmd2Temp, 16, 6);
                break;

            case 9:

                SetModePP(Cmd3Temp, Cmd4Temp, 16, 6);
                break;

            case 10:
                ExModePP(choose, 6);
                break;

            case 11:
                GetRes(data1, data2, data3, data4, axis);
                CheckFlag1(data4, 2, c, axis);
                
                break;

            case -1:
                std::wcout << "Press Enter to exit" << "\n";
                CmdFlag = 0;
                break;

            default: std::wcout << "Command not support" << "\n";
                break;
            }

            RunCmd = -2;
        } //end while CmdFlag
    }
}
    void thread_Receive_RespondData()
    {
        while (1)
        {
            if (k == 1)
            {
                GetRes(data1, data2, data3, data4, axis);

                for (int i = 0; i < axis; i++)
                {
                    std::wcout << " Posion Axis " << i << ":" << data1[i] << "\n";
                }

                for (int i = 0; i < axis; i++)
                {
                    std::wcout << " Velocity Axis " << i << ":" << data2[i] << "\n";
                }
            }

            sleep(1000);
        }
    }

    int main()
    {

        int32_t ErrCode = 0;
        wchar_t _Manufacturer[MAX_STR];
        wchar_t _Product[MAX_STR];
        wchar_t _SerialNumber[MAX_STR];

        // First, check error
        NhgEnum(0x1234, 0x2345);


        ErrCode = NhgIsOpen(_Manufacturer, _Product, _SerialNumber);
        if (ErrCode != 0) {
            std::wcout << "ErrCode: " << ErrCode << "\n";
            std::wcout << "Check USB connection" << "\n";
            return ErrCode;
        }

        std::wcout << "Manufacturer: " << _Manufacturer << "\n";
        std::wcout << "Product: " << _Product << "\n";
        std::wcout << "SerialNumber: " << _SerialNumber << "\n";

        if (ErrCode != 0) {
            std::wcout << "ErrCode: " << ErrCode << "\n";
            return 0;
        }

        std::wcout << "\n\nRuncmd list:" << "\n";
        std::wcout << "1: Reset" << "\n";
        std::wcout << "2: Set number of axis" << "\n";
        std::wcout << "3: Create network" << "\n";
        std::wcout << "4: Excute On/Off Servo" << "\n";
        std::wcout << "5: Set Mode PP" << "\n";
        std::wcout << "6: Excute Mode PP" << "\n";
        std::wcout << "7: Excute Mode CP" << "\n";
        std::wcout << "8: Excute Mode CV" << "\n";
        std::wcout << "9: Excute Mode CT" << "\n";
        std::wcout << "-1: Exit\n";

        thread funcTest1(thread_Transmit_CommandData);
        thread funcTest2(thread_Receive_RespondData);
        funcTest1.join();
        funcTest2.join();
        //get code for command


        std::cin.get();

    }
