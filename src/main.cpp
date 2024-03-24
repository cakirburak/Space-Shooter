#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main(int argc, char * argv[])
{
  Game game("../config.txt");
  game.run();

  return 0;
}

