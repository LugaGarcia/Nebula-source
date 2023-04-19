//! Sprite Header. Overview
#ifndef SPRITE_HPP
#define SPRITE_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <string>

class Sprite{
public:
    //! Construtor -- Create a new Sprite
	Sprite(SDL_Renderer* renderer, int x, int y, std::string image_filename, int w, int h);
    //! Destructor
    ~Sprite();
    //! Copy Constructor
    Sprite(const Sprite& rhs);
    //! Move Constructor
    Sprite(Sprite&& rhs) = default;
    //! Update the Sprite
	void Update(int x, int y, int frame, int anim, double angle);
    //! Draw the Sprite
	void Render(SDL_Renderer* renderer);

private:
	int				spr_w;
	int				spr_h;
	int				num_frames;
	int				num_anims;
	int             mXPosition;
    int             mYPosition;
	unsigned int    mCurrentFrame{0};
	unsigned int	mCurrentAnim{0};
	SDL_Texture*    mTexture;
	SDL_Rect        mSrc;
	SDL_Rect        mDest;
	double 			mAngle;
};

#endif
