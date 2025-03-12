#pragma once
#include "IETThread.h"

class ThreadPool;
class GenericMonitor;

class LevelLoader : public IETThread
{
public:
	LevelLoader();
	~LevelLoader();

private:
	std::string LEVEL_ASSET_PATH = "";
	ThreadPool* threadPool = nullptr;
	GenericMonitor* textureMonitor = nullptr;
	
	// Inherited via IETThread
	void run() override;
};

