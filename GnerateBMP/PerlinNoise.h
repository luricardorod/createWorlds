#pragma once
#include <functional>


class PerlinNoise
{
public:
	void GeneratePerlinNoise();
	void SetOctaves(float octaves);
	void SetSize(float width, float heigth);
	float  GetValuePerlinNoise(int);
	PerlinNoise();
	~PerlinNoise();

private:
	float m_octaves;
	int m_width;
	int m_height;

	float *m_baseNoise;
	float *m_perlinNoise;

	float* GenerateWhiteNoise();
	float* GenerateSmoothNoise(int octave);
};