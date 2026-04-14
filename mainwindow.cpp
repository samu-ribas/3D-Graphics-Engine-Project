#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->desenharPonto, &QPushButton::clicked, this, &MainWindow::processarDesenhoPonto);

}

void MainWindow::processarDesenhoPonto(){
    int x = ui->inputX->text().toInt();
    int y = ui->inputY->text().toInt();
    ui->frame->adicionarPonto("ponto",x, y);
}

MainWindow::~MainWindow()
{
    delete ui;
}
