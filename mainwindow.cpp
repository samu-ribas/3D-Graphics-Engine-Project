#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->desenharPonto, &QPushButton::clicked, this, &MainWindow::processarDesenho);
    connect(ui->desenharReta, &QPushButton::clicked, this, &MainWindow::processarDesenho);
}

void MainWindow::processarDesenho(){
    double x = ui->inputX->text().toDouble();
    double y = ui->inputY->text().toDouble();
    QString nome = ui->lineNome->text();
    QString tipo = ui->comboBox->currentText();

    if(tipo == "PONTO"){
         ui->frame->adicionarPonto(nome ,x, y);
    }else{
        double x2 = ui->inputXReta->text().toDouble();
        double y2 = ui->inputYReta->text().toDouble();
        ui->frame->adicionarReta(nome, x, y, x2, y2);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
