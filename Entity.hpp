#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "Components.hpp"

class Entity
{
  const size_t m_id = 0;
  const std::string m_tag = "Default";
  bool m_alive = true;

public:

  std::shared_ptr<CTransform>   cTransform;
  std::shared_ptr<CShape>       cShape;
  std::shared_ptr<CCollision>   cCollision;
  std::shared_ptr<CScore>       cScore;
  std::shared_ptr<CLifespan>    cLifespan;
  std::shared_ptr<CInput>       cInput;

  Entity(const std::string& tag, size_t id);
  std::string getTag();
  bool getAlive();
  void destroy();

};

#endif
