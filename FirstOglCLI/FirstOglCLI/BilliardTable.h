#pragma once
class BilliardTable
{
private:
  float m_width;
  float m_depth;

public:
  BilliardTable(float w, float d);
  void Draw();
  float GetWidth();
  float GetDepth();
};

