/*
 tools will take effects on sprites/texture,
 like centering to the screen, scalling sprites and etc
*/

#pragma once
#ifndef Tools_HEADER
#define Tools_HEADER
#include <SFML/Graphics.hpp>
#include "WindowManager.hpp"
#include <Windows.h>
#include <WinUser.h>
#include <filesystem>
#include <string>

namespace WinWallpaper {

	class Tools {
	
	public:
		Tools(sf::RenderWindow*);
		~Tools();
		// calls all of the options such as center, cover and fit
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
		sf::RenderWindow* tWin;
	};

}


#endif // !Tools_HEADER
