#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"

using String = std::string;
using TexturePtr = std::shared_ptr<sf::Texture>;
using TextureList = std::vector<TexturePtr>;
using TextureTable = std::unordered_map<String, TextureList>;

class IExecutionEvent;
class ThreadPool;

class TextureManager
{
public:
	static TextureManager* getInstance();
	static void initialize();
	static void destroy();

	void loadFromAssetList(); 
	void loadStreamingAssets();
	void loadSingleAsset(int index, IExecutionEvent* execution_event);

	TexturePtr getFromTextureMap(const String asset_name, int frame_index);
	int getNumFrames(const String asset_name);

	TexturePtr getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;

	void instantiateAsTexture(String path, String asset_name, bool is_streaming);

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	TextureTable m_texture_map;
	TextureList m_base_texture_list;
	TextureList m_streaming_texture_list;
	ThreadPool* m_thread_pool = nullptr;

	const std::string STREAMING_PATH = "Media/Streaming/";
	int m_streaming_asset_count = 0;

	void countStreamingAssets();
};