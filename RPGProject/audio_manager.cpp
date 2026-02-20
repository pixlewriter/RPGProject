#define MINIAUDIO_IMPLEMENTATION
#include "audio_manager.h"
#include <iostream>
ma_engine engine;

bool init_audio() {
	return ma_engine_init(NULL, &engine) == MA_SUCCESS;

}

void play_effect(const char* filepath) {
	ma_engine_play_sound(&engine, filepath, NULL);
	ma_result result = ma_engine_play_sound(&engine, filepath, NULL);
	if (result != MA_SUCCESS) {
		// This will print to your console if the path is wrong!
		std::cout << "AUDIO ERROR: Cannot find file at " << filepath << std::endl;
	}
}

void cleanup_audio() {
	ma_engine_uninit(&engine);
}
