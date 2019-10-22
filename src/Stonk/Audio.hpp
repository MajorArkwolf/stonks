#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

namespace Stonk {
    class Audio {
      public:
        typedef size_t Sound;
        typedef size_t Music;
        auto PlaySound(Sound audio, int playcount = 1) -> int;
        void PlayMusic(Music music, int playcount = -1);
        void StopMusic();
        void StopSound(int channel);
        auto LoadSound(std::string filename) -> Sound;
        auto LoadMusic(std::string filename) -> Music;

        void Init();
        Audio();

        ~Audio();

      private:
        typedef std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> Chunk;
        typedef std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> MusicChunk;

        std::map<std::string, Sound> loadedSounds = {};
        std::map<std::string, Music> loadedMusic  = {};

        std::vector<Chunk> audioChunks      = {};
        std::vector<MusicChunk> musicChunks = {};
    };
}
