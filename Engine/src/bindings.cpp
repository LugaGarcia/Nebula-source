//! Connects CPP code to python with PyBind11
#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

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
#include "ResourceManager.hpp"
#include "Sprite.hpp"
#include "Audio.hpp"
#include "GameObject.hpp"
#include "TileMap.hpp"
#include "SDLGraphicsProgram.hpp"

//! Purpose:
//! This class sets up a full graphics program using SDL

//! Initialization function
//! Returns a true or false value based on successful completion of setup.
//! Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):screenWidth(w),screenHeight(h){
	//! Initialization flag
	bool success = true;
	//! String to hold any errors that occur.
	std::stringstream errorStream;
	//! The window we'll be rendering to
	gWindow = NULL;

	keyUp = false;
	keyDown = false;
	keyLeft = false;
	keyRight = false;
	keySpace = false;
	keyW = false;
	keyA = false;
	keyS = false;
	keyD = false;
	map_x_scroll = 0;
	map_y_scroll = 0;

	//! Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
	    //! Create window
    	gWindow = SDL_CreateWindow( "Game", 0, 0, screenWidth*4, screenHeight*4, SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( gWindow == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//!Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetScale(gRenderer, 2, 2);
        //! Check if Renderer did not create.
        if( gRenderer == NULL ){
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }
  	}

    
    
    //! If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

}


//! Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    	//! Destroy window
	SDL_DestroyWindow( gWindow );
	//! Point gWindow to NULL to ensure it points to nothing.
	gWindow = NULL;
	//! Quit SDL subsystems
	SDL_Quit();
}


//! Initialize OpenGL
//! Setup any of our shaders here.
bool SDLGraphicsProgram::initGL(){
	//! Success flag
	bool success = true;

	return success;
}


//! clear
//! Clears the screen
void SDLGraphicsProgram::clear(){
	// Nothing yet!
    SDL_SetRenderDrawColor(gRenderer, 0x44,0x44,0x4,0xFF);
    SDL_RenderClear(gRenderer);   
}
//! Flip
//! The flip function gets called once per loop
//! It swaps out the previvous frame in a double-buffering system
void SDLGraphicsProgram::flip(){	
	for (int i = 0; i < m_gameobjects.size(); i++) {
		GameObject* o = m_gameobjects[i];
		if (o != NULL) {
			if (o->update != NULL)
				o->update();
			if (o->spr != NULL)
				o->spr->Update(o->x + o->spr_x -map_x_scroll, o->y + o->spr_y - map_y_scroll, (int)o->spr_frame, (int)o->spr_anim, (double)o->spr_rotation);
			o->bbox_x_pos = o->x + o->bbox_x_off;
			o->bbox_y_pos = o->y + o->bbox_y_off;
		}	
	}
	
	if (m_tilemap != NULL) {
		m_tilemap->Render(GetSDLRenderer(), map_x_scroll, map_y_scroll);
	}
	
	for (int i = 0; i < m_gameobjects.size(); i++) {
		GameObject* o = m_gameobjects[i];
		if (o != NULL) {
			if (o->spr != NULL)
				o->spr->Render(GetSDLRenderer());
			if (viewBBs) {
				DrawRectangle(o->x -map_x_scroll, o->y -map_y_scroll, 1, 1, 0x00, 0x00, 0xFF);
				DrawRectangle(o->bbox_x_pos -map_x_scroll, o->bbox_y_pos -map_y_scroll, o->bbox_w, o->bbox_h, 0xFF, 0x00, 0x00);
			}
		}
	}
    SDL_RenderPresent(gRenderer);
}


void SDLGraphicsProgram::delay(int milliseconds){
    SDL_Delay(milliseconds); 
}

