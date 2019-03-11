#include <Windows.h>
#include <string>

#include "Bot.h"
#include "Random.h"

using std::cin;
void main()
{


	Engine engine;
	//engine.rules();
	engine.initGame();
	engine.loop();

}