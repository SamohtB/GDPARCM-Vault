#include "RTImage.h"
#include "Interval.h"
#include <mutex>

RTImage::RTImage(const int image_width, const int image_height) : m_image_width(image_width), m_image_height(image_height)
{
	this->m_pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(m_image_height, m_image_width, CV_8UC3));
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samples_per_pixel)
{
	float scale = 1.f / samples_per_pixel;

	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);

	static const Interval intensity(0.000f, 0.999f);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	cv::Mat img_channels[3];
	cv::split(*this->m_pixels, img_channels);

	img_channels[0].at<uchar>(y, x) = bbyte;
	img_channels[1].at<uchar>(y, x) = gbyte;
	img_channels[2].at<uchar>(y, x) = rbyte;

	cv::merge(img_channels, 3, *this->m_pixels);
}

void RTImage::saveImage(cv::String& file_name) const
{
	cv::imwrite(file_name, *this->m_pixels);
}

cv::Mat RTImage::getPixels() const
{
	return this->m_pixels->clone();
}
