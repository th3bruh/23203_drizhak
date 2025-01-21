#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->field->setSpeed(ui->dial->value());
    ui->field->setSize(ui->spinBox_X->value(), ui->spinBox_Y->value());
    ui->field->setCellSize(ui->spinBoxCellSize->value());
}

Window::~Window()
{
    delete ui;
}

void Window::on_pushButtonStep_clicked()
{
    ui->field->step();
}

void Window::on_pushButtonReset_clicked()
{
    if (ui->field->isPlaying()) {
        on_pushButtonPlay_clicked();
    }
    ui->field->reset();
}


void Window::on_pushButtonPlay_clicked()
{
    if (ui->field->isPlaying()) {
        ui->field->stop();
        ui->pushButtonPlay->setText("Play");
        ui->pushButtonStep->setEnabled(true);
        return;
    }
    ui->field->play();
    ui->pushButtonStep->setEnabled(false);
    ui->pushButtonPlay->setText("Stop");
}

void Window::on_dial_valueChanged(int value)
{
    ui->field->setSpeed(value);
}

void Window::on_pushButtonResize_clicked()
{
    ui->field->setSize(ui->spinBox_X->value(), ui->spinBox_Y->value());
    ui->pushButtonResize->setEnabled(false);
}

void Window::on_spinBox_X_valueChanged(int value)
{
    ui->pushButtonResize->setEnabled(value != ui->field->getSizeX()
                                     || ui->spinBox_Y->value() != ui->field->getSizeY());
}

void Window::on_spinBox_Y_valueChanged(int value)
{
    ui->pushButtonResize->setEnabled(ui->spinBox_Y->value() != ui->field->getSizeX()
                                     || value != ui->field->getSizeY());
}

void Window::on_spinBoxCellSize_valueChanged(int value)
{
    ui->field->setCellSize(value);
}
