#pragma once
#include "IETThread.h"
#include "IExecutionEvent.h"

class ThreadPool;
class GenericMonitor;
class LevelLoaderMonitor;

class LevelLoader : public IETThread
{
public:
	LevelLoader(IExecutionEvent* executionEvent);
	~LevelLoader();

	float getProgress() const;

private:
	std::string LEVEL_ASSET_PATH = "Media/UniformCard/";
	ThreadPool* threadPool = nullptr;
	GenericMonitor* textureMonitor = nullptr;
	LevelLoaderMonitor* levelLoaderMonitor = nullptr;
	IExecutionEvent* executionEvent = nullptr;

	// Inherited via IETThread
	void run() override;
};

