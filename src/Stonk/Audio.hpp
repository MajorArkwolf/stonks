#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

namespace Stonk {
    /**
     * @brief Audio manager for the Stonk engine
     */
    class Audio {
      public:
        /**
         * @brief Sound type
         */
        typedef size_t Sound;
        /**
         * @brief Music type
         */
        typedef size_t Music;
        /**
         * @brief Play a sound. 0 playcount to loop
         * @return The channel the audio is playing on
         */
        auto PlaySound(Sound audio, int playcount = 1) -> int;
        /**
         * @brief Play music. 0 playcount to loop
         */
        void PlayMusic(Music music, int playcount = 1);
        /**
         * @brief Stop music
         */
        void StopMusic();
        /**
         * @brief Stop sound on a certain channel
         */
        void StopSound(int channel);
        /**
         * @brief Load sound of filename
         * @return Sound ID
         */
        auto LoadSound(std::string filename) -> Sound;
        /**
         * @brief Load music of filename
         * @return Music ID
         */
        auto LoadMusic(std::string filename) -> Music;
        /**
         * @brief Init. Call this after Stonk's engine is loaded.
         */
        void Init();
        /**
         * @brief Destructor
         */
        ~Audio();

      private:
        /**
         * @brief Loaded audio, for SDL_Mixer
         */
        typedef std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> Chunk;
        /**
         * @brief Loaded music, for SDL_Mixer
         */
        typedef std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> MusicChunk;

        /**
         * @brief Mapping of filename to audio id. prevents loading the same sound multiple times.
         */
        std::map<std::string, Sound> loadedSounds = {};
        /**
         * @brief Mapping of filename to music id. prevents loading the same music multiple times.
         */
        std::map<std::string, Music> loadedMusic = {};
        /**
         * @brief Storage for loaded sounds
         */
        std::vector<Chunk> audioChunks = {};
        /**
         * @brief Storage for loaded music
         */
        std::vector<MusicChunk> musicChunks = {};
    };
}
