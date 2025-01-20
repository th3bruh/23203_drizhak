#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

class Engine
{
public:
    Engine(int size_x, int size_y);

    const std::vector<bool> &getField();
    void flipCell(int x, int y);
    void step();
    void reset();
    void setSize(int x, int y);

private:
    std::vector<bool> curr_field;
    std::vector<bool> next_field;
    int size_x;
    int size_y;
};

#endif // ENGINE_H
