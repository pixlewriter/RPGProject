#define MINIAUDIO_IMPLEMENTATION
#include "audio_manager.h"
#include <iostream>
ma_engine engine;
ma_sound bgm;            
bool isMusicLoaded = false;



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
void start_music(const char* filepath, bool loop) {
    if (isMusicLoaded) {
        ma_sound_uninit(&bgm);
        isMusicLoaded = false;
    }

    ma_result result = ma_sound_init_from_file(&engine, filepath, 0, NULL, NULL, &bgm);
    if (result != MA_SUCCESS) {
        std::cout << "AUDIO ERROR: Music file not found: " << filepath << std::endl;
        return;
    }

    if (loop) {
        ma_sound_set_looping(&bgm, MA_TRUE);
    }

    ma_sound_start(&bgm);
    isMusicLoaded = true;
}

void stop_music() {
    if (isMusicLoaded) {
        ma_sound_stop(&bgm);
        ma_sound_uninit(&bgm);
        isMusicLoaded = false;
    }
}

void cleanup_audio() {
    if (isMusicLoaded) {
        ma_sound_uninit(&bgm);
    }
	ma_engine_uninit(&engine);
}
