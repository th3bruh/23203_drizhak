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

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void play();
    void stop();
    void reset();
    void setSpeed(int value);
    void setSize(int x, int y);
    void setCellSize(int size);

    bool isPlaying();
    int getSizeX();
    int getSizeY();

public slots:
    void step();

private:
    enum class DragState {
        Inactive,
        SetAlive,
        SetUnalive,
    };
    DragState state = DragState::Inactive;
    int size_x = 30;
    int size_y = 40;
    int cell_size = 15;
    Engine engine;
    QTimer timer;
};

#endif // FIELD_H
