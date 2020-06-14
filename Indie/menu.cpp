#include "Object.h"
#include "event.h"
#include "menu.h"

void init_menu(game_t *game, menu_t *menu, data_t *data)
{
	menu->quit_button = game->driver->getTexture("../media/quit_button.png");
	menu->play_1_button = game->driver->getTexture("../media/1_player_button.png");
	menu->play_2_button = game->driver->getTexture("../media/2_player_button.png");
	menu->load_button = game->driver->getTexture("../media/load_game.png");
	menu->arrow = game->driver->getTexture("../media/arrow.png");
	menu->choice = 1;
	menu->in_game = false;
	menu->is_rotating = 0;
}

void save_menu(game_t* game, menu_t* menu, data_t* data)
{
	std::vector <std::string> ListSave = open_save_data_base(game, data);

}

void display_menu(game_t *game, menu_t *menu, const f32 translation)
{
	game->driver->draw2DImage(menu->play_1_button, core::position2d<s32>(800, 150 - translation),
		core::rect<s32>(0, 0, 594, 107), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->play_2_button, core::position2d<s32>(800, 350 - translation),
		core::rect<s32>(0, 0, 651, 107), 0,
		video::SColor(255, 255, 255, 255), true); 
	game->driver->draw2DImage(menu->load_button, core::position2d<s32>(800, 550 - translation),
			core::rect<s32>(0, 0, 750, 107), 0,
			video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->quit_button, core::position2d<s32>(800, 750 - translation),
		core::rect<s32>(0, 0, 311, 110), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->arrow, core::position2d<s32>(300, 200 * menu->choice - translation - 120),
		core::rect<s32>(0, 0, 338, 256), 0,
		video::SColor(255, 255, 255, 255), true);
}

void menu_camera_rotate(game_t* game, menu_t* menu, const f32 frameDeltaTime, ICameraSceneNode* camera)
{
	static f32 target = 0.5;
	target += 0.5;
	camera->setTarget(camera->getTarget() - vector3df(0, 20.f * frameDeltaTime, 0));
	if (camera->getTarget().Y <= -10) {
		menu->is_rotating = 0;
		menu->in_game = 1;
	}
	display_menu(game, menu, target);
}

int main_menu(game_t *game, menu_t *menu, const f32 frameDeltaTime, MyEventReceiver receiver, data_t *data)
{
	static f32 time = 0;

	time += frameDeltaTime;
	display_menu(game, menu, 0);
	if (receiver.IsKeyDown(irr::KEY_RETURN)) {
		if (menu->choice == 1) {
			menu->is_rotating = true;
			game->nb_player = 1;
		}
		else if (menu->choice == 2) {
			menu->is_rotating = true;
			game->nb_player = 2;
		}
		else if (menu->choice == 3)
			save_menu(game, menu, data);
			//menu->is_rotating = true;
		else if (menu->choice == 4) {
			return (1);
		}
	}
	if (receiver.IsKeyDown(irr::KEY_UP) && menu->choice > 1 && time > 0.2) {
		time = 0;
		menu->choice--;
	}
	if (receiver.IsKeyDown(irr::KEY_DOWN) && menu->choice < 4 && time > 0.2) {
		time = 0;
		menu->choice++;
	}
	return (0);
}