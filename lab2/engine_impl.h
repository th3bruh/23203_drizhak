#pragma once

#include "engine.h"
#include "factory.h"
#include "strategy.h"
#include "user_interface.h"

namespace engine {
template <class T>
using Registrator =
    Registrator<std::string, Engine, T, std::vector<Strategy*>&, UserInterface&,
                Deck&>;
}
