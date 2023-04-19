## DOCUMENTATION for Nebula

Thank you for being interested in Nebula Game Engine.

This page, along with the hyperlinks on the side to the left and top will show you all the classes and source code for our engine. 

Below is a guide on how to use the Nebula:

	Controls for the game:

		W or UP_ARROW	: Move forward
        
		A or LEFT_ARROW	: Turn left
        
		D or RIGHT_ARROW	: Turn right
        
		SPACE			: Shoot

		If you press both A and LEFT_ARROW at the same time, you will turn 2x as fast
		The same applies for D and RIGHT_ARROW. This is by design for the game we built


	For creating a new level:

		Creating a new level map:
			1. Download the free Tiled software
			2. In the upper-left corner, click File -> New -> New Map
			3. In the menu that pops up, keep everything under "Map" as their default values, then, set up the map dimensions under "Map Size" and the tile dimensions under "Tile Size"
				NOTE: For adding a new level to our game, the map is 32x32 tiles, and each tile is 32x32 pixels
			4. Now go to File -> New -> New Tileset. Here you can select a new tileset that you can use to create your map. This should be a bitmap file (.bmp) that contains tiles of the same size as what your map is expecting (for our game, those tiles would be 32x32 pixels)
			5. Name your Tileset, then click "Save As", and save it somewhere you will be able to retrieve it from easily
			6. Go to "Tilesets" in the bottom right of the window and click the down arrow that's right beneath the x button for said window. It should have an option for Importing an External Tileset. Click that and then retrieve the tileset you made
			7. You should now see all of the tiles from your tileset in the bottom right corner, you can then select and place those tiles anywhere within the map.
			8. Once you are finished creating the map, save the file as a .tmj in the project folder

		Loading a newly created level map:
			1. To load a level map into your game, simply use the python command: load_room('the name of your .tsg file', "the path to the bitmap of your tileset")
				For example:	load_room('level_1', "assets/sprites/tilesets/space_tileset_1.bmp")
				NOTE: When calling load_room, the name of your .tsg file SHOULD NOT include the .tsg itself

		Adding the player:
			You do not need to add the player to any level except the first one, as this game plays as a rogue-like where the levels change around one singular player character.

		To add the player to the first level:
			1. Go into Tiled and open the map that you wish to add the player to
			2. On the right side of the screen, under layers, right-click -> New -> Object Layer. This is where all players and enemies should be added
			3. Now press R and click somewhere on the map to add a rectangle. Name it "Player" or whatever your player class is called, and if there are any special properties you wish to set for this object you can add a special property with the name of whatever field you wish to set
			4. Save your .tsg

		To add enemies to a level:
			1. This is the exact same process as adding a player to the first level, except that you name the newly created rectangle "Enemy", or whatever your enemy class is named.
			2. For special properties, we used:
				hp 			- int		- how many hits the enemy can take
				ang_off		- float	- how much an enemy will rotate every tick
				bullet_spawn_time	- float	- how quickly the enemy fires
				radius		- int		- how far in a circle the enemy goes
			3. Save your .tsg



## Game/Engine Publicity

**Project Website**: https://lugagarcia.github.io/NebulaGameEngine/

## Compilation Instructions

Run `python3 build.py` 

This Engine was built for Linux and will only run on Linux. 

This can be found in /Engine/, as that is out /bin/ 

## Project Hieararchy

In the future, other engineers may take on our project, so we have to keep it organized given the following requirements below. Forming some good organization habits now will help us later on when our project grows as well. These are the required files you should have 

### ./Engine Directory Organization
- Inside /Engine/ (our Bin)
    - This is the directory where our  executable resides(for Linux) and any additional generated files are put after each 
- Docs 
    - Source Code Documentation
- Assets
    - Art assets (With the Sub directories music, sound, images, and anything else)
- src
    - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
    - header files(.h and .hpp files)
 
