#include "Object.h"
#include "event.h"
#include "menu.h"

void init_pause(game_t* game, pause_t* pause)
{
	pause->choice = 1;
	pause->resume_button = game->driver->getTexture("../media/resume_button.png");
	pause->quit_button = game->driver->getTexture("../media/quit_button.png");
	pause->save_button = game->driver->getTexture("../media/save_button.png");
	pause->arrow = game->driver->getTexture("../media/arrow.png");
}

void display_pause(game_t *game, pause_t *pause)
{
	game->driver->draw2DImage(pause->resume_button, core::position2d<s32>(800, 150),
		core::rect<s32>(0, 0, 554, 107), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(pause->save_button, core::position2d<s32>(800, 350),
		core::rect<s32>(0, 0, 373, 107), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(pause->quit_button, core::position2d<s32>(800, 550),
		core::rect<s32>(0, 0, 311, 110), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(pause->arrow, core::position2d<s32>(300, 200 * pause->choice - 120),
		core::rect<s32>(0, 0, 338, 256), 0,
		video::SColor(255, 255, 255, 255), true);
}

int play_pause(game_t* game, pause_t* pause, const f32 frameDeltaTime, MyEventReceiver receiver, menu_t *menu)
{
	static f32 time = 0;

	time += frameDeltaTime;
	display_pause(game, pause);
	if (receiver.IsKeyDown(irr::KEY_RETURN)) {
		if (pause->choice == 1) {
			menu->pause = false;
			return (0);
		}
		else if (pause->choice == 2) {
		}
		else if (pause->choice == 3) {
			return (1);
		};
	}
	if (receiver.IsKeyDown(irr::KEY_UP) && pause->choice > 1 && time > 0.2) {
		time = 0;
		pause->choice--;
	}
	if (receiver.IsKeyDown(irr::KEY_DOWN) && pause->choice < 3 && time > 0.2) {
		time = 0;
		pause->choice++;
	}
	return (0);
}