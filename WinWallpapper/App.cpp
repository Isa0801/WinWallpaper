#include "App.h"
#include <iostream>

namespace WinWallpaper {

	App::App(){
		appWindow = std::make_shared<sf::RenderWindow>(getWPWindow());
		tool = std::make_shared<Tools>(appWindow.get());
		clock = std::make_shared<Clock>();

		// setting seed, so that we will get random number each run.
		std::srand(std::time(NULL));

	}

	App::~App() {
		if (appWindow->isOpen())
			appWindow->close();
	}

	//===============setter============
	void App::setCenter(bool state) {
		tool->centerB = state;
	}

	void App::setCover(bool state) {
		tool->coverB = state;
	}

	void App::setFit(bool state) {
		tool->fitB = state;
	}

	void App::setTransition(bool state) {
		transition = state;
	}

	void App::setRndTex(bool state) {
		rndTex = state;
	}

	void App::setFitToCover(bool state) {
		tool->fitToCoverB = state;
	}

	void App::setSlideShow(bool state) {
		slideShow = state;
	}

	void App::setDir(std::string path){
		dir = path;
		loadTextureFromDir();
	}

	void App::setImgDurMs(long ms) {
		imageDurMs = ms;
	}

	void App::setTransDurMs(long ms) {
		transDurMs = ms;
	}

	void App::setFrameLimit(int rate) {
		appWindow->setFramerateLimit(rate);
	}

	//===============end of setter============

	//=============Extra=============

	void App::loadTextureFromDir() {

		if (dir == "")
			return;

		for (const auto& entry : std::filesystem::directory_iterator(dir)) {
			std::cout << entry.path() << " " << entry.path().extension()  << std::endl;
			if (!entry.exists())
				continue;
			if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
			{
				sf::Texture temp;
				temp.loadFromFile(entry.path().u8string());
				temp.setSmooth(true);

				queueOfTex.push_back(temp);

			}

		}

		curTex = std::rand() % queueOfTex.size();

		if (!queueOfTex.empty())
			mainSprite.setTexture(queueOfTex[curTex]);

	}

	bool App::isOpen() {
		return appWindow->isOpen();
	}

	//=============end of Extra=============

	//===========Logic of app==============

	void App::events() {
		sf::Event event;
		while (appWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				appWindow->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			appWindow->close();
		}
	}

	void App::update() {

		audio.fetchData();
		

		tool->preProcess(mainSprite);
		clock->stop();
		if (!loadNextTex && clock->getMs() >= imageDurMs && slideShow)
		{
			clock->getMs(true);
			loadNextTex = !loadNextTex;
			if (rndTex)
				nextTex = std::rand()% queueOfTex.size();
			else
			{
				if (nextTex == queueOfTex.size())
					nextTex = 0;
				else
					nextTex++;
			}
		}

		if (loadNextTex && slideShow) {
			long mst = clock->getMs();

			if(queueOfTex.size() < 2){
				clock->getMs(true);
				loadNextTex = !loadNextTex;
			}




			if (mst >= transDurMs || !transition)
			{
				clock->getMs(true);
				loadNextTex = !loadNextTex;
				mainSprite = tool->transition(queueOfTex[curTex], queueOfTex[nextTex], 1, true);
				curTex = nextTex;

			}
			else
				mainSprite = tool->transition(queueOfTex[curTex], queueOfTex[nextTex], (float)mst / transDurMs, true);
		}
		
	}

	void App::render() {

		if (!isOpen())
			return;

		appWindow->clear();
		appWindow->draw(mainSprite);
		appWindow->display();

	}


	//===========end of app==============

}

