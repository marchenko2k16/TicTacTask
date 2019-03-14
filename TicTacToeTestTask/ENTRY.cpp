#include "Bot.h"


#include "GameDescription.h"


void main()
{
	GameDescription::rules();
	GameDescription::chooseSide();
	Engine engine;
	engine.initGame();
	while (std::cin.get())
		engine.loop();

}