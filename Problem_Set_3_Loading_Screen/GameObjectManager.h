#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

#include "AGameObject.h"

typedef std::vector<AGameObject*> GameObjectList;
typedef std::unordered_map<String, AGameObject*> GameObjectTable;

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
    void addGameObjectBehind(AGameObject* game_object);
    void addUIObject(AGameObject* game_object);
    void deleteObject(AGameObject* game_object);
    void deleteObjectByName(String name);
    void clearAllObjects();

    AGameObject* findObjectByName(String name);
    GameObjectList getAllObjects();

private:
    GameObjectManager() = default;
    GameObjectManager(GameObjectManager const&) {}
    GameObjectManager& operator=(GameObjectManager const&) {}

    static GameObjectManager* sharedInstance;

    GameObjectList m_object_list;
    GameObjectList m_ui_objects;
    GameObjectTable m_object_table;
};