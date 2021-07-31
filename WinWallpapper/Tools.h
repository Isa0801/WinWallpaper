#pragma once
#ifndef Tools_HEADER
#define Tools_HEADER
#include <SFML/Graphics.hpp>
#include "WindowManager.hpp"
#include "Clock.h"
#include <Windows.h>
#include <WinUser.h>
#include <deque>
#include <filesystem>
#include <string>

namespace WinWallpaper {

	class Tools {
	
	public:
		Tools(sf::RenderWindow*);
		~Tools();
		void loadTextureFromDir(std::string);
		void preProcess(sf::Sprite&);
		sf::Sprite transition(sf::Texture&, sf::Texture&, float = 0, bool = true);

		bool centerB = false;
		bool coverB = false;
		bool fitB = false;
		bool fitToCoverB = false;

	private:
		// centers sprite origin and to the screen
		void center(sf::Sprite&);
		// covers whole screen
		void cover(sf::Sprite&);
		// fits sprite to screen
		void fit(sf::Sprite&);
		
		

		sf::RenderTexture mainTexture;
		sf::Sprite mainSprite;
		sf::View mainView;
		std::deque<sf::Texture> texQueu;
		sf::RenderWindow* tWin;
	};

}


#endif // !Tools_HEADER
