#pragma once

#include <string>
#include <vector>

#include "deck.h"
#include "factory.h"
#include "strategy.h"
#include "user_interface.h"

class Engine {
 public:
  virtual void Play() = 0;
  virtual void PrintWinners() = 0;
  virtual std::vector<size_t> GetWinners() = 0;
  virtual ~Engine() = default;
};

namespace engine {
using Factory =
    Factory<std::string,
            std::function<Engine*(std::vector<Strategy*>&, UserInterface&, Deck&)>>;
}  // namespace engine
