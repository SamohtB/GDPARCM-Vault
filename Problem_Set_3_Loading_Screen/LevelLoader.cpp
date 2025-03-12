#include "LevelLoader.h"

#include <filesystem>
#include "ThreadPool.h"
#include "StreamAssetLoader.h"
#include "GenericMonitor.h"
#include "LevelLoaderMonitor.h"
#include "TextureManager.h"

LevelLoader::LevelLoader(IExecutionEvent* executionEvent) : executionEvent(executionEvent)
{
	this->threadPool = new ThreadPool("Texture Pool", 16);
    this->textureMonitor = new GenericMonitor();
    this->textureMonitor->open();
    this->levelLoaderMonitor = new LevelLoaderMonitor();
}

LevelLoader::~LevelLoader()
{
	delete this->threadPool;
    delete this->textureMonitor;
    delete this->levelLoaderMonitor;
}

void LevelLoader::run()
{
	this->threadPool->startScheduler();

    int assetCount = 0;

    /* schedule assets */
    for (const auto& entry : std::filesystem::directory_iterator(LEVEL_ASSET_PATH))
    {
        auto path = entry.path().generic_string();
        this->levelLoaderMonitor->increment();
        StreamAssetLoader* assetLoader = new StreamAssetLoader(path, this->textureMonitor, this->levelLoaderMonitor);
        this->threadPool->scheduleTask(assetLoader);

        assetCount++;
    }

    if (assetCount > 0)
    {
        this->levelLoaderMonitor->tryEnter();
    }
   
    /* add what to do when loading is complete */
    this->threadPool->stopScheduler();
    this->executionEvent->onFinishedExecution();

}
