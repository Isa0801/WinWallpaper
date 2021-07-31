#include "Tools.h"
#include <iostream>

namespace WinWallpaper {


	Tools::Tools(sf::RenderWindow* tWin){
		this->tWin = tWin;
		mainTexture.create(tWin->getSize().x, tWin->getSize().y);
	}

	Tools::~Tools() {
	}


	void Tools::center(sf::Sprite& sprite) {
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(tWin->getSize().x/2, tWin->getSize().y / 2);
	}

	void Tools::cover(sf::Sprite& sprite) {
		sprite.setScale(tWin->getSize().x / sprite.getLocalBounds().width,
			tWin->getSize().y / sprite.getLocalBounds().height);
	}

	void Tools::fit(sf::Sprite& sprite) {

		// get the diff between sprite and screen
		float diffx = sprite.getLocalBounds().width - tWin->getSize().x ;
		float diffy = sprite.getLocalBounds().height - tWin->getSize().y ;

		float spriteHeight = sprite.getLocalBounds().height;
		float spriteWidth = sprite.getLocalBounds().width;

		// check if sprite is bigger than screen
		if (diffx > 0 || diffy > 0)
		{
			// get aspect ratio of sprite
			double ratio = sprite.getLocalBounds().height / sprite.getLocalBounds().width;

			// if width is larger than height, than get make it screen width,
			// and apply aspect ratio to height else opposite
			if (diffx > diffy) {

				spriteWidth = spriteWidth - diffx;


				spriteHeight = spriteWidth * ratio;

			}
			else if (diffx < diffy) {

				spriteHeight = spriteHeight - diffy;

				spriteWidth = spriteHeight / ratio;

			}

		}

		sprite.setScale(spriteWidth / sprite.getLocalBounds().width,
			spriteHeight / sprite.getLocalBounds().height);
	}

	sf::Sprite Tools::transition(sf::Texture& from, sf::Texture& to, float pre, bool processTex) {

		if (pre < 0.0f || pre > 1.0f) {
			pre = 1.0f;
		}

		mainTexture.clear();
		sf::Sprite temp;
		temp.setTexture(from);
		sf::Color tempColor = temp.getColor();

		tempColor.a = 255 - (255*pre);
		temp.setColor(tempColor);

		if (processTex)
			preProcess(temp);

		mainTexture.draw(temp);
		
		temp = sf::Sprite();

		temp.setTexture(to);
		tempColor = temp.getColor();

		tempColor.a = (255 * pre);
		temp.setColor(tempColor);



		if (processTex)
			preProcess(temp);

		mainTexture.draw(temp);

		mainTexture.display();
		sf::Sprite ret;
		ret.setTexture(mainTexture.getTexture());
		return ret;		
		
	}

	void Tools::preProcess(sf::Sprite& sprite) {
		
		if (fitToCoverB) {
			if (sprite.getGlobalBounds().width < tWin->getSize().x
				&& sprite.getGlobalBounds().height < tWin->getSize().y)
				cover(sprite);
			else if (sprite.getGlobalBounds().width > tWin->getSize().x
				|| sprite.getGlobalBounds().height > tWin->getSize().y)
				fit(sprite);
		}
		else if (fitB)
			fit(sprite);
		else if (coverB)
			cover(sprite);

		if (centerB)
			center(sprite);

	}


}