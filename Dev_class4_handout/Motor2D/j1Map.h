#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------

struct TileSet
{
	unsigned int firstgid = 0, tilewidht = 0, tileheight = 0, spacing = 0, margin = 0;
	char* name=nullptr;

};


// TODO 1: Create a struct needed to hold the information to Map node

enum ORIENTATION {
	default,
	orthogonal,
	isometric,
	staggered,
	hexagonal,
	MAX_ORIENTATION
};

enum RENDERORDER
{
	rightdown,
	rightup,
	leftdown,
	leftup,
	MAX_RENDERORDER
};

struct Map
{
	float version = 0;
	unsigned int width, height = 0, tilewidth = 0, tileheight = 0, nextobjectid = 0;
	RENDERORDER renderorder = rightdown;
	ORIENTATION orientation = default;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:

	//LoadMap
	void LoadMapInfo();

	//LoadATileset
	void LoadTileset();

public:

	// TODO 1: Add your struct for map info as public for now

	Map mymap;
	TileSet mytileset;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;

	pugi::xml_node mynode;

	pugi::xml_node TileSetNode;


};

#endif // __j1MAP_H__