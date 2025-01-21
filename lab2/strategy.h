#pragma once

#include <string_view>
#include "card.h"
#include "move.h"

class Strategy {
 public:
  virtual Move GetNextMove() = 0;
  virtual void TakeCard(Card card) = 0;
  virtual void TakeOpponentCard(Card card) = 0;
  virtual std::string_view GetName() = 0;
  virtual void ReadConfig(std::string confdir) = 0;
  virtual void Reset() = 0;
  virtual void ReduceAce() = 0;
  virtual ~Strategy() = default;
};
