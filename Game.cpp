#include "Game.hpp"

Game::Game(const std::string& config)
{
}

void Game::init(const std::string& config)
{}

void Game::run()
{}

void Game::setPaused(bool paused)
{
  m_paused = paused;
}

void Game::sMovement()
{}

void Game::sCollision()
{}

void Game::sRender()
{}

void Game::sUserInput()
{}

void Game::sLifespan()
{}

void Game::sEnemySpawner()
{}

void Game::spawnPlayer()
{}

void Game::spawnEnemy()
{}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{}
