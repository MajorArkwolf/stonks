#include "Audio.hpp"

#include "Engine.hpp"
using Stonk::Audio;

auto Audio::PlaySound(Audio::Sound audio, int playcount) -> int {
    auto result =
        Mix_PlayChannel(-1, this->audioChunks.at(audio).get(), playcount - 1);
    return result;
}
void Audio::PlayMusic(Audio::Music music, int playcount) {
    Mix_PlayMusic(this->musicChunks.at(music).get(), playcount - 1);
}
void Audio::StopMusic() {
    Mix_HaltMusic();
}
void Audio::StopSound(int channel) {
    Mix_HaltChannel(channel);
}
auto Audio::LoadSound(std::string filename) -> Audio::Sound {
    auto find = loadedSounds.find(filename);
    if (find != loadedSounds.end()) {
        return find->second;
    }
    auto filepath = Stonk::Engine::get().basepath + "res/sound/" + filename;
    auto chunk    = Audio::Chunk{Mix_LoadWAV(filepath.c_str()), &Mix_FreeChunk};
    this->audioChunks.push_back(std::move(chunk));
    auto soundIndex        = this->audioChunks.size() - 1;
    loadedSounds[filename] = soundIndex;
    return soundIndex;
}
auto Audio::LoadMusic(std::string filename) -> Audio::Music {
    auto find = loadedMusic.find(filename);
    if (find != loadedMusic.end()) {
        return find->second;
    }
    auto filepath = Stonk::Engine::get().basepath + "res/sound/" + filename;
    auto chunk = Audio::MusicChunk{Mix_LoadMUS(filepath.c_str()), &Mix_FreeMusic};
    this->musicChunks.push_back(std::move(chunk));
    auto musicIndex       = this->musicChunks.size() - 1;
    loadedMusic[filename] = musicIndex;
    return musicIndex;
}

#include <iostream>
void Audio::Init() {
    const auto channelCount = 16;
    auto freq               = 22050;     // recommended by below link
    ushort format           = AUDIO_F32; // arbitrary choice
    auto channels           = 2;         // stereo
    auto chunksize          = 1024;      // arbitrary choice
    // see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html
    Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
    Mix_OpenAudio(freq, format, channels, chunksize);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    Mix_Volume(-1, MIX_MAX_VOLUME);
    Mix_AllocateChannels(channelCount);
}
Audio::~Audio() {
    Mix_CloseAudio();
    while (Mix_Init(0)) {
        // see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html
        Mix_Quit();
    }
}
