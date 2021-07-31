#pragma once
#ifndef Clock_HEADER
#define Clock_HEADER
#include <chrono>

namespace WinWallpaper {

	class Clock
	{
	public:
		Clock();
		~Clock();
		void start();
		void stop();
		long getMs(bool = false);

	private:
		std::chrono::high_resolution_clock::time_point startTime;
		std::chrono::high_resolution_clock::time_point currentTime;
		void reset();
	};


}


#endif // !Clock_HEADER
