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

void TextureManager::loadSingleAsset(int index)
{
    int file_num = 0;

    for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
    {
        if (index == file_num)
        {
            std::ostringstream fileNumStream;
            fileNumStream << std::setw(3) << std::setfill('0') << file_num;
            std::string file_num_str = fileNumStream.str();

            String assetName = "tile" + file_num_str + ".png";
            this->instantiateAsTexture(STREAMING_PATH + assetName, assetName, true);
            std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
            break;
        }

        file_num++;
    }
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
    return 0;
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