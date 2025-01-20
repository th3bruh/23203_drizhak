#include "field.h"
#include "QMouseEvent"

Field::Field(QWidget *parent)
    : QWidget{parent}
    , engine(size_x, size_y)
    , timer(this)
{
    setFixedSize(size_x * cell_size, size_y * cell_size);
    timer.setInterval(1);
    connect(&timer, &QTimer::timeout, this, &Field::step);
}

void Field::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::white);

    //p.setPen(QPen(Qt::gray, 2));
    p.setPen(Qt::gray);
    const std::vector<bool> &f = engine.getField();
    for (int i = 0; i < size_y; ++i) {
        for (int j = 0; j < size_x; ++j) {
            if (f[j + size_x * i]) {
                continue;
            }
            p.fillRect(j * cell_size, i * cell_size, cell_size, cell_size, Qt::black);
        }
    }
    for (int i = 0; i <= size_x; ++i) {
        p.drawLine(i * cell_size, 0, i * cell_size, size_y * cell_size);
    }
    for (int i = 0; i <= size_y; ++i) {
        p.drawLine(0, i * cell_size, size_x * cell_size, i * cell_size);
    }
}

void Field::mousePressEvent(QMouseEvent *event)
{
    if (isPlaying()) {
        return;
    }
    int x = event->pos().x() / cell_size;
    int y = event->pos().y() / cell_size;
    engine.flipCell(x, y);
    update();
}

void Field::step()
{
    engine.step();
    update();
}

bool Field::isPlaying()
{
    return timer.isActive();
}

void Field::play()
{
    timer.start();
}

void Field::stop()
{
    timer.stop();
    update();
}

void Field::reset()
{
    timer.stop();
    engine.reset();
    update();
}

void Field::setSpeed(int value)
{
    assert(1 <= value && value <= 100);
    timer.setInterval(2 * (100 - value));
}

void Field::setSize(int x, int y)
{
    engine.setSize(x, y);
    size_x = x;
    size_y = y;
    setFixedSize(size_x * cell_size, size_y * cell_size);
    update();
}

int Field::getSizeX()
{
    return size_x;
}

int Field::getSizeY()
{
    return size_y;
}
