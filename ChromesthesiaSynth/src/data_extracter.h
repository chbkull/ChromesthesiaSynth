#pragma once
#include "ofMain.h"
#include <vector>
class DataExtracter
{
public:

	// note the loop size is UpscaleSize^2.
	static const int kUpscaleSize = 4;

	enum PixelData {NonePD, RedPD, GreenPD, BluePD, LightnessPD, HuePD, SaturationPD, BrightnessPD};
	enum PixelOrder {NonePO, LeftRightPO, TopBottomPO, RandomPO};

	// extracts the float data from an image given a data type to look for and an order to process them in
	static std::vector<float> Extract(ofImage image, PixelData data, PixelOrder order);

private:
	static std::vector<float> LeftRightOrder(std::vector<std::vector<float>> data);
	static std::vector<float> TopBottomOrder(std::vector<std::vector<float>> data);
	static std::vector<float> RandomOrder(std::vector<std::vector<float>> data);
	
	// upscales the input photo to a size * size photo
	static std::vector<vector<float>> Upscale(std::vector<std::vector<float>> data, int size);
};

