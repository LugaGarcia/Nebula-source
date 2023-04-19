//! Basic Funcuinality with SDL HEADER
#ifndef SDLGRAPHICSPROGRAM_HPP
#define SDLGRAPHICSPROGRAM_HPP

//! ==================== Libraries ==================
//! Depending on the operating system we use
//! The paths to SDL are actually different.
//! The #define statement should be passed in
//! when compiling using the -D argument.
//! This gives an example of how a programmer
//! may support multiple platforms with different
//! dependencies.
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else //! This works for Mac
    #include <SDL.h>
#endif

//! The glad library helps setup OpenGL extensions.
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

//! Include the pybindings
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

//! Purpose:
//! This class sets up a full graphics program using SDL
//
//
//
class SDLGraphicsProgram{
public:

    //! Constructor
    SDLGraphicsProgram(int w, int h);
    //! Destructor
    ~SDLGraphicsProgram();
    //! Setup OpenGL
    bool initGL();
    //! Clears the screen
    void clear();
    //! Flips to new buffer
    void flip();
    //! Delay rendering
    void delay(int milliseconds);
    //! loop that runs forever
    bool loop();
    //! Get Pointer to Window
    SDL_Window* getSDLWindow();
	//! Get Pointer to Renderer
    SDL_Renderer* GetSDLRenderer();

    //! Draw a simple rectangle
    void DrawRectangle(int x, int y, int w, int h, int r, int g, int b);
	//! Set the tilemap
	void SetTilemap(std::string tiles_sprite, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, const std::vector<int> &l);
	int GetTilemapAtPixel(float x, float y);
	//! add an instantiated gameobject to the game scene.
	void AddObject(GameObject* obj);
	//! remove gameobject from scene and destroy it.
	void RemoveObject(GameObject* obj);
	//! remove all gameobjects from the scene except this one
	void RemoveAllObjects(GameObject* obj);

	//! check for a collision with an instance of a specific object
	//! returns the collided object if found
    py::object* InstancePlace(GameObject* obj, std::string obj_name);

    void PlaySound(std::string sound_filename);
    void StopSound(std::string sound_filename);

	bool keyUp;
	bool keyDown;
	bool keyLeft;
	bool keyRight;

    bool keySpace;

    bool keyW;
	bool keyA;
	bool keyS;
	bool keyD;
	bool viewBBs;
	
	int map_x_scroll;
	int map_y_scroll;

private:
	//! Objects in our game
	std::vector<GameObject*> m_gameobjects;
    std::unordered_map<std::string, Audio*> m_gamesounds;
	//! Only one tilemap can be loaded at a time
	TileMap* m_tilemap;
    //! Screen dimension constants
    int screenHeight;
    int screenWidth;
    //! The window we'll be rendering to
    SDL_Window* gWindow ;
    // Our renderer
    SDL_Renderer* gRenderer;
};








#endif
