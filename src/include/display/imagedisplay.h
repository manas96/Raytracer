#pragma once			   
#define OLC_PGE_APPLICATION
#include <olcPixelGameEngine.h>


class ImageDisplay : public olc::PixelGameEngine {

public:
	int w, h;
	std::vector<uint8_t>* imageBuffer;
	ImageDisplay(int width, int height, std::vector<uint8_t>* buff)
	{
		sAppName = "Raytracer display";
		w = width;
		h = height;
		imageBuffer = buff;
	}

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int j = h - 1; j >= 0; j--)
			for (int i = 0; i < w; i++) {
				int base = 3 * (j * w + i);
				int r = imageBuffer->at(base + 0);
				int g = imageBuffer->at(base + 1);
				int b = imageBuffer->at(base + 2);
				// PGE's origin is top left
				Draw( i, h - j, olc::Pixel(r, g, b));
			}
		return true;
	}

	void startDisplay() {
		if (Construct(w, h, 1, 1))
			Start();
		else
			std::cerr << "Error initializing display.\n";
	}

};