#pragma once

#include <string>
#include "card.h"

enum class Move { Hit, Stand };

class Strategy {
 public:
  virtual Move GetNextMove() = 0;
  virtual void TakeCard(Card card) = 0;
  virtual void TakeOpponentCard(Card card) = 0;
  virtual std::string GetName() = 0;
  virtual ~Strategy() = default;
};

