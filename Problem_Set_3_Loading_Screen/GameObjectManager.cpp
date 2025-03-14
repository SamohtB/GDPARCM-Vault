#include "GameObjectManager.h"
#include "AGameObject.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
    return sharedInstance;
}

void GameObjectManager::initialize()
{
    try
    {
        sharedInstance = new GameObjectManager();
    }
    catch (...)
    {
        std::cerr << "GameObjectManager not created successfully" << std::endl;
    }
}

void GameObjectManager::destroy()
{
    delete sharedInstance;
}

void GameObjectManager::processInput(const std::optional<sf::Event> event)
{
    for (int i = 0; i < this->m_object_list.size(); i++)
    {
        this->m_object_list[i]->processInput(event);
    }
}

void GameObjectManager::update(sf::Time delta_time)
{
    for (int i = 0; i < this->m_object_list.size(); i++)
    {
        this->m_object_list[i]->update(delta_time);
    }
}

void GameObjectManager::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < this->m_object_list.size(); i++)
    {
        this->m_object_list[i]->draw(window);
    }
}

void GameObjectManager::addGameObject(AGameObject* game_object)
{
    m_object_list.insert(m_object_list.begin(), game_object);
    m_object_table[game_object->getName()] = game_object;
}

void GameObjectManager::addGameObjectBehind(AGameObject* game_object)
{
    m_object_list.insert(m_object_list.begin(), game_object);
    m_object_table[game_object->getName()] = game_object;
}

void GameObjectManager::deleteObject(AGameObject* game_object)
{
    auto it = m_object_table.find(game_object->getName());
    if (it == m_object_table.end())
    {
        std::cerr << "Object " << game_object->getName() << " not found in table." << std::endl;
        return;
    }

    auto objIt = std::find_if(m_object_list.begin(), m_object_list.end(),
        [&](AGameObject* obj) { return obj == game_object; });

    if (objIt != m_object_list.end())
    {
        m_object_list.erase(objIt);
    }

    m_object_table.erase(it);
}

void GameObjectManager::deleteObjectByName(String name)
{
    auto it = m_object_table.find(name);
    if (it == m_object_table.end())
    {
        std::cerr << "Object " << name << " not found in table." << std::endl;
        return;
    }

    auto objIt = std::find_if(m_object_list.begin(), m_object_list.end(),
        [&](AGameObject* obj) { return obj->getName() == name; });

    if (objIt != m_object_list.end())
    {
        m_object_list.erase(objIt);
    }

    m_object_table.erase(it);
}

void GameObjectManager::clearAllObjects()
{
    this->m_object_table.clear();
    this->m_object_list.clear();
}

AGameObject* GameObjectManager::findObjectByName(String name)
{
    auto it = m_object_table.find(name);
    return (it != m_object_table.end()) ? it->second : nullptr;

    std::cerr << name << " not found" << std::endl;
}

GameObjectList GameObjectManager::getAllObjects()
{
    return this->m_object_list;
}
