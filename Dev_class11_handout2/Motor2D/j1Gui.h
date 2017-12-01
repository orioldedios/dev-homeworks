#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Fonts.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
enum UI_Elem_type
{
	NO_TYPE,
	TEXT,
	IMAGE,
	BUTTON,
	NO_ATLAS_IMAGE
};

enum EVENT
{
	NO_EVENT_TYPE,
	MOUSE_ENTER,
	MOUSE_LEAVE,
	MOUSE_RIGHT_CLICK,
	MOUSE_LEFT_CLICK
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

class Interactuable :public UI_Elem
{
public:
	SDL_Rect rect;
public:
	Interactuable(iPoint position, UI_Elem_type type, SDL_Rect rect);
	virtual bool Update();
	virtual ~Interactuable();
	// Check Mouse
	EVENT CheckMouse(const SDL_Rect button_rect, const iPoint position);
};

class Button :public Interactuable
{
public:
	Button(iPoint position, UI_Elem_type type, SDL_Rect rect);
	virtual bool Update();
	virtual ~Button();
};

class Image :public NO_Interactuable
{
public:
	SDL_Rect Image_Rect;
public:
	Image(iPoint position, UI_Elem_type type, SDL_Rect rect);
	virtual bool Update();
	virtual ~Image();
};

class Text :public NO_Interactuable
{
public:
	TTF_Font* text_font=nullptr;
	char* string=nullptr;
public:
	Text(iPoint position, UI_Elem_type type,char* string_text, TTF_Font* text_font);
	virtual bool Update();
	virtual ~Text();
};

class NoAtlasImage:public NO_Interactuable
{
public:
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;
public:
	NoAtlasImage(iPoint position, UI_Elem_type type, SDL_Texture* texture, SDL_Rect rect);
	virtual bool Update();
	virtual ~NoAtlasImage();
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
	UI_Elem* CreateText(iPoint position, UI_Elem_type type, char* string_text, TTF_Font* text_font);
	UI_Elem* CreateNoAtlasImage(iPoint position, UI_Elem_type type, SDL_Texture* texture, SDL_Rect rect);
	UI_Elem* CreateButton(iPoint position, UI_Elem_type type, SDL_Rect ButtonRect);

	p2List<j1Module*> listeners;

	SDL_Texture* GetAtlas() const;
	SDL_Texture* GetNoAtlas();

private:

	SDL_Texture* atlas = nullptr;
	SDL_Texture* no_atlas_tex = nullptr;
	p2SString atlas_file_name;
	p2List<UI_Elem*> UIelementsList;
};

#endif // __j1GUI_H__