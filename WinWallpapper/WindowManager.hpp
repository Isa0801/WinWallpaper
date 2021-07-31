/*
 returns hwnd of the desktop
*/

#pragma once

#ifndef WALLPAPPER_MANAGER
#define WALLPAPPER_MANAGER
#include <Windows.h>
#include <WinUser.h>

namespace WinWallpaper {

    BOOL CALLBACK EnumWindowsProc(HWND, LPARAM);
    HWND getWPWindow();

}
#endif // !WALLPAPPER_MANAGER

