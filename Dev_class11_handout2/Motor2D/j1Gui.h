#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum UI_Elem_type
{
	DEFAULT_TYPE,
	TEXT,
	IMAGE,
	MAX_TYPES
};

class UI_Elem 
{
public:
	iPoint position;
	UI_Elem_type type;
public:
	UI_Elem(iPoint position, UI_Elem_type type);
	virtual bool Update();
	virtual ~UI_Elem();
};

class NO_Interactuable:public UI_Elem
{
public:
	NO_Interactuable(iPoint position, UI_Elem_type type);
	virtual bool Update();
	virtual ~NO_Interactuable();
};

class Image :public NO_Interactuable
{
public:
	SDL_Rect Image_Rect;
public:
	Image(iPoint position, UI_Elem_type type);
	virtual bool Update();
	virtual ~Image();
};

class Text :public NO_Interactuable
{
public:
	_TTF_Font* text_font;
	char* string;
public:
	Text(iPoint position, UI_Elem_type type);
	virtual bool Update();
	virtual ~Text();
};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	UI_Elem* CreateImage(iPoint position, UI_Elem_type type, SDL_Rect ImageRect);
	UI_Elem* CreateText(iPoint position, UI_Elem_type type, char* string_text,  _TTF_Font text_font);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__