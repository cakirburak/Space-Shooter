#include "Game.hpp"

void Game::spawnPlayer()
{
  auto entity = m_entities.addEntity("player");

  entity->cTransform = std::make_shared<CTransform>(Vec2(m_windowConfig.WW/2.0f, m_windowConfig.WH/2.0f),
                                                    Vec2(0, 0),
                                                    m_playerConfig.S,
                                                    0);
  entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V,
                                            sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
                                            sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
                                            m_playerConfig.OT);
  entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
  entity->cInput = std::make_shared<CInput>();
  entity->cScore = std::make_shared<CScore>(0);

  m_player = entity;
}

void Game::spawnEnemy()
{
  auto entity = m_entities.addEntity("enemy");
  float enemyPosX = m_enemyConfig.SR + ( rand() % (1 + m_windowConfig.WW - m_enemyConfig.SR*2));
  float enemyPosY = m_enemyConfig.SR + ( rand() % (1 + m_windowConfig.WH - m_enemyConfig.SR*2));

  float randomDirs[] = {15, 45, 75, 105, 135, 165, 195, 225, 255, 285, 315, 345};
  Vec2 enemyVelocityVec(randomDirs[int(rand() % 12)]);
  float enemySpeed = m_enemyConfig.SMIN + ( rand() % int(1 + m_enemyConfig.SMAX - m_enemyConfig.SMIN));
  Vec2 enemyVelocity = enemyVelocityVec.scale(enemySpeed);

  entity->cTransform = std::make_shared<CTransform>(Vec2(enemyPosX,enemyPosY),
                                                    enemyVelocity,
                                                    enemySpeed,
                                                    0);

  int numOfV = m_enemyConfig.VMIN + ( rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));
  int r, g, b;
  r = rand() % (1 + 255);
  g = rand() % (1 + 255);
  b = rand() % (1 + 255);
  entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, numOfV,
                                            sf::Color(r, g, b),
                                            sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
                                            m_enemyConfig.OT);
  entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
  entity->cScore = std::make_shared<CScore>(numOfV*100);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
  size_t points = entity->cShape->circle.getPointCount();
  float angleInterval = 360 / (float)points;
  float radius = entity->cShape->circle.getRadius() / 2;
  Vec2 position = entity->cTransform->pos;

  for(int i = 0 ; i < points ; i++)
  {
    float angle = angleInterval * i;
    Vec2 velocity(angle);
    velocity.scale(entity->cTransform->speed);

    auto e = m_entities.addEntity("small_enemy");

    e->cTransform = std::make_shared<CTransform>(position,
                                                      velocity,
                                                      entity->cTransform->speed,
                                                      0);
    e->cShape = std::make_shared<CShape>(radius, points,
                                              entity->cShape->circle.getFillColor(),
                                              entity->cShape->circle.getOutlineColor(),
                                              entity->cShape->circle.getOutlineThickness());
    e->cCollision = std::make_shared<CCollision>(entity->cCollision->radius / 2);
    e->cScore = std::make_shared<CScore>(entity->cScore->score * points);
    e->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
  }
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
  Vec2 bulletVelocity = entity->cTransform->pos;
  bulletVelocity.distVec(mousePos).normalize().scale(m_bulletConfig.S);

  auto e = m_entities.addEntity("bullet");

  e->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, bulletVelocity,
                                               m_bulletConfig.S,
                                               0);
  e->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V,
                                       sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
                                       sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
                                       m_bulletConfig.OT);
  e->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
  e->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
}

