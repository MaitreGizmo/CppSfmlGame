#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include <SFML/Graphics.hpp>

namespace gst {

	static const bool        SHOW_DEBUG = true;
	static const unsigned    WINDOW_WIDTH = 1600;
	static const unsigned    WINDOW_HEIGHT = 800;
	static const std::string WINDOW_TITLE = "CPP_SFML";
	static const sf::Color   WINDOW_BACK_COLOR(150, 150, 150);
	static const std::string MAP_FILE_LOCATION = "map_1.bmp";
	static const float       WORLD_BLOC_SIZE = 20.0f;
	static const float       PLAYER_SIZE = 20.0f;
	static const unsigned    TIME_PER_FRAME = 10; // diff time [ms] between two computations
	static const float       GRAVITY = 0.75f;
	static const float       SPEED_LEFT_RIGHT = 2.5f;
	static const float       JUMP_STRENGTH = 10.0f;

	enum class WorldBlocType {
		BACKGROUND = 0,
		FLOOR
	};
}

#endif //SETTINGS_H
