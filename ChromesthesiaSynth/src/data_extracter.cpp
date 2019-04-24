#include "data_extracter.h"

DataExtracter::DataExtracter()
{
}


DataExtracter::~DataExtracter()
{
}

std::vector<std::vector<float>> DataExtracter::Extract(ofImage image, PixelData p_data, PixelOrder p_order) {
	std::vector<std::vector<float>> filtered_data(image.getWidth(), std::vector<float>(image.getHeight()));

	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); y++) {
			switch (p_data) {
				case Red:
					filtered_data[x][y] = image.getColor(x, y).r;
					break;
				case Green:
					filtered_data[x][y] = image.getColor(x, y).g;
					break;
				case Blue:
					filtered_data[x][y] = image.getColor(x, y).b;
					break;
				case Lightness:
					filtered_data[x][y] = image.getColor(x, y).getLightness();
					break;
				case Hue:
					filtered_data[x][y] = image.getColor(x, y).getHue();
					break;
				case Saturation:
					filtered_data[x][y] = image.getColor(x, y).getSaturation();
					break;
				case Brightness:
					filtered_data[x][y] = image.getColor(x, y).getBrightness();
					break;
			}
		}
	}

	return filtered_data;
}
