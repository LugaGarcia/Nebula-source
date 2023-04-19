//! The ResourceManager class in src
#include "ResourceManager.hpp"
#include <iterator>
#include <iostream>

ResourceManager::ResourceManager(){
}

ResourceManager& ResourceManager::instance() {
	static ResourceManager *instance = new ResourceManager();
	return *instance;
}

void ResourceManager::LoadSurface(std::string image_filename) {
	if (mSurfaces.count(image_filename))
		return;
    //! std::cout << "New surface of " << image_filename << " has been loaded\n";
	SDL_Surface* surface = SDL_LoadBMP(image_filename.c_str());
	//red is our transparent color.
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 0));
	if(surface == nullptr)
        std::cerr << image_filename << " not found!\n";
    //! else
    //!    std::cout << "SDL_LoadBMP allocated\n";
	mSurfaces.insert({image_filename, surface});
}

void ResourceManager::LoadTexture(SDL_Renderer* renderer, std::string image_filename) {
	if (mTextures.count(image_filename))
		return;
	//! std::cout << "New texture of " << image_filename << " has been loaded\n";
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, GetSurface(image_filename));
    if(texture == nullptr)
        std::cerr << "Error creating texture\n";
    //!else
    //!    std::cout << "SDL_Texture allocated\n";
   	mTextures.insert({image_filename, texture});
}

void ResourceManager::DestroySurface(std::string image_filename) {
	SDL_FreeSurface(mSurfaces[image_filename]);
	mSurfaces.erase(image_filename);
}

void ResourceManager::DestroyTexture(std::string image_filename) {
	SDL_DestroyTexture(mTextures[image_filename]);
	mTextures.erase(image_filename);
}

SDL_Surface* ResourceManager::GetSurface(std::string image_filename) {
	if (!mSurfaces.count(image_filename))
		LoadSurface(image_filename);
    //! std::cout << "Retrieved saved copy of " << image_filename << " from GetSurface\n";
    return mSurfaces[image_filename];
}

SDL_Texture* ResourceManager::GetTexture(SDL_Renderer* renderer, std::string image_filename) {
	if (!mTextures.count(image_filename))
		LoadTexture(renderer, image_filename);
    //! std::cout << "Retrieved saved copy of " << image_filename << " from GetTexture\n";
    return mTextures[image_filename];
}

void ResourceManager::LoadSound(std::string sound_filename) {
	if (mSounds.count(sound_filename)) 
		return;

	Mix_Chunk *chunk = Mix_LoadWAV(sound_filename.c_str());
    if (chunk == nullptr) {
        std::cout << "Could not load audio file: " << sound_filename << std::endl;
    }
	else {
		mSounds.insert({sound_filename, chunk});
	}
}

void ResourceManager::DestroySound(std::string sound_filename) {
	Mix_FreeChunk(mSounds[sound_filename]);
	mSounds.erase(sound_filename);
}

Mix_Chunk *ResourceManager::GetSound(std::string sound_filename) {
	if (!mSounds.count(sound_filename))
		LoadSound(sound_filename);

	return mSounds[sound_filename];
}
