#pragma once
#ifndef Audio_HEADER
#define Audio_HEADER
#include <chrono>
#include <bass.h>
#include <basswasapi.h>

namespace WinWallpaper {

	class Audio
	{
	public:
		Audio();
		~Audio();
		void fetchData();
		float fftData[512];

	private:
		BASS_WASAPI_INFO info;
		

	};


}


#endif // !Audio_HEADER
