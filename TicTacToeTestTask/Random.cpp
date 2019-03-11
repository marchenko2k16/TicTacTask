#include "Random.h"

float Random::random(float from, float to)
{

	std::random_device randomDevice;
	std::mt19937_64 mt(randomDevice());
	std::uniform_real_distribution<> distribution(from, to);
	return distribution(mt);

}
