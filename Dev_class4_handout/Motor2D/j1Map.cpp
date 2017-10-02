#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	
	SDL_Texture* backbround_tileset = nullptr;
	
		for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset")) {

			p2SString backg("maps/%s.png", mytileset.name);

			backbround_tileset = App->tex->Load(backg.GetString());

		App->render->Blit(backbround_tileset, 0, 0);
		num_tileset++;
	}


}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data

		LoadMapInfo();
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	LoadTileset();

	if (ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
		LOG("\nSuccessfully phrased map XML----------\nFile: %s\nwidth: %u\nheigth: %u\ntile_width: %u\ntile_heigth: %u\n", file_name, mymap.width, mymap.height, mymap.tilewidth, mymap.tileheight);

		for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset")) {
			LOG("TileSet ----- \nName: %s\nfirstgid: %u\ntile_width: %u\ntileheight: %u\nspacing: %u\nmargin: %u", mytileset.name, mytileset.firstgid, mytileset.tilewidth, mytileset.tileheight, mytileset.spacing, mytileset.margin);
		}
	}

	map_loaded = ret;

	return ret;
}

void j1Map::LoadMapInfo() {

	//pugi::xml_parse_result result = map_file.load_file("maps/elloiro.tmx");

	//assert(result);
	mynode = map_file.document_element();

		mymap.version = mynode.attribute("version").as_float();
		mymap.height= mynode.attribute("height").as_uint();
		mymap.width = mynode.attribute("width").as_uint();
		mymap.nextobjectid = mynode.attribute("nextobjectid").as_uint();
		mymap.tileheight= mynode.attribute("tileheight").as_uint();
		mymap.tilewidth = mynode.attribute("tilewidth").as_uint();


		if (strcmp(mynode.attribute("renderorder").value(), "right-down")==0)
		{
			mymap.renderorder= RENDERORDER::rightdown;
		}
		else if (strcmp(mynode.attribute("renderorder").value(), "right-up") == 0)
		{
			mymap.renderorder = RENDERORDER::rightup;
		}
		else if (strcmp(mynode.attribute("renderorder").value(), "left-down") == 0)
		{
			mymap.renderorder = RENDERORDER::leftdown;
		}
		else if (strcmp(mynode.attribute("renderorder").value(), "left-up") == 0)
		{
			mymap.renderorder = RENDERORDER::leftup;
		}
		else
		{
			LOG("ERROR LOADING RENDERORDER\n");
		}


		if (strcmp(mynode.attribute("orientation").value(), "default") == 0)
		{
			mymap.orientation = ORIENTATION::default;
		}
		else if (strcmp(mynode.attribute("orientation").value(), "orthogonal") == 0)
		{
			mymap.orientation = ORIENTATION::orthogonal;
		}
		else if (strcmp(mynode.attribute("orientation").value(), "isometric") == 0)
		{
			mymap.orientation = ORIENTATION::isometric;
		}
		else if (strcmp(mynode.attribute("orientation").value(), "staggered") == 0)
		{
			mymap.orientation = ORIENTATION::staggered;
		}
		else if (strcmp(mynode.attribute("orientation").value(), "hexagonal") == 0)
		{
			mymap.orientation = ORIENTATION::hexagonal;
		}
		else
		{
			LOG("ERROR LOADING ORIENTATION\n");
		}

}

void j1Map::LoadTileset() {

	for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset")) {

		/*pugi::xml_parse_result result = map_file.load_file("maps/elloiro.tmx");

		assert(result);*/
		//TileSetNode = map_file.document_element();

		//TileSetNode = TileSetNode.child("tileset");

		mytileset.firstgid = tileset.attribute("firstgid").as_uint();
		mytileset.margin = tileset.attribute("margin").as_uint();
		mytileset.name = (char*)tileset.attribute("name").value();
		mytileset.spacing = tileset.attribute("spacing").as_uint();
		mytileset.tileheight = tileset.attribute("tileheight").as_uint();
		mytileset.tilewidth = tileset.attribute("tilewidth").as_uint();
	}
}
