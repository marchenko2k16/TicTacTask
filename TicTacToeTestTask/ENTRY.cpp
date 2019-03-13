#include "Bot.h"


#include "GameDescription.h"


void main()
{
	GameDescription::chooseSide();
	GameDescription::rules();
	Engine engine;
	engine.initGame();
	while (std::cin.get())
		engine.loop();

}