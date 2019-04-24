#pragma once
#include "ofMain.h"
#include <vector>
class DataExtracter
{
public:
	enum PixelData {Red, Green, Blue, Lightness, Hue, Saturation, Brightness};
	enum PixelOrder {LR, TB, Random, Scaling};
	DataExtracter();
	~DataExtracter();

	static std::vector<std::vector<float>> Extract(ofImage image, PixelData data, PixelOrder order);
};

