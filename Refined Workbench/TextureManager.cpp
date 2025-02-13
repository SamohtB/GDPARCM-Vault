#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"
#include "StringUtils.h"
#include "IETThread.h"
#include "StreamAssetLoader.h"
#include "IExecutionEvent.h"

TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager* TextureManager::getInstance()
{
    return sharedInstance;
}

void TextureManager::initialize()
{
    try
    {
        sharedInstance = new TextureManager();
    }
    catch (...)
    {
        std::cerr << "TextureMnager not created successfully" << std::endl;
    }
}

void TextureManager::destroy()
{
    delete sharedInstance;
}

TextureManager::TextureManager() 
{
    this->countStreamingAssets();
}

void TextureManager::loadFromAssetList()
{
    std::cout << "[TextureManager] Reading from asset list" << std::endl;
    std::ifstream stream("Media/assets.txt");
    String path;

    while (std::getline(stream, path))
    {
        std::vector<String> tokens = StringUtils::split(path, '/');
        String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
        this->instantiateAsTexture(path, assetName, false);
        std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
    }
}

void TextureManager::loadStreamingAssets()
{
    for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) 
    {
        //simulate loading of very large file
        IETThread::sleep(200);

        String path = entry.path().generic_string();
        std::vector<String> tokens = StringUtils::split(path, '/');
        String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
        this->instantiateAsTexture(path, assetName, true);

        std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
    }
}

void TextureManager::loadSingleAsset(int index, IExecutionEvent* executionEvent)
{
    int file_num = 0;

    for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
    {
        if (index == file_num)
        {
            IETThread::sleep(200.f);

            String path = entry.path().generic_string();
            StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
            assetLoader->start();

            break;
        }

        file_num++;
    }
}

TexturePtr TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
    if (!this->m_texture_map[assetName].empty()) 
    {
        return this->m_texture_map[assetName][frameIndex];
    }
    else 
    {
        std::cerr << "[TextureManager] No texture found for " << assetName << std::endl;
        return nullptr;
    }
}

int TextureManager::getNumFrames(const String assetName)
{
    if (!this->m_texture_map[assetName].empty()) 
    {
        return static_cast<int>(this->m_texture_map[assetName].size());
    }
    else 
    {
        std::cerr << "[TextureManager] No texture found for " << assetName << std::endl;
        return 0;
    }
}

TexturePtr TextureManager::getStreamTextureFromList(const int index)
{
    return this->m_streaming_texture_list[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
    return static_cast<int>(this->m_streaming_texture_list.size());
}

void TextureManager::countStreamingAssets()
{
    this->m_streaming_asset_count = 0;

    for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) 
    {
        this->m_streaming_asset_count++;
    }
    std::cout << "[TextureManager] Number of streaming assets: " << this->m_streaming_asset_count << std::endl;
}

void TextureManager::instantiateAsTexture(String path, String asset_name, bool is_streaming)
{
    TexturePtr texture = std::make_shared<sf::Texture>(path);
    this->m_texture_map[asset_name].push_back(texture);

    if (is_streaming)
    {
        this->m_streaming_texture_list.push_back(texture);
    }
    else
    {
        this->m_base_texture_list.push_back(texture);
    }
}