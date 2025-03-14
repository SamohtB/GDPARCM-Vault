#include "LevelLoaderMonitor.h"

void LevelLoaderMonitor::tryEnter()
{
	std::unique_lock<std::mutex> lock(this->lock);

	while (!isComplete && assetCount > 0)
	{
		this->condition.wait(lock);
	}
}

void LevelLoaderMonitor::reportExit()
{
	std::lock_guard<std::mutex> lock(this->lock);

	this->completedCount++;
	this->assetCount--;
	
	if (assetCount == 0)
	{
		isComplete = true;
		this->condition.notify_one();
	}
}

void LevelLoaderMonitor::increment()
{
	std::lock_guard<std::mutex> lock(this->lock);
	this->assetCount++;
	isComplete = false;
}

float LevelLoaderMonitor::getProgress()
{
	std::lock_guard<std::mutex> lock(this->lock);

	if (assetCount == 0 && completedCount == 0) return 0.0f;

	return completedCount / static_cast<float>(completedCount + assetCount);
}
