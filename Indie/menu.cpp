#include "Object.h"
#include "event.h"
#include "menu.h"

void init_menu(game_t *game, menu_t *menu)
{
	menu->quit_button = game->driver->getTexture("../media/quit_button.png");
	menu->play_button = game->driver->getTexture("../media/play_button.png");
	menu->arrow = game->driver->getTexture("../media/arrow.png");
	menu->choice = 1;
	menu->in_game = false;
	menu->is_rotating = 0;
}

void display_menu(game_t *game, menu_t *menu, const f32 translation)
{
	game->driver->draw2DImage(menu->play_button, core::position2d<s32>(800, 250 - translation),
		core::rect<s32>(0, 0, 368, 107), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->quit_button, core::position2d<s32>(800, 450 - translation),
		core::rect<s32>(0, 0, 311, 110), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->arrow, core::position2d<s32>(300, 200 * menu->choice - translation),
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

int main_menu(game_t *game, menu_t *menu, const f32 frameDeltaTime, MyEventReceiver receiver)
{
	static f32 time = 0;

	time += frameDeltaTime;
	display_menu(game, menu, 0);
	if (receiver.IsKeyDown(irr::KEY_RETURN)) {
		if (menu->choice == 1)
			menu->is_rotating = true;
		else if (menu->choice == 2) {
			return (1);
		}
	}
	if (receiver.IsKeyDown(irr::KEY_UP) && menu->choice > 1 && time > 0.2) {
		time = 0;
		menu->choice--;
	}
	if (receiver.IsKeyDown(irr::KEY_DOWN) && menu->choice < 3 && time > 0.2) {
		time = 0;
		menu->choice++;
	}
	return (0);
}