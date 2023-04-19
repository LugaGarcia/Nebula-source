//! Audio header and simplification
#ifndef AUDIO_HPP
#define AUDIO_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <string>
#include <SDL2/SDL_mixer.h>

//!
//! The Audio Class which contains virtual functions along with
//! functionality to play and stop sound
//!
class IAudio {
    public:
        virtual ~IAudio() {};

        virtual void PlaySound() = 0;
        virtual void StopSound() = 0;
};



class Audio : public IAudio {
public:
    //! Constructor
    Audio(std::string sound_filepath);
    //! Destructor
    ~Audio();
    //! Play a sound
    void PlaySound();
    //! Stop playing a sound
    void StopSound();

    private:
    //! The sound chunk we want to play
    Mix_Chunk *m_chunk;
};






#endif
