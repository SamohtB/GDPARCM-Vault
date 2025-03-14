#include "StreamAssetLoader.h"
#include <iostream>

#include "IETThread.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"
#include "GenericMonitor.h"
#include "LevelLoaderMonitor.h"
#include "TextureManager.h"


std::mt19937 StreamAssetLoader::randomEngine(std::random_device{}());

StreamAssetLoader::StreamAssetLoader(String path, GenericMonitor* monitor, LevelLoaderMonitor* levelLoaderMonitor)
	: path(path), monitor(monitor), levelLoaderMonitor(levelLoaderMonitor)
{
}

StreamAssetLoader::~StreamAssetLoader() {}

void StreamAssetLoader::onStartTask()
{
	/* add random delay to loading */
	std::uniform_int_distribution<int> dist(1000, 2000);
	IETThread::sleep(dist(randomEngine));

	sf::Texture* texture = new sf::Texture(path);

	if (texture == nullptr)
	{
		std::cerr << "[TextureManager] No texture found for " << path << std::endl;
		delete texture;
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
