#include "Vec2.hpp"

Vec2::Vec2(){}

Vec2::Vec2(float xin, float yin):x(xin),y(yin){}

Vec2::Vec2(float angle)
{
  float radian = angle * 3.14 / 180;
  x = std::cos(radian);
  y = std::sin(radian);
}

bool Vec2::operator == (const Vec2& rhs) const
{
  return (x == rhs.x && y== rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
  return !(x == rhs.x && y== rhs.y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
  return Vec2(x+rhs.x, y+rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
  return Vec2(x-rhs.x, y-rhs.y);
}

Vec2 Vec2::operator * (const Vec2& vec) const
{
  return Vec2(x*vec.x, y*vec.y);
}
Vec2 Vec2::operator * (const float val) const
{
  return Vec2(x*val, y*val);
}

Vec2 Vec2::operator / (const float val) const
{
  return Vec2(x/val, y/val);
}

void Vec2::operator += (const Vec2& rhs)
{
  x += rhs.x; y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
  x -= rhs.x; y -= rhs.y;
}

void Vec2::operator *= (const float val)
{
  x *= val; y *= val;
}

void Vec2::operator /= (const float val)
{
  x /= val; y /= val;
}

Vec2& Vec2::distVec(const Vec2& vec)
{
  *this -= vec;
  *this *= -1;
  return *this;
}

Vec2& Vec2::normalize()
{
  *this /= this->length();
  return *this;
}

Vec2& Vec2::scale(const float val)
{
  x *= val; y *= val;
  return *this;
}

float Vec2::distLen(const Vec2& vec) const
{
  return sqrt( (vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) );
}

float Vec2::length() const
{
  return sqrt(x*x + y*y);
}

void Vec2::print() const
{
  std::cout << "X: " << x << " / Y: " << y << std::endl;
}












