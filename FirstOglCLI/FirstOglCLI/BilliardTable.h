#pragma once
#include "OglForCLI.h"
#include "Cuboid.h"

class BilliardTable
{
private:
	std::vector<Cuboid> cuboids_;
  BilliardTable();

public:
  static BilliardTable* GetInst() {
    static BilliardTable p;
    return &p;
  }

  void Draw() const;
};

