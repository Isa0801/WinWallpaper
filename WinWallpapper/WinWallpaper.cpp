// WinWallpapper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "WindowManager.hpp"
#include "Tools.h"
#include <chrono>
#include "Clock.h"
#include "App.h"
#include <deque>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;



int main(int argc, char** argv)
{

    WinWallpaper::App app;

    // hardcoding for now
    app.setDir("C:/Users/warri/Desktop/aa/");

    app.setCenter(true);
    app.setFitToCover(true);
    app.setSlideShow(true);
    app.setTransition(true);
    app.setFrameLimit(30);
    app.setRndTex(true);
    app.setBeatOnBass(true);
    app.setHueShift(true);
    app.setHueShiftOnBeat(true);

    while (app.isOpen())
    {
        app.events();
        app.update();
        app.render();

    }


    return 0;

}
