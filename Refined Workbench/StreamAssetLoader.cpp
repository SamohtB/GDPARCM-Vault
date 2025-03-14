#include "StreamAssetLoader.h"
#include <iostream>
#include <random>

#include "IETThread.h"
#include "TextureManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->execEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader() {}

void StreamAssetLoader::onStartTask()
{
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(1000, 4000);
	IETThread::sleep(dist(engine));

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	this->execEvent->onFinishedExecution();
	//delete after being done
	delete this;
}
