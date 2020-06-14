#include "Object.h"
#include "event.h"
#include "menu.h"

void display_load(game_t* game, menu_t* menu, gui::IGUIFont* font, std::vector <std::string> ListSave)
{
	game->driver->draw2DImage(menu->default_button, core::position2d<s32>(600, 150),
		core::rect<s32>(0, 0, 700, 50), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->default_button, core::position2d<s32>(600, 350),
		core::rect<s32>(0, 0, 700, 50), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->default_button, core::position2d<s32>(600, 550),
		core::rect<s32>(0, 0, 700, 50), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->default_button, core::position2d<s32>(600, 750),
		core::rect<s32>(0, 0, 700, 50), 0,
		video::SColor(255, 255, 255, 255), true);
	game->driver->draw2DImage(menu->arrow, core::position2d<s32>(300, 200 * menu->choice - 120),
		core::rect<s32>(0, 0, 338, 256), 0,
		video::SColor(255, 255, 255, 255), true);
	for (int i = 0 + 4 * menu->lateral_choice; i < 4 + 4 * menu->lateral_choice && i < ListSave.size(); i++) {
		font->draw(ListSave.at(i).c_str(), core::rect<s32>(800, 160 + i * 200 - 4 * 200 * menu->lateral_choice, 900, 800), video::SColor(255, 255, 255, 255));
	}
}

int load_menu(game_t* game, menu_t* menu, f32 frameDeltaTime, MyEventReceiver receiver, data_t* data)
{
	static f32 time = 0;
	static gui::IGUIFont* font = game->device->getGUIEnvironment()->getBuiltInFont();
	font->setKerningHeight(100);
	std::vector <std::string> ListSave = open_save_data_base(game, data);

	time += frameDeltaTime;
	display_load(game, menu, font, ListSave);
	if (receiver.IsKeyDown(irr::KEY_RETURN)) {
		if (menu->choice == 1) {
			save_menu(game, menu, data);
			game->load = true;
		}
		else if (menu->choice == 2) {
		}
		else if (menu->choice == 3) {
			save_menu(game, menu, data);
			game->load = true;
			//menu->is_rotating = true;
		}
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
	if (receiver.IsKeyDown(irr::KEY_LEFT) && menu->lateral_choice > 0 && time > 0.2) {
		time = 0;
		menu->lateral_choice--;
	}
	if (receiver.IsKeyDown(irr::KEY_RIGHT) && menu->lateral_choice < ListSave.size() / 4 - 1 && time > 0.2) {
		time = 0;
		menu->lateral_choice++;
	}
	return (0);
}