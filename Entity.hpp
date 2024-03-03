#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <iostream>

class Entity
{
  const size_t m_id = 0;
  const std::string m_tag = "Default";
  bool m_alive = true;

public:
  /*
   * Components will be here
   * std::shared_ptr<CTransform> cTransform;
   */

  Entity(const std::string& tag, size_t id);
  std::string getTag();
  bool getAlive();
  void destroy();

};

#endif
