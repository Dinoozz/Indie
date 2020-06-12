
typedef struct
{
	int choice;
	bool in_game;
	bool is_rotating;
	video::ITexture* quit_button;
	video::ITexture* play_button;
	video::ITexture* help_button;
	video::ITexture* arrow;
} menu_t;

void init_menu(game_t* game, menu_t* menu);
void display_menu(game_t* game, menu_t* menu);
int main_menu(game_t* game, menu_t* menu, const f32 frameDeltaTime, MyEventReceiver receiver);
void menu_camera_rotate(game_t* game, menu_t* menu, const f32 frameDeltaTime, ICameraSceneNode* camera);
