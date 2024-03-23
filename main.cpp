#include <iostream>
#include "EntityManager.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char * argv[])
{
  std::cout << "selaminaleykum\n";
  Vec2 v1(1,1);
  Vec2 v2(4,5);


  Vec2 speedVec = v1;
  speedVec.distVec(v2).normalize().scale(1);

  while(v1.length() <= v2.length())
  {
    v1.print();
    v1 += speedVec;
    std::cout << "Step.." << std::endl;
  }

  EntityManager eManager;

  eManager.addEntity("Player");

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}

