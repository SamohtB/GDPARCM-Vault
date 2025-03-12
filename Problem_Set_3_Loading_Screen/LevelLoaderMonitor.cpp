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
