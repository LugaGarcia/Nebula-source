//! Audio Class Defined. Src
#include "Audio.hpp"
#include "ResourceManager.hpp"

#include <iostream>


Audio::Audio(std::string filepath) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        std::cout << "Audio library not working: " << Mix_GetError() << std::endl;
    }

    //! Load our wav file || move to resourcemanager
    m_chunk = ResourceManager::instance().GetSound(filepath);
}

Audio::~Audio() {
}

void Audio::PlaySound() {
    if (m_chunk != nullptr) {
        Mix_PlayChannel(-1, m_chunk, 0);
    }
}

void Audio::StopSound() {
    if (m_chunk != nullptr) {
        Mix_HaltChannel(-1);
    }
}
