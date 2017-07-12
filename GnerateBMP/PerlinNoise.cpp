#include "PerlinNoise.h"
#include "functionsRandom.h"

float Interpolate(float x0, float x1, float alpha)
{
	return x0 * (1 - alpha) + alpha * x1;
}

void PerlinNoise::SetOctaves(float octaves)
{
	m_octaves = octaves;
}

void PerlinNoise::SetSize(float width, float heigth)
{
	m_width = width;
	m_height = heigth;
}

float PerlinNoise::GetValuePerlinNoise(int position)
{
	return m_perlinNoise[position];
}

float * PerlinNoise::GenerateWhiteNoise()
{
	float* baseNoise = new float[m_width * m_height];

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			baseNoise[y*m_width + x] = floatRandom();
		}
	}
	return baseNoise;
}

float * PerlinNoise::GenerateSmoothNoise(int octave)
{
	float* smoothNoise = new float[m_width * m_height];

	int samplePeriod = 1 << octave; // calculates 2 ^ k
	float sampleFrequency = 1.0f / samplePeriod;

	for (int i = 0; i < m_width; i++)
	{
		//calculate the horizontal sampling indices
		int sample_i0 = (i / samplePeriod) * samplePeriod;
		int sample_i1 = (sample_i0 + samplePeriod) % m_width; //wrap around
		float horizontal_blend = (i - sample_i0) * sampleFrequency;

		for (int j = 0; j < m_height; j++)
		{
			//calculate the vertical sampling indices
			int sample_j0 = (j / samplePeriod) * samplePeriod;
			int sample_j1 = (sample_j0 + samplePeriod) % m_height; //wrap around
			float vertical_blend = (j - sample_j0) * sampleFrequency;

			//blend the top two corners

			float top = Interpolate(m_baseNoise[sample_j0*m_width + sample_i0],
				m_baseNoise[sample_j0*m_width + sample_i1], horizontal_blend);

			//blend the bottom two corners
			float bottom = Interpolate(m_baseNoise[sample_j1*m_width + sample_i0],
				m_baseNoise[sample_j1*m_width + sample_i1], horizontal_blend);

			//final blend
			smoothNoise[j*m_width + i] = Interpolate(top, bottom, vertical_blend);
		}
	}
	return smoothNoise;
}

void PerlinNoise::GeneratePerlinNoise()
{
	m_baseNoise = GenerateWhiteNoise();

	float *smoothNoiseTemp;
	m_perlinNoise = new float[m_width * m_height];
	for (int i = 0; i < m_width*m_height; i++)
	{
		m_perlinNoise[i] = 0;
	}
	float persistance = .5f;
	float amplitude = 1.0f;
	float totalAmplitude = 0.0f;
	//generate smooth noise
	for (int i = 0; i < m_octaves; i++)
	{
		smoothNoiseTemp = GenerateSmoothNoise( m_octaves - i);
		amplitude *= persistance;
		totalAmplitude += amplitude;
		for (int i = 0; i < m_width*m_height; i++)
		{
			m_perlinNoise[i] += smoothNoiseTemp[i] * amplitude;
		}
		delete[] smoothNoiseTemp;
	}

	//normalisation
	for (int i = 0; i < m_width*m_height; i++)
	{
		m_perlinNoise[i] /= totalAmplitude;
	}
	delete[] m_baseNoise;
}

PerlinNoise::PerlinNoise()
{
}

PerlinNoise::~PerlinNoise()
{
	delete[] m_perlinNoise;
}
