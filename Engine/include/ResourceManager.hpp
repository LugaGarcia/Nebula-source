//! ResourceManager Header. Overview
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

//! I recommend a map for filling in the resource manager
#include <unordered_map>
#include <string>
#include <SDL2/SDL_mixer.h>

//! Our resource Manager

//! This resourcce manager has its solo instance
//! and is able to load a "surface", textures, sounds,
//! along with being able to destory them
class ResourceManager{
public:
	static ResourceManager& instance();
    void LoadSurface(std::string image_filename);
    void LoadTexture(SDL_Renderer* renderer, std::string image_filename);
	void DestroySurface(std::string image_filename);
	void DestroyTexture(std::string image_filename);
    SDL_Surface* GetSurface(std::string key);
	SDL_Texture* GetTexture(SDL_Renderer* renderer, std::string key);
    void LoadSound(std::string sound_filename);
    void DestroySound(std::string sound_filename);
    Mix_Chunk *GetSound(std::string key);

private:
	ResourceManager();
    ResourceManager(ResourceManager const&); //!< Avoid copy constructor
						//!<
    void operator=(ResourceManager const&); //!< Don't allow assignment.
						//!<
	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
	std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::unordered_map<std::string, Mix_Chunk *> mSounds;
};

#endif
