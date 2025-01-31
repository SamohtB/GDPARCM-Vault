#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <filesystem>

#include "SFML/Graphics.hpp"

typedef std::string String;
typedef std::vector<sf::Texture*> TextureList;
typedef std::unordered_map<String, TextureList> TextureTable;
class TextureManager
{
public:
	static TextureManager* getInstance();
	static void initialize();
	static void destroy();

	void loadFromAssetList(); 
	void loadSingleAsset(int index);

	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	TextureTable m_texture_map;
	TextureList m_base_texture_list;
	TextureList m_streaming_texture_list;

	const std::string STREAMING_PATH = "Media/Streaming/";
	int streamingAssetCount = 0;

	void instantiateAsTexture(String path, String assetName, bool isStreaming);
};