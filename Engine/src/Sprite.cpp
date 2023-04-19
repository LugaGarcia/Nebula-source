//! Sprite Class defined. Src
#include "Sprite.hpp"
#include "ResourceManager.hpp"
#include <iostream>


//! Constructor for our sprite class
Sprite::Sprite(SDL_Renderer* renderer, int x, int y, std::string image_filename, int w, int h){
	spr_w = w;
	spr_h = h;
    mXPosition = x;
    mYPosition = y;
    //! Texture data on the GPU that we keep track of
    mTexture = ResourceManager::instance().GetTexture(renderer, image_filename);
    SDL_Point size;
    SDL_QueryTexture(mTexture, NULL, NULL, &size.x, &size.y);
	//! get num of frames and anims.
	num_frames = size.x / spr_w;
	num_anims = size.y / spr_h;
	mAngle = 0.0;
}

Sprite::~Sprite(){
	
}

//! Copy Constructor

//! NOTE: This only does a 'shallow' copy, in order to
//!       to do a true copy, we need to allocate a new texture
//!       and assign it to mTexture.
Sprite::Sprite(const Sprite& rhs)
{
    std::cout << "Copy Construtor called\n";
    mXPosition      = rhs.mXPosition;
    mYPosition      = rhs.mYPosition;
    mCurrentFrame   = rhs.mCurrentFrame;
    mTexture        = rhs.mTexture;
    mSrc            = rhs.mSrc;
    mDest           = rhs.mDest;
	mAngle			= rhs.mAngle;
}


//! Update the current frame we are on
void Sprite::Update(int x, int y, int frame, int anim, double angle){
	mXPosition = x;
    mYPosition = y;
	mAngle = angle;

	mCurrentFrame = frame % num_frames;
	mCurrentAnim = anim % num_anims;

	//! Here I am selecting which frame I want to draw
	//! from our sprite sheet. Think of this as just
	//! using a mouse to draw a rectangle around the
	//! sprite that we want to draw.
	mSrc.x = mCurrentFrame*spr_w;
	mSrc.y = mCurrentAnim*spr_h;
	mSrc.w = spr_w;
	mSrc.h = spr_h;

	//! Where we want the rectangle to be rendered at.
	//! This is an actual 'quad' that will draw our
	//! source image on top of.	
	mDest.x = mXPosition; 
	mDest.y = mYPosition;
	mDest.w = spr_w;
	mDest.h = spr_h;
}

//! Render our sprite as its position(mDest) and
//! using our texture mTexture,
//! mSrc represents the portion of the mTexture that
//! we want to draw onto our mDest.
void Sprite::Render(SDL_Renderer* renderer){
    SDL_RenderCopyEx(renderer, mTexture, &mSrc, &mDest, mAngle, NULL, SDL_FLIP_NONE);
}
