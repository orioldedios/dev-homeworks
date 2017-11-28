#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class Image;
class Text;
class NoAtlasImage;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* debug_tex;
	NoAtlasImage* back;
	Image* banner;
	Text* text;

	Text* AccountName;
	Text* AccountPasword;
	Text* Login;
	Text* ManageAccount;
	Text* CommunitySite;
	Text* RememberAccountName;
	Text* Version;
	Text* DateVersion;
	Text* CopyRight;
	Text* Cinematics;
	Text* Credits;
	Text* TermsOfUse;
	Text* Quit;
	Text* wowpsorg;

	Image* manage_account_button;
	Image* community_site_button;
	Image* remember_account_name_checkbox;
	Image* esrbNotice;
	Image* account_name_input_box;
	Image* account_pasword_input_box;
	Image* login_button;
	Image* blizzard_logo;
	Image* cinematics_button;
	Image* credits_button;
	Image* terms_of_use_button;
	Image* quit_button;
	Image* wow_logo;
};

#endif // __j1SCENE_H__