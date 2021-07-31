#include "Clock.h"

namespace WinWallpaper {


	Clock::Clock() {
		start();
	}
	Clock::~Clock() {

	}

	void Clock::start() {
		startTime = std::chrono::high_resolution_clock::now();
		currentTime = std::chrono::high_resolution_clock::now();
	}

	void Clock::stop() {
		currentTime = std::chrono::high_resolution_clock::now();
	}

	long Clock::getMs(bool resetClock) {


		auto diff = currentTime - startTime;

		if (resetClock)
			reset();



		return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

	}


	void Clock::reset() {
		startTime = std::chrono::high_resolution_clock::now();
	}


}