#pragma once
#include "opencv2/core.hpp"
#include <opencv2/imgcodecs.hpp>

class RTImage
{
public:
	RTImage(const int image_width, const int image_height);
	void setPixel(int x, int y, float r, float g, float b, int samples_per_pixel);
	void saveImage(cv::String& file_name) const;

private:
	std::unique_ptr<cv::Mat> m_pixels;
	int m_image_width;
	int m_image_height;
};

