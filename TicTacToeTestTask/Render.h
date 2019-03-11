#pragma once

#include "Engine.h"
#include <Windows.h>

class Render
{
public:
	static void clearCmd();
	static void renderField(Cell**_gField);
};

