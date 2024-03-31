#include "Game.hpp"

void Game::playerMovement()
{
  m_player->cTransform->velocity = {0, 0};

  if(m_player->cTransform->pos.x < m_playerConfig.SR + m_playerConfig.OT)
    m_player->cInput->left = false;
  if(m_player->cTransform->pos.x + m_playerConfig.SR + m_playerConfig.OT > m_windowConfig.WW)
    m_player->cInput->right = false;
  if(m_player->cTransform->pos.y < m_playerConfig.SR + m_playerConfig.OT)
    m_player->cInput->up = false;
  if(m_player->cTransform->pos.y + m_playerConfig.SR + m_playerConfig.OT > m_windowConfig.WH)
    m_player->cInput->down = false;

  if(m_player->cInput->up && m_player->cInput->right)
  {
    Vec2 velocityVec(m_playerConfig.S, -m_playerConfig.S);
    velocityVec.normalize().scale(m_playerConfig.S);
    m_player->cTransform->velocity = velocityVec;
  }
  else if(m_player->cInput->up && m_player->cInput->left)
  {
    Vec2 velocityVec(-m_playerConfig.S, -m_playerConfig.S);
    velocityVec.normalize().scale(m_playerConfig.S);
    m_player->cTransform->velocity = velocityVec;
  }
  else if(m_player->cInput->down && m_player->cInput->right)
  {
    Vec2 velocityVec(m_playerConfig.S, m_playerConfig.S);
    velocityVec.normalize().scale(m_playerConfig.S);
    m_player->cTransform->velocity = velocityVec;
  }
  else if(m_player->cInput->down && m_player->cInput->left)
  {
    Vec2 velocityVec(-m_playerConfig.S, m_playerConfig.S);
    velocityVec.normalize().scale(m_playerConfig.S);
    m_player->cTransform->velocity = velocityVec;
  }
  else
  {
    if(m_player->cInput->up)
      m_player->cTransform->velocity.y = -m_playerConfig.S;
    else if(m_player->cInput->down)
      m_player->cTransform->velocity.y = m_playerConfig.S;
    else if(m_player->cInput->right)
      m_player->cTransform->velocity.x = m_playerConfig.S;
    else if(m_player->cInput->left)
      m_player->cTransform->velocity.x = -m_playerConfig.S;
  }

  m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
  m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::enemyMovement()
{
  for( auto& e: m_entities.getEntities("enemy"))
  {
    if(e->cTransform->pos.x + e->cCollision->radius > m_windowConfig.WW ||
       e->cTransform->pos.x - e->cCollision->radius < 0 )
      e->cTransform->velocity.x *= -1;
    if(e->cTransform->pos.y + e->cCollision->radius > m_windowConfig.WH ||
       e->cTransform->pos.y - e->cCollision->radius < 0 )
      e->cTransform->velocity.y *= -1;
    e->cTransform->pos.x += e->cTransform->velocity.x;
    e->cTransform->pos.y += e->cTransform->velocity.y;
  }
  for( auto& e: m_entities.getEntities("small_enemy"))
  {
    if(e->cTransform->pos.x + e->cCollision->radius > m_windowConfig.WW ||
       e->cTransform->pos.x - e->cCollision->radius < 0 )
      e->cTransform->velocity.x *= -1;
    if(e->cTransform->pos.y + e->cCollision->radius > m_windowConfig.WH ||
       e->cTransform->pos.y - e->cCollision->radius < 0 )
      e->cTransform->velocity.y *= -1;
    e->cTransform->pos.x += e->cTransform->velocity.x;
    e->cTransform->pos.y += e->cTransform->velocity.y;
  }
}

void Game::bulletMovement()
{
  for( auto& e: m_entities.getEntities("bullet"))
  {
    e->cTransform->pos += e->cTransform->velocity;
  }
}




