#pragma once
#include "IETThread.h"
#include "RTImage.h"
#include "Hittable.h"
#include "color.h"
#include "ray.h"
#include "Camera.h"

class RayTraceThread : public IETThread
{
public:
	RayTraceThread(const Hittable& world, Camera* camera, int row_start, 
		int row_end, int column_count, int samples_per_pixel, int depth);
	~RayTraceThread();

	void run() override;
	bool isRunning();

	void writeImage();
	cv::Mat getImageData();
	int getRowStart();
	int getRowEnd();

private:
	bool m_is_running = false;

	int m_row_start = 0;
	int m_row_end = 0;
	int m_column_count = 0;
	int m_depth = 0;
	int m_samples_per_pixel = 0;

	Camera* m_camera = nullptr;
	const Hittable& m_world;
	RTImage* m_output_image = nullptr;
};

