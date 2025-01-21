#include "engine.h"
#include <cassert>

Engine::Engine(int size_x, int size_y)
    : curr_field(size_x * size_y, false)
    , next_field(size_x * size_y)
    , size_x(size_x)
    , size_y(size_y)
{}

void Engine::flipCell(int x, int y)
{
    assert(x + size_x * y < curr_field.size());
    curr_field[x + size_x * y] = !curr_field[x + size_x * y];
}

void Engine::setCell(int x, int y, bool state)
{
    assert(x + size_x * y < curr_field.size());
    curr_field[x + size_x * y] = state;
}

bool Engine::getCell(int x, int y)
{
    assert(x + size_x * y < curr_field.size());
    return curr_field[x + size_x * y];
}

void Engine::setSize(int x, int y)
{
    assert(x >= 3 && y >= 3);
    next_field.assign(next_field.size(), false);
    next_field.resize(x * y, false);

    for (int i = 0; i < size_y && i < y; ++i) {
        for (int j = 0; j < size_x && j < x; ++j) {
            next_field[j + x * i] = curr_field[j + size_x * i];
        }
    }
    std::swap(curr_field, next_field);
    next_field.resize(x * y);
    size_x = x;
    size_y = y;
}

void Engine::step()
{
    int size = curr_field.size();
    for (int i = 0; i < size; ++i) {
        const int count
            = curr_field[i + 1 - size_x * (i % size_x == size_x - 1)]
              + curr_field[i + size_x - size * (size - i <= size_x)]
              + curr_field[(i + 1 + size_x - size * (size - i <= size_x)
                            - size_x * (i % size_x == size_x - 1))
                           * (i != size - 1)]
              + curr_field[i - 1 + size_x * (!(i % size_x))]
              + curr_field[i - 1 + size_x - size * (size - i <= size_x) + size_x * !(i % size_x)]
              + curr_field[i - size_x + size * (i < size_x)]
              + curr_field[i - size_x + 1 + size * (i < size_x) - size_x * (i % size_x == size_x - 1)]
              + curr_field[i - 1 - size_x + size_x * !(i % size_x) + size * (i < size_x)];

        if (curr_field[i])
            next_field[i] = (2 == count || 3 == count);
        else
            next_field[i] = (count == 3);
    }
    std::swap(curr_field, next_field);
}

void Engine::reset()
{
    curr_field.assign(curr_field.size(), false);
}

const std::vector<bool> &Engine::getField()
{
    return curr_field;
}
