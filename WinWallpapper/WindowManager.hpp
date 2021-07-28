#pragma once

#ifndef WALLPAPPER_MANAGER
#include <Windows.h>
#include <WinUser.h>

namespace WindowManager {

    BOOL CALLBACK EnumWindowsProc(HWND, LPARAM);
    HWND getWPWindow();


}
#endif // !WALLPAPPER_MANAGER

