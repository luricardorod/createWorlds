#include "functionsRandom.h"

float floatRandom()
{
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

int RandomBetween(int minValue, int maxValue)
{
	return rand() % (maxValue - minValue + 1) + minValue;
}

int BasicRandom() {
	static int randomSeed = 1223345;
	static int randomSeedM = 67890;
	static int randomSeedA = 102023;
	static int randomSeedC = 84756;

	randomSeed = (randomSeedA * randomSeed + randomSeedC) % randomSeedM;
	return randomSeed;

}

float BoxMuller(float m, float s)
{
	float x1, x2, w, y1;
	static float y2;

	static int use_last = 0;

	if (use_last)
	{
		y1 = y2;
		//Reutilizar el otro valor
		use_last = 0;
	}
	else
	{
		do
		{
			x1 = 2.0 * floatRandom() - 1.0;
			x2 = 2.0 * floatRandom() - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = sqrt((-2.0 * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return(m + y1 * s);
}


template <class Type>
Type& Clamp(Type& x, Type& min, Type& max)
{
	return (x < min) ? min : ((max < x) ? max : x);
}