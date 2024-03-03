#include "Entity.hpp"

Entity::Entity(const std::string& tag, size_t id):m_id(id), m_tag(tag){}

std::string Entity::getTag()
{
  return m_tag;
}

bool Entity::getAlive()
{
  return m_alive;
}

void Entity::destroy()
{
  m_alive = false;
}
