#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP
#include "Entity.hpp"
#include <map>
#include <memory>
#include <vector>
// #include <algorithm>


typedef std::vector <std::shared_ptr<Entity>> EntityVec;
typedef std::map    <std::string, EntityVec>  EntityMap;

class EntityManager
{
  EntityVec m_entities;
  EntityMap m_entityMap;
  EntityVec m_toAdd;
  size_t    m_totalEntities;

public:

  EntityManager();
  void update();
  std::shared_ptr<Entity> addEntity(const std::string& tag);
  EntityVec& getEntities();
  EntityVec& getEntities(const std::string& tag);

};

#endif
