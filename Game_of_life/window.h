#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void on_pushButtonStep_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonPlay_clicked();

    void on_dial_valueChanged(int value);

    void on_pushButtonResize_clicked();

    void on_spinBox_X_valueChanged(int arg1);

    void on_spinBox_Y_valueChanged(int arg1);

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
