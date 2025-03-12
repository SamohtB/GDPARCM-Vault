#include "StreamAssetLoader.h"
#include <iostream>
#include <random>

#include "IETThread.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"
#include "GenericMonitor.h"
#include "TextureManager.h"

StreamAssetLoader::StreamAssetLoader(String path, GenericMonitor* monitor)
{
	this->path = path;
	this->monitor = monitor;
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
		return;
	}

	this->monitor->tryEnter();
	TextureManager::getInstance()->storeTexture(texture);
	this->monitor->reportExit();
}
