#include "App.h"
#include <iostream>
#include <vector>




namespace WinWallpaper {

	App::App(){
		appWindow = std::make_shared<sf::RenderWindow>(getWPWindow());
		tool = std::make_shared<Tools>(appWindow.get());
		clock = std::make_shared<Clock>();

		// setting seed, so that we will get random number each run.
		std::srand(std::time(NULL));

		// load only the fragment shader
		if (!shader.loadFromFile("HueShift.frag", sf::Shader::Fragment))
		{
			std::cout << "shader error";
		}

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
		transitionB = state;
	}

	void App::setRndTex(bool state) {
		rndTexB = state;
	}

	void App::setFitToCover(bool state) {
		tool->fitToCoverB = state;
	}

	void App::setSlideShow(bool state) {
		slideShowB = state;
	}

	void App::setBeatOnBass(bool state) {
		beatOnBassB = state;
	}

	void App::setHueShiftOnBeat(bool state) {
		hueShiftOnBeatB = state;
	}

	void App::setHueShift(bool state) {
		hueShiftB = state;
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
		frames = rate;
	}


	//===============end of setter============

	//=============Extra=============

	void App::loadTextureFromDir() {

		if (dir == "")
			return;

		for (const auto& entry : std::filesystem::directory_iterator(dir)) {
			//std::cout << entry.path() << " " << entry.path().extension()  << std::endl;
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

	void App::slideToNextTex() {

		clock->stop();

		// show tex for x amount of ms
		if (!loadNextTexB && clock->getMs() >= imageDurMs)
		{
			clock->getMs(true);
			loadNextTexB = !loadNextTexB;
			if (rndTexB)
				nextTex = std::rand() % queueOfTex.size();
			else
			{
				if (nextTex == queueOfTex.size())
					nextTex = 0;
				else
					nextTex++;
			}
		} else if (loadNextTexB) {
			long mst = clock->getMs();

			// if there are only 1 texture than just return
			if (queueOfTex.size() < 2) {
				clock->getMs(true);
				loadNextTexB = !loadNextTexB;
				return;
			}

			if (mst >= transDurMs || !transitionB)
			{
				clock->getMs(true);
				loadNextTexB = !loadNextTexB;
				mainSprite = tool->transition(queueOfTex[curTex], queueOfTex[nextTex], 1, true);
				curTex = nextTex;

			}
			else
				mainSprite = tool->transition(queueOfTex[curTex], queueOfTex[nextTex], (float)mst / transDurMs, true);
		}

	}

	void App::beatOnBass() {
		audio.fetchData();

		float bv = audio.fftData[0] + audio.fftData[1] + audio.fftData[2] + audio.fftData[3] + audio.fftData[4] + audio.fftData[5] + audio.fftData[6] + audio.fftData[7];
		bv /= 8;

		bv = sqrt(bv) * 100;

		static bool beated = false;


		if (bv >= beatThresshold && !beated){
			counter = 0;
			//std::cout << bv << " bass beat\n";

			sf::View v = appWindow.get()->getDefaultView();

			if (hueShiftOnBeatB)
				hueShiftValue += 0.10f;

			if (bv >= 15){
				v.zoom(0.98f);
			}
			else{
				v.zoom(0.99f);
			}


			appWindow.get()->setView(v);
			beated = true;

		}
		else if (counter > frames / 4 && beated) {
			counter = 0;
			//std::cout << " reset beat\n";
			beated = !beated;
			appWindow.get()->setView(appWindow.get()->getDefaultView());
		}

	}

	void App::hueShift() {

		hueShiftValue += 0.01f;

		if (hueShiftValue > 2 * 3.1415f)
		{
			hueShiftValue = 0.0f;
		}

		shader.setUniform("texture", sf::Shader::CurrentTexture);

		shader.setUniform("shift", hueShiftValue);
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

		
		tool->preProcess(mainSprite);

		if (slideShowB)
			slideToNextTex();

		if (beatOnBassB)
			beatOnBass();

		if (hueShiftB)
			hueShift();

	}

	void App::render() {

		if (!isOpen())
			return;

		if (beatOnBassB)
			counter++;

		appWindow->clear();
		appWindow->draw(mainSprite, &shader);
		appWindow->display();

	}


	//===========end of app==============

}

