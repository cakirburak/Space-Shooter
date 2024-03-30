#include "Game.hpp"

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

  if(!m_font.loadFromFile(m_fontConfig.FILE))
  {
    std::cerr << "Could not load specified Font!" << "\n";
  }

  spawnPlayer();

}

void Game::run()
{

  while(m_running)
  {

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

  playerMovement();
}

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
    {
      m_player->cTransform->velocity.y = -m_playerConfig.S;
    }
    else if(m_player->cInput->down)
    {
      m_player->cTransform->velocity.y = m_playerConfig.S;
    }
    else if(m_player->cInput->right)
    {
      m_player->cTransform->velocity.x = m_playerConfig.S;
    }
    else if(m_player->cInput->left)
    {
      m_player->cTransform->velocity.x = -m_playerConfig.S;
    }
  }

  m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
  m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
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
{
  sf::Event event;
  while (m_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed){
      m_running = false;
    }

    if(event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::W:
          m_player->cInput->up = true;
          break;
        case sf::Keyboard::S:
          m_player->cInput->down = true;
          break;
        case sf::Keyboard::A:
          m_player->cInput->left = true;
          break;
        case sf::Keyboard::D:
          m_player->cInput->right = true;
          break;
        default: break;
      }
    }

    if(event.type == sf::Event::KeyReleased)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::W:
          m_player->cInput->up = false;
          break;
        case sf::Keyboard::S:
          m_player->cInput->down = false;
          break;
        case sf::Keyboard::A:
          m_player->cInput->left = false;
          break;
        case sf::Keyboard::D:
          m_player->cInput->right = false;
          break;
        default: break;
      }
    }

    if(event.type == sf::Event::MouseButtonPressed)
    {
      if(event.mouseButton.button == sf::Mouse::Left)
      {
        std::cout << "Left Mouse Button Clicked at ("
                  << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
      }
      if(event.mouseButton.button == sf::Mouse::Right)
      {
        std::cout << "Right Mouse Button Clicked at ("
                  << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
      }
    }
  }
}

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
  float enemyPosX = m_enemyConfig.SR + ( rand() % (1 + m_windowConfig.WW - m_enemyConfig.SR*2));
  float enemyPosY = m_enemyConfig.SR + ( rand() % (1 + m_windowConfig.WH - m_enemyConfig.SR*2));
  entity->cTransform = std::make_shared<CTransform>(Vec2(enemyPosX,enemyPosY),
                                                    Vec2(0,0),
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
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{}