//! Loops forever
bool SDLGraphicsProgram::loop(){
    //! Main loop flag
    //! If this is quit = 'true' then the program terminates.
    bool quit = false;
    //! Event handler that handles various events in SDL
    //! that are related to input and output
    SDL_Event e;
    //! Enable text input
    SDL_StartTextInput();
    //! While application is running
    //! while(!quit){
     	 //! Handle events on queue
		while(SDL_PollEvent( &e ) != 0){
        	//! User posts an event to quit
	        //! An example is hitting the "x" in the corner of the window.
    	    if(e.type == SDL_QUIT){
        		quit = true;
	        }
			if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym){
					case SDLK_UP:
						keyUp = 1;
						break;
					case SDLK_DOWN:
						keyDown = 1;
						break;
					case SDLK_LEFT:
						keyLeft = 1;
						break;
					case SDLK_RIGHT:
						keyRight = 1;
						break;
					case SDLK_SPACE:
						keySpace = 1;
						break;
					case SDLK_w:
						keyW = 1;
						break;
					case SDLK_a:
						keyA = 1;
						break;
					case SDLK_s:
						keyS = 1;
						break;
					case SDLK_d:
						keyD = 1;
						break;
				}
			}
			if (e.type == SDL_KEYUP) {
				switch(e.key.keysym.sym){
					case SDLK_UP:
						keyUp = 0;
						break;
					case SDLK_DOWN:
						keyDown = 0;
						break;
					case SDLK_LEFT:
						keyLeft = 0;
						break;
					case SDLK_RIGHT:
						keyRight = 0;
						break;
					case SDLK_SPACE:
						keySpace = 0;
						break;
					case SDLK_w:
						keyW = 0;
						break;
					case SDLK_a:
						keyA = 0;
						break;
					case SDLK_s:
						keyS = 0;
						break;
					case SDLK_d:
						keyD = 0;
						break;
				}
			}
      	} //! End SDL_PollEvent loop.

      	//! Update screen of our specified window
      	SDL_GL_SwapWindow(getSDLWindow());
    //}
	
    //! Disable text input
    SDL_StopTextInput();
	return quit;
}


//!  Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
  return gWindow;
}

//! Get Pointer to a specific SDLRenderer
SDL_Renderer* SDLGraphicsProgram::GetSDLRenderer(){
  return gRenderer;
}

//! Okay, render our rectangles!
void SDLGraphicsProgram::DrawRectangle(int x, int y, int w, int h, int r, int g, int b){
    SDL_Rect fillRect = {x,y,w,h};
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);
    SDL_RenderDrawRect(gRenderer, &fillRect); 
}

void SDLGraphicsProgram::AddObject(GameObject* obj) {
	//! add sprite when obj added to scene.
	if (!obj->image_filename.empty()) {
		obj->spr = new Sprite(GetSDLRenderer(),
								obj->x + obj->spr_x,
								obj->y + obj->spr_y,
								obj->image_filename,
								obj->spr_w,
								obj->spr_h);
	}

	obj->index = m_gameobjects.size();
	m_gameobjects.push_back(obj);
}

void SDLGraphicsProgram::RemoveObject(GameObject* obj) {
	//! remove from gameobjects array
	m_gameobjects.erase(m_gameobjects.begin() + obj->index);
	int i = 0;
	for (GameObject* o : m_gameobjects) {
		o->index = i;
		i++;
	}
}

void SDLGraphicsProgram::RemoveAllObjects(GameObject* obj) {
	m_gameobjects.clear();
	obj->index = m_gameobjects.size();
	m_gameobjects.push_back(obj);

}

bool check_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    if ((x1 < x2 + w2) && (x1 + w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2))
		return true;
	return false;
}

py::object* SDLGraphicsProgram::InstancePlace(GameObject* obj, std::string obj_name) {
	
	for (GameObject* o : m_gameobjects) {
		if (o->GetName() == obj_name) {
			if (check_collision(obj->bbox_x_pos, obj->bbox_y_pos, obj->bbox_w, obj->bbox_h, o->bbox_x_pos, o->bbox_y_pos, o->bbox_w, o->bbox_h))
				return &o->obj;
		}
	}
	return nullptr;
}

void SDLGraphicsProgram::PlaySound(std::string sound_filename) {
	if (!m_gamesounds.count(sound_filename)) {
		Audio *sound = new Audio(sound_filename);
		m_gamesounds.insert({sound_filename, sound});
	}
	m_gamesounds[sound_filename]->PlaySound();
}

void SDLGraphicsProgram::StopSound(std::string sound_filename) {
	if (!m_gamesounds.count(sound_filename)) {
		return;
	}

	m_gamesounds[sound_filename]->StopSound();
}


