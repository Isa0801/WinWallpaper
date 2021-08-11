#include "Audio.h"
#include <iostream>

namespace WinWallpaper {

	static DWORD CALLBACK wasapiProc(void* buffer, DWORD length, void* user) {
		return TRUE;
	}

	Audio::Audio() {


		if (!BASS_Init(0, 48000, 0, 0, NULL)) {
			std::cerr << ("Can't initialize BASS");
			exit(1);
		}

		if (!BASS_WASAPI_Init(-3, 0, 0, BASS_WASAPI_BUFFER, 1, 0.1, &wasapiProc, NULL)) {
			std::cerr << ("Can't initialize wasapi");
			exit(1);
		}

		BASS_WASAPI_GetInfo(&info);


		if (!BASS_WASAPI_Start())
		{
			std::cerr << ("Can't start wasapi");
			exit(1);
		}



	}


	Audio::~Audio() {

		BASS_WASAPI_Stop(
			false
		);

		BASS_Free();
		BASS_WASAPI_Free();
	}

	void Audio::fetchData() {
		BASS_WASAPI_GetData(
			fftData,
			BASS_DATA_FFT1024
		);
	}


}