#include "LevelLoader.h"

#include <filesystem>
#include "ThreadPool.h"
#include "StreamAssetLoader.h"
#include "GenericMonitor.h"
#include "TextureManager.h"

LevelLoader::LevelLoader()
{
	this->threadPool = new ThreadPool("Texture Pool", 16);
    this->textureMonitor = new GenericMonitor();
}

LevelLoader::~LevelLoader()
{
	delete this->threadPool;
    delete this->textureMonitor;
}

void LevelLoader::run()
{
	this->threadPool->startScheduler();

    /* schedule assets */
    for (const auto& entry : std::filesystem::directory_iterator(LEVEL_ASSET_PATH))
    {
        auto path = entry.path().generic_string();
        StreamAssetLoader* assetLoader = new StreamAssetLoader(path, this->textureMonitor);
        this->threadPool->scheduleTask(assetLoader);
    }

    /* add wait for all threads to finish */


}
