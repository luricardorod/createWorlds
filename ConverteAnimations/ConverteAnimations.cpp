// ConverteAnimations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct Frame {
	struct Size
	{
		int w;
		int h;
	};
	struct Position
	{
		int x;
		int y;
	};
	struct PositionAndSize {
		Position position;
		Size size;
	};
	PositionAndSize m_framePositionAndSize;
	PositionAndSize m_spriteSourceSize;

	bool m_bRotated;
	bool m_bTrimmed;
	Size m_SourceSize;
};

struct Animation {
	char m_name[30];
	std::vector<Frame> m_frames;
};


char *file2string(const char *path, long& size) {
	FILE *fd;
	long len;
	char *str;
	if (fopen_s(&fd, path, "r")) {
		fprintf(stderr, "Can't open file '%s'\n", path);
		return NULL;
	}
	fseek(fd, 0, SEEK_END);
	len = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	str = (char*)malloc((len + 1) * sizeof(char));
	(size) = fread(str, sizeof(char), len, fd);
	str[(size)] = '\0';
	fclose(fd);
	return str;
}

void main() {
	std::vector<Animation> animations;
	std::string fileName = "samuri.json";
	char *file;
	long sizeFile;
	std::cout << "nombre del archivo? ";
	std::getline(std::cin, fileName);
	file = file2string(fileName.c_str(), sizeFile);

	std::cout << "nombre del archivo? ";

	int positionBuffer = 0;
	char buffer[50];
	int counter = 0;
	while (file[counter] != '\n')
	{
		buffer[positionBuffer] = file[counter];
		positionBuffer++;
		counter++;
	}
	buffer[positionBuffer] = '\0';
	int lolo = std::strcmp(buffer, "{\"frames\": {\n");
	if (std::strcmp(buffer, "{\"frames\": {") == 0)
	{
		bool flagReadFile = true;
		Animation tempAnimation;
		while (flagReadFile)
		{
			while (file[counter] != '"')
			{
				counter++;
			}
			positionBuffer = 0;
			counter++;
			while (file[counter] != '"')
			{
				buffer[positionBuffer] = file[counter];
				positionBuffer++;
				counter++;
			}

			if (std::strcmp(buffer, "meta") == 0)
			{
				flagReadFile = false;
			}
			else
			{
				buffer[positionBuffer - 4] = '\0';

				if (std::strcmp(tempAnimation.m_name, buffer) != 0)
				{
					if (tempAnimation.m_frames.size() > 0)
					{
						animations.push_back(tempAnimation);
						tempAnimation.m_frames.clear();
					}
					strncpy_s(tempAnimation.m_name, buffer, positionBuffer - 4);
				}
				Frame tempFrame;
				counter += 3;
				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;
				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_framePositionAndSize.position.x = atoi(buffer);
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_framePositionAndSize.position.y = atoi(buffer);
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_framePositionAndSize.size.w = atoi(buffer);
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != '}')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_framePositionAndSize.size.h = atoi(buffer);
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter += 2;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				if (std::strcmp(buffer, "true") == 0)
				{
					tempFrame.m_bRotated = true;
				}
				else
				{
					tempFrame.m_bRotated = false;
				}

				while (file[counter] != ':')
				{
					counter++;
				}
				counter += 2;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				if (std::strcmp(buffer, "true") == 0)
				{
					tempFrame.m_bTrimmed = true;
				}
				else
				{
					tempFrame.m_bTrimmed = false;
				}
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;
				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_spriteSourceSize.position.x = atoi(buffer);
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_spriteSourceSize.position.y = atoi(buffer);
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_spriteSourceSize.size.w = atoi(buffer);
				counter++;

				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != '}')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_spriteSourceSize.size.h = atoi(buffer);


				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;
				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;

				positionBuffer = 0;
				while (file[counter] != ',')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_SourceSize.w = atoi(buffer);
				counter++;
				while (file[counter] != ':')
				{
					counter++;
				}
				counter++;
				positionBuffer = 0;
				while (file[counter] != '}')
				{
					buffer[positionBuffer] = file[counter];
					positionBuffer++;
					counter++;
				}
				buffer[positionBuffer] = '\0';
				tempFrame.m_SourceSize.h = atoi(buffer);

				tempAnimation.m_frames.push_back(tempFrame);
			}
			counter++;
		}

		std::ofstream output_file(fileName + ".data", std::ifstream::binary);
		output_file.write((char*)&animations, sizeof(animations));
		output_file.close();


		for (int i = 0; i < animations.size(); i++)
		{
			std::cout << animations[i].m_name << std::endl;
		}

	}
	else
	{
		std::cout << "Archivo invalido";
	}
	std::cout << "terminar ";
	std::getline(std::cin, fileName);
}