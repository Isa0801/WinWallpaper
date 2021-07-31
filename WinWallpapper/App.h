/*
 App will take care of drawing images on desktop window,
 you can pass path of images (png or jpg) by setDir(path).
 you have different options, such transition, transition durration,
 image durration and etc. keep in mind to setFrameLimit(rate) so your gpu wont try to get maximum rate.
*/

#pragma once
#ifndef App_HEADER
#define App_HEADER
#include <SFML/Graphics.hpp>
#include "Clock.h"
#include "Tools.h"
#include "WindowManager.hpp"
#include <thread>
#include <mutex>
#include <memory>
#include <deque>
#include <time.h> 
#include <filesystem>
#include <Audioclient.h>
#include <Audiopolicy.h>
#include <mmdeviceapi.h>

namespace WinWallpaper {

	class App
	{
	public:
		App();
		~App();
		bool isOpen();
		void events();
		void update();
		void render();

		void setDir(std::string);
		void setFrameLimit(int);
		void setImgDurMs(long);
		void setTransDurMs(long);

		void setCenter(bool);
		void setCover(bool);
		void setFit(bool);
		void setFitToCover(bool);
		void setTransition(bool);
		void setSlideShow(bool);
		void setRndTex(bool);
		

	private:
		IMMDevice* pDevice = NULL;
		IAudioClient* pClient = NULL;
		std::shared_ptr<sf::RenderWindow> appWindow;
		std::shared_ptr<Tools> tool;
		std::shared_ptr<Clock> clock;
		std::deque<sf::Texture> queueOfTex;
		sf::Sprite mainSprite;
		std::string dir;
		std::mutex guard;
		int curTex = 0;
		int nextTex = 1;
		bool transition = false;
		bool slideShow = false;
		bool rndTex = false;
		bool loadNextTex = false;
		long imageDurMs = 5000;
		long transDurMs = 3000;

		void loadTextureFromDir();
	};


}


#endif // !App_HEADER
