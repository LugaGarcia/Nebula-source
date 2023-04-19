//! GameObject Header. Overview
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
//!
//! The purpose of this file is to create a game object
//! that would represent game objects in our game
//!

#include <string>
#include "Sprite.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
namespace py = pybind11;


//! Create a new Game Object
class GameObject{
public:
    //! Constructor
    GameObject(const std::string &name, 
				int _x, int _y, 
				std::string image_filename, 
				int _spr_w, int _spr_h, int _spr_x, int spr_y,
				const std::function<void(void)> &f,
				int bbox_x, int bbox_y, int bbox_w, int bbox_h,
				py::object &_obj);
    //! Setter
    void SetName(const std::string &name_);
    //! Getter
    const std::string &GetName() const;
	
    //!
    //! This function will load a script file
    //! that is written in python and evaluate it.
    //! We are going to use it to load some of
    //! the functions in this library
    //!
    void ExecuteScript(std::string pythonScriptFile); 
	int x;
	int y;
	py::object obj;
	
	//! Collision
	int bbox_x_pos;
	int bbox_y_pos;
	int bbox_x_off;
	int bbox_y_off;
	int bbox_w;
	int bbox_h;
	
	//! Sprite
	Sprite* spr;
	int spr_w;
	int spr_h;
	int spr_x;
	int spr_y;
	float spr_frame;
	float spr_anim;
	double spr_rotation;
	
	std::string image_filename;
		
	//! index in global gameobject vector
	unsigned int index;
	//! update function
	std::function<void(void)> update;

private:
    //! Name of our game object
    std::string name;
    //!
    //! Keep track of how many game objects
    //! we have.
    //!
    static unsigned int m_uniqid;
};


#endif
