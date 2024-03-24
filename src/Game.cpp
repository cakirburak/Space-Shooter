#include "Game.hpp"
#include <cstring>
#include <string>

Game::Game(const std::string& config)
{
  init(config);
}

void Game::init(const std::string& config)
{
  std::fstream fin(config);

  std::string temp = "";
  while (fin >> temp)
  {
    if(temp == "Window")
    {
      fin >> m_windowConfig.WW >> m_windowConfig.WH >> m_windowConfig.FR >> m_windowConfig.IFS;
    }
    else if (temp == "Font")
    {
      fin >> m_fontConfig.FILE >> m_fontConfig.FS >> m_fontConfig.FR >> m_fontConfig.FG >> m_fontConfig.FB;
      std::string fontDir = "../fonts/";
      m_fontConfig.FILE = fontDir + m_fontConfig.FILE;
    }
    else if (temp == "Player")
    {
      fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S
          >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB
          >> m_playerConfig.OR >> m_playerConfig.OB >> m_playerConfig.OB
          >> m_playerConfig.OT >> m_playerConfig.V;
    }
    else if (temp == "Enemy")
    {
      fin >> m_enemyConfig.SR   >> m_enemyConfig.CR
          >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX
          >> m_enemyConfig.OR   >> m_enemyConfig.OG   >> m_enemyConfig.OB >> m_enemyConfig.OT
          >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX
          >> m_enemyConfig.L    >> m_enemyConfig.SI;
    }
    else if (temp == "Bullet")
    {
      fin >> m_bulletConfig.SR >> m_bulletConfig.CR
          >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB
          >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB
          >> m_bulletConfig.OT >> m_bulletConfig.V  >> m_bulletConfig.L >> m_bulletConfig.S;
    }
    else
    {
      std::cout << temp << "\n";
    }
  }

  m_window.create(sf::VideoMode(m_windowConfig.WW, m_windowConfig.WH), "Space Shooter");
  m_window.setFramerateLimit(m_windowConfig.FR);

  m_font.loadFromFile(m_fontConfig.FILE);

  spawnPlayer();

}

void Game::run()
{

  while(m_running)
  {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed){
        m_window.close();
        m_running = false;
      }
    }

    m_entities.update();

    sEnemySpawner();
    sMovement();
    sCollision();
    sUserInput();
    sRender();

    m_currentFrame++;
  }
}

void Game::setPaused(bool paused)
{
  m_paused = paused;
}

void Game::sMovement()
{

}

void Game::sCollision()
{}

void Game::sRender()
{
  m_window.clear();

  for(auto& e : m_entities.getEntities())
  {
    e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
    e->cTransform->angle += 1.0f;
    e->cShape->circle.setRotation(e->cTransform->angle);
    m_window.draw(e->cShape->circle);
  }

  m_window.display();

}

void Game::sUserInput()
{}

void Game::sLifespan()
{}

void Game::sEnemySpawner()
{
  if(m_currentFrame - m_lastEnemySpawnTime == m_windowConfig.FR)
  {
    spawnEnemy();
    m_lastEnemySpawnTime = m_currentFrame;
  }
}

void Game::spawnPlayer()
{
  auto entity = m_entities.addEntity("player");

  entity->cTransform = std::make_shared<CTransform>(Vec2(m_windowConfig.WW/2.0f, m_windowConfig.WH/2.0f),
                                                    Vec2(0, 0),
                                                    0);
  entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V,
                                            sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
                                            sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
                                            m_playerConfig.OT);
  entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
  entity->cInput = std::make_shared<CInput>();

  m_player = entity;
}

void Game::spawnEnemy()
{
  auto entity = m_entities.addEntity("enemy");
  float enemyPosX = m_enemyConfig.SR*2 + ( rand() % (1 + m_windowConfig.WW - m_enemyConfig.SR*2));
  float enemyPosY = m_enemyConfig.SR*2 + ( rand() % (1 + m_windowConfig.WH - m_enemyConfig.SR*2));
  entity->cTransform = std::make_shared<CTransform>(Vec2(enemyPosX,enemyPosY),
                                                    Vec2(0,0),
                                                    0);

  int numOfV = m_enemyConfig.VMIN + ( rand() % (1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));
  std::cout << numOfV << std::endl;
  int r, g, b;
  r = rand() % (1 + 255);
  g = rand() % (1 + 255);
  b = rand() % (1 + 255);
  entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, numOfV,
                                            sf::Color(r, g, b),
                                            sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
                                            m_enemyConfig.OT);
  entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{}
