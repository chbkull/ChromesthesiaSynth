#pragma once
#include "ofMain.h"
#include <vector>
class DataExtracter
{
public:
	enum PixelData {NonePD, Red, Green, Blue, Lightness, Hue, Saturation, Brightness};
	enum PixelOrder {NonePO, LR, TB, Random};

	static std::vector<float> Extract(ofImage image, PixelData data, PixelOrder order);

private:
	static std::vector<float> LeftRightOrder(std::vector<std::vector<float>> data);
	static std::vector<float> TopBottomOrder(std::vector<std::vector<float>> data);
	static std::vector<float> RandomOrder(std::vector<std::vector<float>> data);
	static std::vector<vector<float>> Upscale(std::vector<std::vector<float>> data, int size);
};

