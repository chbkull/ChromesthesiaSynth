#include "data_extracter.h"

vector<float> DataExtracter::LeftRightOrder(vector<vector<float>> data) {
	vector<float> ordered_data;
	for (int y = 0; y < data[0].size(); y++) {
		for (int x = 0; x < data.size(); x++) {
			ordered_data.push_back(data[x][y]);
		}
	}
	return ordered_data;
}

vector<float> DataExtracter::TopBottomOrder(vector<vector<float>> data) {
	vector<float> ordered_data;
	for (int x = 0; x < data.size(); x++) {
		for (int y = 0; y < data[x].size(); y++) {
			ordered_data.push_back(data[x][y]);
		}
	}
	return ordered_data;
}

vector<float> DataExtracter::RandomOrder(vector<vector<float>> data) {
	vector<float> ordered_data;
	for (int x = 0; x < data.size(); x++) {
		for (int y = 0; y < data[x].size(); y++) {
			ordered_data.push_back(data[x][y]);
		}
	}

	vector<float> randomized;
	for (int i = ordered_data.size(); i > 0; i--) {
		int rand_int = rand() % i;
		randomized.push_back(ordered_data[rand_int]);
		swap(ordered_data[rand_int], ordered_data.back());
		ordered_data.pop_back();
	}
	return randomized;
}

vector<vector<float>> DataExtracter::Upscale(vector<vector<float>> data, int size) {
	
	vector<vector<float>> totals(pow(size, 2), vector<float>());
	vector<vector<float>> upscaled(size, vector<float>());
	int horizontal_divider = ceil((double) data.size() / (double) size);
	int vertical_divider = ceil((double) data[0].size() / (double) size);

	for (int x = 0; x < data.size(); x++) {
		for (int y = 0; y < data[x].size(); y++) {
			int index = (x / horizontal_divider) + size * (y / vertical_divider);
			totals[index].push_back(data[x][y]);
		}
	}

	vector<float> averaged;
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

vector<float> DataExtracter::Extract(ofImage image, PixelData p_data, PixelOrder p_order) {
	vector<vector<float>> filtered_data(image.getWidth(), vector<float>(image.getHeight()));
	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); y++) {
			switch (p_data) {
			case PixelData::RedPD:
				filtered_data[x][y] = image.getColor(x, y).r;
				break;
			case PixelData::GreenPD:
				filtered_data[x][y] = image.getColor(x, y).g;
				break;
			case PixelData::BluePD:
				filtered_data[x][y] = image.getColor(x, y).b;
				break;
			case PixelData::LightnessPD:
				filtered_data[x][y] = image.getColor(x, y).getLightness();
				break;
			case PixelData::HuePD:
				filtered_data[x][y] = image.getColor(x, y).getHue();
				break;
			case PixelData::SaturationPD:
				filtered_data[x][y] = image.getColor(x, y).getSaturation();
				break;
			case PixelData::BrightnessPD:
				filtered_data[x][y] = image.getColor(x, y).getBrightness();
				break;
			}
		}
	}

	

	switch (p_order) {
		case PixelOrder::LeftRightPO:
			return LeftRightOrder(Upscale(filtered_data, kUpscaleSize));
		case PixelOrder::TopBottomPO:
			return TopBottomOrder(Upscale(filtered_data, kUpscaleSize));
		case PixelOrder::RandomPO:
			return RandomOrder(Upscale(filtered_data, kUpscaleSize));
	}
}
