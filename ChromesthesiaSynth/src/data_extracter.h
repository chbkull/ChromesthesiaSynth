#pragma once
#include "ofMain.h"
#include <vector>
class DataExtracter
{
public:
	enum PixelData {Red, Green, Blue, Lightness, Hue, Saturation, Brightness};
	enum PixelOrder {LR, TB, Random, EightByEight};
	DataExtracter();
	~DataExtracter();

	static std::vector<float> Extract(ofImage image, PixelData data, PixelOrder order);

private:
	static std::vector<float> LeftRightOrder(std::vector<std::vector<float>> data);
	static std::vector<float> TopBottomOrder(std::vector<std::vector<float>> data);
	static std::vector<float> RandomOrder(std::vector<std::vector<float>> data);
	static std::vector<float> EightByEightOrder(std::vector<std::vector<float>> data);
};

