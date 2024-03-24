#include "EntityManager.hpp"

EntityManager::EntityManager(){}

void EntityManager::update()
{
  for(auto& e : m_toAdd)
  {
    m_entities.push_back(e);
    m_entityMap[e->getTag()].push_back(e);
  }
  m_toAdd.clear();

  removeDeadEntities(m_entities);

  for(auto& [tag, entityVec]: m_entityMap)
  {
    removeDeadEntities(entityVec);
  }

  // // Removes dead entities from m_entities
  // m_entities.erase(std::remove_if(
  //    m_entities.begin()
  //   ,m_entities.end()
  //   ,[this](std::shared_ptr<Entity> e)
  //   {
  //     if(!e->getAlive())
  //     {
  //       // removes dead entities from entityMap
  //       // by capturing "e" in the iteration
  //       auto tag = e->getTag();
  //       m_entityMap[tag].erase(std::remove_if(
  //          m_entityMap[tag].begin()
  //         ,m_entityMap[tag].end()
  //         ,[this](std::shared_ptr<Entity> e) { return !e->getAlive(); }
  //       ), m_entityMap[tag].end());
  //     }
  //     return !e->getAlive();
  //   }
  // ), m_entities.end());
}

void EntityManager::removeDeadEntities(EntityVec& entityVec)
{
  entityVec.erase(std::remove_if(
     entityVec.begin()
    ,entityVec.end()
    ,[](std::shared_ptr<Entity> e)
    {
      return !e->getAlive();
    }
  ), entityVec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
  auto e = std::make_shared<Entity>(tag, m_totalEntities++);
  m_toAdd.push_back(e);
  return e;
}

EntityVec& EntityManager::getEntities()
{
  return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
  return m_entityMap[tag];
}
