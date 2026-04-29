#pragma once

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "miniaudio.h"

bool init_audio();

void play_effect(const char* filepath);

void start_music(const char* filepath, bool loop);

void stop_music();

void cleanup_audio();

void cleanup_audio();

#endif