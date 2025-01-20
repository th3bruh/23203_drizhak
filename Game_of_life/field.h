#ifndef FIELD_H
#define FIELD_H

#include <QPainter>
#include <QTimer>
#include <QWidget>

#include <engine.h>

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void play();
    void stop();
    void reset();
    void setSpeed(int value);
    void setSize(int x, int y);

    bool isPlaying();
    int getSizeX();
    int getSizeY();

public slots:
    void step();

private:
    int size_x = 30;
    int size_y = 40;
    const int cell_size = 15;
    //double scale_factor = 1;
    Engine engine;
    QTimer timer;
};

#endif // FIELD_H
