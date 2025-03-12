#include "StreamAssetLoader.h"
#include <iostream>
#include <random>

#include "IETThread.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"
#include "GenericMonitor.h"
#include "LevelLoaderMonitor.h"
#include "TextureManager.h"

StreamAssetLoader::StreamAssetLoader(String path, GenericMonitor* monitor, LevelLoaderMonitor* levelLoaderMonitor)
	: path(path), monitor(monitor), levelLoaderMonitor(levelLoaderMonitor)
{
}

StreamAssetLoader::~StreamAssetLoader() {}

void StreamAssetLoader::onStartTask()
{
	/* add random delay to loading */
	// move random device outside
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(1000, 4000);
	IETThread::sleep(dist(engine));

	sf::Texture* texture = new sf::Texture(path);

	if (texture == nullptr)
	{
		std::cerr << "[TextureManager] No texture found for " << path << std::endl;
	}
	else /* Dont add if texture load fail */
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

		this->monitor->tryEnter();
		std::cout << assetName << " Stored" << std::endl;
		TextureManager::getInstance()->storeTexture(assetName, texture);
		this->monitor->reportExit();
	}

	this->levelLoaderMonitor->reportExit();
}
