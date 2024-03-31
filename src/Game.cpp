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
          >> m_bulletConfig.S
          >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB
          >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB
          >> m_bulletConfig.OT >> m_bulletConfig.V  >> m_bulletConfig.L;
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

  m_text.setString(std::string("Score: ").append(std::to_string(m_player->cScore->score)));
  m_text.setFont(m_font);
  m_text.setCharacterSize(m_fontConfig.FS);
  m_text.setPosition(4, 4);
}

void Game::run()
{

  while(m_running)
  {

    m_entities.update();

    sEnemySpawner();
    sMovement();
    sLifespan();
    sCollision();
    sUserInput();
    sRender();

    m_currentFrame++;
  }
}

void Game::sMovement()
{
  playerMovement();
  enemyMovement();
  bulletMovement();
}

void Game::setPaused(bool paused)
{
  m_paused = paused;
}

void Game::sCollision()
{
  for(auto& e: m_entities.getEntities("enemy"))
  {

    if(m_player->cTransform->pos.distLen(e->cTransform->pos)
       <
       m_player->cCollision->radius + e->cCollision->radius)
    {
      m_player->cTransform->pos.x = m_windowConfig.WW / 2.0f;
      m_player->cTransform->pos.y = m_windowConfig.WH / 2.0f;
      e->destroy();
      spawnSmallEnemies(e);
    }

    for(auto& b: m_entities.getEntities("bullet"))
    {
      if(e->cTransform->pos.distLen(b->cTransform->pos)
         <
         e->cCollision->radius + b->cCollision->radius)
      {
        m_player->cScore->score += e->cScore->score;
        m_text.setString(std::string("Score: ").append(std::to_string(m_player->cScore->score)));
        b->destroy();
        e->destroy();
        spawnSmallEnemies(e);
      }
    }
  }


  for(auto& e: m_entities.getEntities("small_enemy"))
  {
    if(m_player->cTransform->pos.distLen(e->cTransform->pos)
       <
       m_player->cCollision->radius + e->cCollision->radius)
    {
      m_player->cTransform->pos.x = m_windowConfig.WW / 2.0f;
      m_player->cTransform->pos.y = m_windowConfig.WH / 2.0f;
      e->destroy();
    }

    for(auto& b: m_entities.getEntities("bullet"))
    {
      if(e->cTransform->pos.distLen(b->cTransform->pos)
         <
         e->cCollision->radius + b->cCollision->radius)
      {
        m_player->cScore->score += e->cScore->score;
        m_text.setString(std::string("Score: ").append(std::to_string(m_player->cScore->score)));
        b->destroy();
        e->destroy();
      }
    }
  }
}

void Game::sRender()
{
  m_window.clear();

  m_window.draw(m_text);

  for(auto& e : m_entities.getEntities())
  {
    e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
    e->cTransform->angle += 1.0f;
    e->cShape->circle.setRotation(e->cTransform->angle);
    m_window.draw(e->cShape->circle);
  }

  m_window.display();

}

void Game::sLifespan()
{
  for(auto& e: m_entities.getEntities())
  {
    if(e->cLifespan)
    {
      if(e->cLifespan->remaining > 0)
      {
        sf::Color entityFillColor = e->cShape->circle.getFillColor();
        entityFillColor.a = e->cLifespan->remaining * 255 / e->cLifespan->total ;
        sf::Color entityOutColor = e->cShape->circle.getOutlineColor();
        entityOutColor.a = e->cLifespan->remaining * 255 / e->cLifespan->total ;
        e->cShape->circle.setFillColor(entityFillColor);
        e->cShape->circle.setOutlineColor(entityOutColor);
      }
      else
      {
        e->destroy();
      }

      e->cLifespan->remaining--;
    }
  }
}

void Game::sEnemySpawner()
{
  if(m_currentFrame - m_lastEnemySpawnTime == m_enemyConfig.SI)
  {
    spawnEnemy();
    m_lastEnemySpawnTime = m_currentFrame;
  }
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{}

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
        spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
      }
      if(event.mouseButton.button == sf::Mouse::Right)
      {
        std::cout << "Right Mouse Button Clicked at ("
                  << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
      }
    }
  }
}
