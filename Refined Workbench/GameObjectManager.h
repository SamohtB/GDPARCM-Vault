#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics.hpp>

class AGameObject;

using String = std::string;
using GameObjectList = std::vector<AGameObject*>;
using GameObjectTable = std::unordered_map<String, AGameObject*>;

class GameObjectManager
{
public:
    static GameObjectManager* getInstance();
    static void initialize();
    static void destroy();

    void processInput(const std::optional<sf::Event> event);
    void update(sf::Time delta_time);
    void draw(sf::RenderWindow* window);

    void addGameObject(AGameObject* game_object);
    void deleteObject(AGameObject* game_object);
    void deleteObjectByName(String name);
    void clearAllObjects();

    AGameObject* findObjectByName(String name);
    GameObjectList getAllObjects();

    int activeObjects();

private:
    GameObjectManager();
    GameObjectManager(GameObjectManager const&) {}
    GameObjectManager& operator=(GameObjectManager const&) {}

    static GameObjectManager* sharedInstance;

    GameObjectList m_object_list;
    GameObjectTable m_object_table;
};