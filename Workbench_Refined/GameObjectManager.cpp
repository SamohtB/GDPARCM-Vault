#include "GameObjectManager.h"

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
    for (AGameObject* obj : m_object_list)
    {
        obj->processInput(event);
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
    for (AGameObject* obj : m_object_list)
    {
        obj->draw(window);
    }
}

void GameObjectManager::addGameObject(AGameObject* game_object)
{
    m_object_list.push_back(game_object);
    m_object_table[game_object->getName()] = game_object;
}

void GameObjectManager::deleteObject(AGameObject* game_object)
{
    if (this->m_object_table[game_object->getName()] != nullptr)
    {
        this->m_object_table.erase(game_object->getName());

        int index = -1;
        for (int i = 0; i < this->m_object_list.size(); i++)
        {
            if (this->m_object_list[i] == game_object)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            this->m_object_list.erase(this->m_object_list.begin() + index);
        }
        else
        {
            std::cerr << game_object->getName() << " not found and deleted" << std::endl;
        }
    }
}

void GameObjectManager::deleteObjectByName(String name)
{
    if (this->m_object_table[name] != nullptr)
    {
        int index = -1;
        for (int i = 0; i < this->m_object_list.size(); i++)
        {
            if (this->m_object_list[i] == this->m_object_table[name])
            {
                index = i;
                break;
            }
        }

        this->m_object_table.erase(name);

        if (index != -1)
        {
            this->m_object_list.erase(this->m_object_list.begin() + index);
        }
        else
        {
            std::cerr << name << " not found and deleted" << std::endl;
        }
    }
}

void GameObjectManager::clearAllObjects()
{
    for (AGameObject* object : this->m_object_list)
    {
        delete object;
    }

    this->m_object_table.clear();
    this->m_object_list.clear();
}

AGameObject* GameObjectManager::findObjectByName(String name)
{
    if (this->m_object_table[name] != nullptr)
    {
        return this->m_object_table[name];
    }

    std::cerr << name << " not found" << std::endl;
}

GameObjectList GameObjectManager::getAllObjects()
{
    return this->m_object_list;
}
