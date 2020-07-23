#pragma once
#include <string>

class GameConstants {

	public:

		// png paths
		inline static const std::string BACKGROUND_PATH = "graphics/background-1280-720.png";
		inline static const std::string TREE_PATH = "graphics/tree2.png";
		inline static const std::string CLOUD_PATH = "graphics/cloud.png";
		inline static const std::string BEE_PATH = "graphics/bee.png";
		inline static const std::string PLAYER_PATH = "graphics/player.png";
		inline static const std::string BRANCH_PATH = "graphics/branch.png";
		inline static const std::string AXE_PATH = "graphics/axe.png";
		inline static const std::string RIPSTONE_PATH = "graphics/rip.png";
		inline static const std::string LOG_PATH = "graphics/log.png";
		inline static const std::string FONT_FAMILY = "fonts/PressStart2P.ttf";

		// Game messages
		inline static const std::string GREETINGS = "Press enter to start game...";
		inline static const std::string GAME_OVER_TIME_OVER = "You ran out of times!";
		inline static const std::string GAME_OVER_SQUISHED = "Ooh! Squished";

		// Game video size
		inline static const int VIDEO_HEIGHT= 720;
		inline static const int VIDEO_WIDTH = 1280;

		// Game Title
		inline static const std::string TITLE = "Timber";

		// Game config
		inline static const enum class DIRECTION {LEFT, RIGHT, NONE};
		inline static const int NUMBER_OF_CLOUDS = 3;
		inline static const int NUMBER_OF_BRANCHES = 4;

		// Sound path
		inline static const std::string CHOP_SOUND = "sounds/chop.wav";
		inline static const std::string DEATH_SOUND = "sounds/death.wav";
		inline static const std::string OUT_OF_TIME_SOUND = "sounds/out_of_time.wav";
};
