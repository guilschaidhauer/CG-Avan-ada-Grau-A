#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
#include "Structures.h"

using namespace std;

class Image
{
public:
	Image();
	~Image();

	void SaveImage(string fileName, int w, int h, int dpi, RGBType *data);

	int w;
	int h;
	int dpi;
};