void SDLGraphicsProgram::SetTilemap(std::string tiles_sprite, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, const std::vector<int> &l) {
	int data[_mapX*_mapY] = {};
	int ind = 0;     

	for(int item : l) {
		data[ind] = int(item);
		//std::cout << data[ind] << "  ";

		ind++;
    }
	m_tilemap = new TileMap(tiles_sprite, rows, cols, _TileWidth, _TileHeight, _mapX, _mapY, data, GetSDLRenderer());
}

int SDLGraphicsProgram::GetTilemapAtPixel(float p_x, float p_y) {
	int x = int(p_x);
	int y = int(p_y);
	return m_tilemap->GetTileType(x/m_tilemap->m_TileWidth, y/m_tilemap->m_TileHeight);
}

//!
//! Creates a macro function that will be called
//! whenever the module is imported into python
//! 'mygameengine' is what we 'import' into python.
//! 'm' is the interface (creates a py::module object)
//!      for which the bindings are created.
//!  The magic here is in 'template metaprogramming'
//!
PYBIND11_MODULE(mygameengine, m){
    m.doc() = "our game engine as a library"; // Optional docstring

    py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
            .def(py::init<int,int>(), py::arg("w"), py::arg("h"))   //! our constructor
            .def("clear", &SDLGraphicsProgram::clear) //! Expose member methods
            .def("delay", &SDLGraphicsProgram::delay) 
            .def("flip", &SDLGraphicsProgram::flip) 
            .def("loop", &SDLGraphicsProgram::loop) 
            .def("draw_rectangle", &SDLGraphicsProgram::DrawRectangle)
			.def("instance_create", &SDLGraphicsProgram::AddObject)
			.def("instance_destroy", &SDLGraphicsProgram::RemoveObject)
			.def("instance_destroy_all", &SDLGraphicsProgram::RemoveAllObjects)
			.def("instance_place", &SDLGraphicsProgram::InstancePlace)
			.def("tilemap_create", &SDLGraphicsProgram::SetTilemap)
			.def("tilemap_get_at_pixel", &SDLGraphicsProgram::GetTilemapAtPixel)
			.def_readonly("key_up", &SDLGraphicsProgram::keyUp)
			.def_readonly("key_down", &SDLGraphicsProgram::keyDown)
			.def_readonly("key_left", &SDLGraphicsProgram::keyLeft)
			.def_readonly("key_right", &SDLGraphicsProgram::keyRight)
			.def_readonly("key_space", &SDLGraphicsProgram::keySpace)
			.def_readonly("key_w", &SDLGraphicsProgram::keyW)
			.def_readonly("key_a", &SDLGraphicsProgram::keyA)
			.def_readonly("key_s", &SDLGraphicsProgram::keyS)
			.def_readonly("key_d", &SDLGraphicsProgram::keyD)
			.def_readwrite("view_hitboxes", &SDLGraphicsProgram::viewBBs)
			.def_readwrite("camera_x", &SDLGraphicsProgram::map_x_scroll)
			.def_readwrite("camera_y", &SDLGraphicsProgram::map_y_scroll)
			.def("play_sound", &SDLGraphicsProgram::PlaySound)
			.def("stop_sound", &SDLGraphicsProgram::StopSound);

    py::class_<GameObject>(m, "GameObject")
            .def(py::init([](const std::string &name, int _x, int _y, std::string image_filename, int _spr_w, int _spr_h, int _spr_x, int _spr_y, const std::function<void(void)> &f, int bbox_x, int bbox_y, int bbox_w, int bbox_h, py::object &_obj) {
				return new GameObject(name, _x, _y, image_filename, _spr_w, _spr_h, _spr_x, _spr_y, f, bbox_x, bbox_y, bbox_w, bbox_h, _obj); 
			}))   //! our constructor
            .def("set_name", &GameObject::SetName)   //! Expose member methods
            .def("get_name", &GameObject::GetName)   
            .def("execute_script", &GameObject::ExecuteScript)
			.def_readwrite("x", &GameObject::x)
			.def_readwrite("y", &GameObject::y)
			.def_readwrite("rotation", &GameObject::spr_rotation)
			.def_readwrite("frame", &GameObject::spr_frame)
			.def_readwrite("anim", &GameObject::spr_anim);
//!          .def_readwrite("name",&GameObject::name);  // Expose member variables


//! We do not need to expose everything to our users!
//!            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference) 
}


#endif
