#include <iostream>
#include "Vec2.hpp"

  // Vec2& add(const Vec2& v)
  // {
  //   x += v.x;
  //   y += v.y;
  //   return *this;
  // }
  //
  // Vec2& scale(float s)
  // {
  //   x *= s;
  //   y *= s;
  //   return *this;
  // }

int main(int argc, char * argv[])
{
  std::cout << "selaminaleykum\n";
  Vec2 v1(1,1);
  Vec2 v2(6,6);

  Vec2 v3(3,3);
  Vec2 v4(6,7);

  v3.print();
  v4.print();

  std::cout << v3.dist(v4) << std::endl;


  return 0;
}

