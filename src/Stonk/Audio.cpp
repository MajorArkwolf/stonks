#include "Audio.hpp"

#include "Engine.hpp"
using Stonk::Audio;

void Audio::PlaySound(Audio::Sound audio, int playcount) {
    auto avail_channel = Mix_GroupAvailable(-1);
    Mix_PlayChannel(avail_channel, this->audioChunks.at(audio).get(), playcount);
}
void Audio::PlayMusic(Audio::Music music, int playcount) {
    Mix_PlayMusic(this->musicChunks.at(music).get(), playcount);
}
void Audio::StopMusic() {
    Mix_HaltMusic();
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
    const auto device          = SDL_GetAudioDeviceName(0, 0);
    const auto deviceName      = std::string{device};
    const auto channelCount    = 24;
    SDL_AudioSpec desiredSpecs = {};
    desiredSpecs.freq          = 48000;     // 48kHz
    desiredSpecs.format        = AUDIO_F32; // arbitrary choice
    desiredSpecs.channels      = 2;         // stereo
    desiredSpecs.samples       = 2048;      // arbitrary choice
    // see https://wiki.libsdl.org/SDL_AudioSpec#Remarks
    SDL_AudioSpec receivedSpecs = {};
    SDL_OpenAudioDevice(device, 0, &desiredSpecs, &receivedSpecs, 0);
    Mix_AllocateChannels(channelCount);
    std::cout << "Audio device: " << deviceName << std::endl
              << "Frequency: " << receivedSpecs.freq << std::endl
              << "Channels: " << receivedSpecs.channels << std::endl
              << "Samples: " << receivedSpecs.samples << std::endl;
}
Audio::Audio() {}
Audio::~Audio() {
    SDL_CloseAudioDevice(this->deviceId);
}
