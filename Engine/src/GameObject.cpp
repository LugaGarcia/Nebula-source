//! GameObject class defined. Src
#include "GameObject.hpp"

//! ========= C++ Standard Libraries ============
#include <iostream>
#include <string>
#include <fstream>

//! =========== Third Party Libraries ===========
//! Include our pybind11 library
#include <pybind11/pybind11.h>
//! Also need to include the embedded interpreter
//! for our 'ExecuteScript' command
#include <pybind11/embed.h>

//! Setup the namespace
namespace py = pybind11;


//! Create a new Game Object
GameObject::GameObject(const std::string &name, 
						int _x, int _y, 
						std::string _image_filename,
						int _spr_w, int _spr_h, int _spr_x, int _spr_y,
						const std::function<void(void)> &f, 
						int _bbox_x, int _bbox_y, int _bbox_w, int _bbox_h,
						py::object &_obj) : name(name) {
	x = _x;
	y = _y;
	bbox_x_off = _bbox_x;
	bbox_y_off = _bbox_y;
	bbox_w = _bbox_w;
	bbox_h = _bbox_h;
	bbox_x_pos = x + bbox_x_off;
	bbox_y_pos = y + bbox_y_off;
	obj = _obj;


	spr_frame = 0;
	spr_anim = 0;
	spr_rotation = 0.0;
	image_filename = _image_filename;
	spr = nullptr;
	spr_w = _spr_w;
	spr_h = _spr_h;
	spr_x = _spr_x;
	spr_y = _spr_y;
	update = f;
    m_uniqid++;
}

//! Setter
void GameObject::SetName(const std::string &name_){
    name = name_;
}
//! Getter
const std::string& GameObject::GetName() const { return name; }

//! This function will load a script file
//! that is written in python and evaluate it.
//! We are going to use it to load some of
//! the functions in this library
void GameObject::ExecuteScript(std::string pythonScriptFile){
    std::ifstream script(pythonScriptFile);
    std::string line;
    if(script.is_open()){
        //! Read each line at a time and execute
        while(std::getline(script,line)){
            py::exec(line.c_str());
        } 
        script.close();
    }
}

//! Setup any static variables
unsigned int GameObject::m_uniqid = 0;
