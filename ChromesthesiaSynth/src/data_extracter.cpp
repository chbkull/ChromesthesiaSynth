#include "data_extracter.h"

std::vector<float> DataExtracter::LeftRightOrder(std::vector<std::vector<float>> data) {
	std::vector<float> ordered_data;
	for (int y = 0; y < data[0].size(); y++) {
		for (int x = 0; x < data.size(); x++) {
			ordered_data.push_back(data[x][y]);
		}
	}
	return ordered_data;
}

std::vector<float> DataExtracter::TopBottomOrder(std::vector<std::vector<float>> data) {
	std::vector<float> ordered_data;
	for (int x = 0; x < data.size(); x++) {
		for (int y = 0; y < data[x].size(); y++) {
			ordered_data.push_back(data[x][y]);
		}
	}
	return ordered_data;
}

std::vector<float> DataExtracter::RandomOrder(std::vector<std::vector<float>> data) {
	std::vector<float> ordered_data;
	for (int x = 0; x < data.size(); x++) {
		for (int y = 0; y < data[x].size(); y++) {
			ordered_data.push_back(data[x][y]);
		}
	}

	std::vector<float> randomized;
	for (int i = ordered_data.size(); i > 0; i--) {
		int rand_int = rand() % i;
		randomized.push_back(ordered_data[rand_int]);
		swap(ordered_data[rand_int], ordered_data.back());
		ordered_data.pop_back();
	}
	return randomized;
}

std::vector<vector<float>> DataExtracter::Upscale(std::vector<std::vector<float>> data, int size) {
	std::vector<std::vector<float>> totals(pow(size, 2), vector<float>());
	std::vector<std::vector<float>> upscaled(size, vector<float>());
	int horizontal_divider = ceil((double) data.size() / (double) size);
	int vertical_divider = ceil((double) data[0].size() / (double) size);

	cout << "entered upscale" << endl;

	for (int x = 0; x < data.size(); x++) {
		//cout << "x: " << x << endl;
		for (int y = 0; y < data[x].size(); y++) {
			//cout << "y: " << y << endl;
			int index = (x / horizontal_divider) + size * (y / vertical_divider);
			//cout << "index: " << index << endl;
			totals[index].push_back(data[x][y]);
		}
	}

	cout << "first loop done" << endl;

	std::vector<float> averaged;
	int x = 0;
	int y = 0;
	for (int i = 0; i < totals.size(); i++) {
		int sum = 0;
		for (int j = 0; j < totals[i].size(); j++) {
			sum += totals[i][j];
		}
		
		upscaled[x].push_back(sum / totals[i].size());
		y++;
		if (y >= size) {
			x++;
			y = 0;
		}
	}
	
	return upscaled;
}

std::vector<float> DataExtracter::Extract(ofImage image, PixelData p_data, PixelOrder p_order) {
	std::vector<std::vector<float>> filtered_data(image.getWidth(), std::vector<float>(image.getHeight()));

	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); y++) {
			switch (p_data) {
			case PixelData::Red:
				filtered_data[x][y] = image.getColor(x, y).r;
				break;
			case PixelData::Green:
				filtered_data[x][y] = image.getColor(x, y).g;
				break;
			case PixelData::Blue:
				filtered_data[x][y] = image.getColor(x, y).b;
				break;
			case PixelData::Lightness:
				filtered_data[x][y] = image.getColor(x, y).getLightness();
				break;
			case PixelData::Hue:
				filtered_data[x][y] = image.getColor(x, y).getHue();
				break;
			case PixelData::Saturation:
				filtered_data[x][y] = image.getColor(x, y).getSaturation();
				break;
			case PixelData::Brightness:
				filtered_data[x][y] = image.getColor(x, y).getBrightness();
				break;
			}
		}
	}

	switch (p_order) {
	case PixelOrder::LR:
		return LeftRightOrder(Upscale(filtered_data, 4));
	case PixelOrder::TB:
		return TopBottomOrder(Upscale(filtered_data, 4));
	case PixelOrder::Random:
		return RandomOrder(Upscale(filtered_data, 4));
	}
}
