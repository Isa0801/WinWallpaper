#include "WindowManager.hpp"

namespace WinWallpaper {

    BOOL CALLBACK EnumWindowsProc(HWND tophandle, LPARAM lParam) {

        // check if window has child SHELLDLL_DefView, 
        // if contains then we will take next window
        HWND window = FindWindowEx(tophandle, NULL, L"SHELLDLL_DefView", NULL);


        if (window)
        {
            HWND* toRer = (HWND*)lParam;
            *toRer = FindWindowEx(NULL, tophandle, L"WorkerW", NULL);
            return false;
        }


        return true;
    }

    HWND getWPWindow() {
        // find program manager, and get its handler
        HWND progman = FindWindow(L"ProgMan", NULL);

        // send message to program manager, to create new WorkerW window
        SendMessageTimeout(progman, 0x57, NULL, NULL, SMTO_NORMAL, 1000, NULL);


        HWND WorkerW = nullptr;

        EnumWindows(EnumWindowsProc, (LPARAM)&WorkerW);

        return WorkerW;
    }

}