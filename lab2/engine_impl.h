#pragma once

#include "engine.h"
#include "factory.h"

namespace engine_namespace {
template <class T>
using Registrator =
    Registrator<std::string, Engine, T, std::vector<std::string>, std::string,
                std::string, unsigned int>;
}
