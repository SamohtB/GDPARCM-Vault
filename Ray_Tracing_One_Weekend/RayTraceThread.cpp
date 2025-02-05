#include "RayTraceThread.h"

RayTraceThread::RayTraceThread(const Hittable& world, Camera* camera, int row_start, int row_end, 
	int column_count, int samples_per_pixel, int depth) : IETThread(),
	m_camera(camera), m_world(world), m_row_start(row_start), m_row_end(row_end), m_column_count(column_count),
	m_samples_per_pixel(samples_per_pixel), m_depth(depth) 
{
	this->m_output_image = new RTImage(column_count, column_count);
}

RayTraceThread::~RayTraceThread() {}

void RayTraceThread::run()
{
	this->m_is_running = true;

	for (int y = m_row_start; y < m_row_end; y++)
	{
		for (int x = 0; x < m_column_count; x++)
		{
			Color pixel_color = Color(0.f, 0.f, 0.f);
			for (int sample = 0; sample < m_samples_per_pixel; sample++)
			{
				Ray r = this->m_camera->getRay(x, y);
				pixel_color += this->m_camera->rayColor(r, m_depth, m_world);
			}

			this->m_output_image->setPixel(x, y, pixel_color.x(), pixel_color.y(), pixel_color.z(), m_samples_per_pixel);
		}
	}

	this->m_is_running = false;
}

bool RayTraceThread::isRunning()
{
	return this->m_is_running;
}

void RayTraceThread::writeImage()
{
	cv::String file_name = "_Image_Render.png";
	this->m_output_image->saveImage(file_name);
}

cv::Mat RayTraceThread::getImageData()
{
	return this->m_output_image->getPixels();
}

int RayTraceThread::getRowStart()
{
	return this->m_row_start;
}

int RayTraceThread::getRowEnd()
{
	return this->m_row_end;
}
