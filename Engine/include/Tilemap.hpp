//! Tilemap or "tiles" header. Overview
#ifndef TILE_H
#define TILE_H

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <string>

/**
 * This is a minimal implementation of a TileMap
 */
class TileMap{
public:
    
    /**
     * Constructor for a tilemap
     */
    TileMap(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, int* data, SDL_Renderer* ren);
    /**
     * Destructor for a tilemap
     */
    ~TileMap();
    /**
     * Temporary function for generating a simple
     * map to display some tiles
     */
    void GenerateSimpleMap();
    /**
     * Function for printing text to console
     */
    void PrintMap();
    /**
     * Set the 'type' of tile at an x and y position
     */
    void SetTile(int x, int y, int type);
    /**
     * Return the tile type at an x and y position
     */
    int GetTileType(int x, int y);
    /**
     * Draw all of the tiles in the tilemap
     */
    void Render(SDL_Renderer* ren, int x_scroll, int y_scroll);
    //! How big each tile is.
    int m_TileWidth;
    int m_TileHeight;

private:
    //!
    //! Dimensions of our TileMap and individual tiles.
    //! Used for spiltting up the sprite sheet
    //!
    int m_Rows;
    int m_Cols;      
    //! size of our tilemap
    int m_MapX;
    int m_MapY; 
    //!
    //! Where our TileMap is rendered
    //! An SDL Surface contains pixel data to draw our TileMap
    //!
    SDL_Surface *m_TileSpriteSheet;
    SDL_Texture *m_Texture;
    //! Stores our tile types
    int* m_Tiles;
};

#endif
