#ifndef VEC2_HPP
#define VEC2_HPP
#include <cmath>
#include <iostream>

class Vec2
{
public:
  float x = 0;
  float y = 0;

  Vec2();
  Vec2(float xin, float yin);

  bool operator == (const Vec2& rhs) const;
  bool operator != (const Vec2& rhs) const;

  Vec2 operator +  (const Vec2& rhs) const;
  Vec2 operator -  (const Vec2& rhs) const;
  Vec2 operator *  (const float val) const;
  Vec2 operator /  (const float val) const;

  void operator += (const Vec2& rhs);
  void operator -= (const Vec2& rhs);
  void operator *= (const float val);
  void operator /= (const float val);

  Vec2& distVec(const Vec2& vec);
  Vec2& normalize();
  Vec2& scale(const float val);

  float distLen(const Vec2& vec) const;
  float length() const;

  void print() const;

};
#endif
