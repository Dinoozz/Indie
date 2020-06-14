
typedef struct
{
	int choice;
	bool in_game;
	bool is_rotating;
	bool pause;
	bool in_load_menu;
	int lateral_choice;
	video::ITexture* quit_button;
	video::ITexture* play_1_button;
	video::ITexture* play_2_button;
	video::ITexture* help_button;
	video::ITexture* load_button;
	video::ITexture* arrow;
	video::ITexture* default_button;
} menu_t;

typedef struct
{
	int choice;
	video::ITexture* resume_button;
	video::ITexture* save_button;
	video::ITexture* quit_button;
	video::ITexture* arrow;
} pause_t;

void init_menu(game_t* game, menu_t* menu, data_t* data);
void display_menu(game_t* game, menu_t* menu, const f32 translation);
int main_menu(game_t* game, menu_t* menu, const f32 frameDeltaTime, MyEventReceiver receiver, data_t* data);
void menu_camera_rotate(game_t* game, menu_t* menu, const f32 frameDeltaTime, ICameraSceneNode* camera);
std::vector <std::string> open_save_data_base(game_t *game, data_t *data);
int play_pause(game_t* game, pause_t* pause, const f32 frameDeltaTime, MyEventReceiver receiver, menu_t* menu);
void init_pause(game_t* game, pause_t* pause);
void save_menu(game_t* game, menu_t* menu, data_t* data);
int load_menu(game_t* game, menu_t* menu, f32 frameDeltaTime, MyEventReceiver receiver, data_t* data);
