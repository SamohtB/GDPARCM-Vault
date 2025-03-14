#include "TextureManager.h"

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
    loadFromAssetList();
}

void TextureManager::loadFromAssetList()
{
    std::ifstream stream("Media/assets.txt");
    String path;

    while (std::getline(stream, path))
    {
        if (path.empty()) continue;
        std::string assetName = path.substr(path.find_last_of("/\\") + 1);
        assetName = assetName.substr(0, assetName.find_last_of("."));
        this->instantiateAsTexture(path, assetName, false);
        std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
    }
}


void TextureManager::storeTexture(String assetName, sf::Texture* texture)
{
    this->m_texture_map[assetName].push_back(texture);
    this->m_streaming_texture_list.push_back(texture);
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
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

sf::Texture* TextureManager::getStreamTextureFromList(const int index)
{
    return this->m_streaming_texture_list[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
    return this->m_streaming_texture_list.size();
}

void TextureManager::instantiateAsTexture(String path, String asset_name, bool is_streaming)
{
    sf::Texture* texture = new sf::Texture(path);

    if (texture == nullptr)
    {
        std::cerr << "[TextureManager] No texture found for " << asset_name << std::endl;
        return;
    }

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