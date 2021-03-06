#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	no_atlas_tex = App->tex->Load("Homework/logonscreen.png");

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (uint i = 0; i < UIelementsList.count(); i++)
	{
		delete UIelementsList[i];
		UIelementsList[i] = nullptr;
	}

	App->tex->UnLoad(no_atlas_tex);

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

//const getter for other tex
SDL_Texture* j1Gui::GetNoAtlas()
{
	return no_atlas_tex;
}

// class Gui ---------------------------------------------------

//---------------------------------------------Constructors-----------------------------------------
UI_Elem::UI_Elem(iPoint position, UI_Elem_type type) : position(position), type(type) {}
NO_Interactuable::NO_Interactuable(iPoint position, UI_Elem_type type) : UI_Elem(position, type) {}
Image::Image(iPoint position, UI_Elem_type type, SDL_Rect rect) : NO_Interactuable(position, type), Image_Rect(rect) {}
Text::Text(iPoint position, UI_Elem_type type,char* string_text, TTF_Font* text_font) : NO_Interactuable(position, type), string(string_text), text_font(text_font){}
NoAtlasImage::NoAtlasImage(iPoint position, UI_Elem_type type, SDL_Texture* texture, SDL_Rect rect) : NO_Interactuable(position,type), texture(texture), rect(rect) {}
Interactuable::Interactuable(iPoint position, UI_Elem_type type, SDL_Rect rect) : UI_Elem(position, type), rect(rect) {}
Button::Button(iPoint position, UI_Elem_type type, SDL_Rect rect) : Interactuable(position, type, rect) {}

//---------------------------------------------Updates--------------------------------------------
bool UI_Elem::Update() { return true; }
bool NO_Interactuable::Update() { return true; }
bool Image::Update()
{
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), this->position.x, this->position.y, &this->Image_Rect);
	return true;
}
bool Text::Update()
{
	App->render->Blit(App->font->Print(this->string, { 255,0,0,255 }, this->text_font), this->position.x, this->position.y);
	return true;
}
bool NoAtlasImage::Update()
{
	App->render->Blit(this->texture, this->position.x, this->position.y, &this->rect);
	return true;
}
bool Interactuable::Update() { return true; }
bool Button::Update()
{ 
	App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), this->position.x, this->position.y, &this->rect);
	CheckMouse(this->rect,this->position);
	return true; 
}

//---------------------------------------------Destructors-------------------------------------------
UI_Elem::~UI_Elem() {}
NO_Interactuable::~NO_Interactuable() {}
Image::~Image() {}
Text::~Text() {}
NoAtlasImage::~NoAtlasImage() {}
Interactuable::~Interactuable() {}
Button::~Button() {}

//-------------------------------------------Factory Methods------------------------------------------
UI_Elem* j1Gui::CreateImage(iPoint position, UI_Elem_type type, SDL_Rect ImageRect)
{
	UI_Elem* elemImage = nullptr;

	elemImage = new Image(position, type,ImageRect);
	
	UIelementsList.add(elemImage);
	return elemImage;
}
UI_Elem* j1Gui::CreateText(iPoint position, UI_Elem_type type, char* string_text, TTF_Font* text_font)
{
	UI_Elem* elemText = nullptr;

	elemText = new Text(position, type,string_text,(text_font) ? text_font : App->font->default);

	UIelementsList.add(elemText);
	return elemText;
}
UI_Elem* j1Gui::CreateNoAtlasImage(iPoint position, UI_Elem_type type, SDL_Texture* texture, SDL_Rect rect)
{
	UI_Elem* noAtlasElem = nullptr;

	noAtlasElem = new NoAtlasImage(position, type, texture, rect);
	
	UIelementsList.add(noAtlasElem);

	return noAtlasElem;
}
UI_Elem* j1Gui::CreateButton(iPoint position, UI_Elem_type type, SDL_Rect ButtonRect) 
{
	UI_Elem* elemButton = nullptr;

	elemButton = new Button(position, type, ButtonRect);

	UIelementsList.add(elemButton);
	return elemButton;
}


//Buttons----------------------------------------------------------------------------------------------
EVENT Interactuable::CheckMouse(const SDL_Rect button_rect, const iPoint position)
{
	EVENT res = MOUSE_LEAVE;

	int m_x, m_y;
	App->input->GetMousePosition(m_x, m_y);

	if (m_x < position.x+button_rect.w && m_x > position.x &&
		m_y < position.y+button_rect.h && m_y > position.y)
	{
		res = MOUSE_ENTER;
		//test--------
		App->render->Blit(App->gui->GetAtlas(), 200, 200);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			res = MOUSE_LEFT_CLICK;

		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			res = MOUSE_RIGHT_CLICK;
		}
	}
	else
	{
		res = MOUSE_LEAVE;
	}

	return res;
}


