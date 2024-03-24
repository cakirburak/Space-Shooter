#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <fstream>
#include <cstdlib>
#include <iostream>

struct WindowConfig { int WW, WH, FR, IFS; };
struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };
struct FontConfig   { std::string FILE; int FS, FR, FG, FB; };

class Game
{
  sf::RenderWindow    m_window;
  EntityManager       m_entities;
  sf::Font            m_font;
  sf::Text            m_text;
  WindowConfig        m_windowConfig;
  FontConfig          m_fontConfig;
  PlayerConfig        m_playerConfig;
  EnemyConfig         m_enemyConfig;
  BulletConfig        m_bulletConfig;
  int                 m_score = 0;
  int                 m_currentFrame = 0;
  int                 m_lastEnemySpawnTime = 0;
  bool                m_paused = false;
  int                 m_running = true;

  std::shared_ptr<Entity> m_player;

  void init(const std::string& config);
  void setPaused(bool paused);

  void sMovement();
  void sUserInput();
  void sLifespan();
  void sRender();
  void sEnemySpawner();
  void sCollision();

  void spawnPlayer();
  void spawnEnemy();
  void spawnSmallEnemies(std::shared_ptr<Entity> entity);
  void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
  void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

  Game(const std::string& config);
  void run();

};

#endif

