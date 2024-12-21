#pragma once

#include <string>
#include <vector>

#include "factory.h"

class Engine {
 public:
  virtual void Play() = 0;
  virtual std::vector<size_t> GetWinners() = 0;
  virtual ~Engine() = default;
};

namespace engine_namespace {
using Factory =
    Factory<std::string, std::function<Engine*(std::vector<std::string>,
                                               std::string, std::string, unsigned int)>>;
}  // namespace engine_namespace

