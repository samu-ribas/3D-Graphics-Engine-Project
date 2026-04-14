#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>
#include <list>
#include <cmath>
#include "forma.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->desenharPonto, &QPushButton::clicked, this, &MainWindow::processarDesenho);
    connect(ui->desenharReta, &QPushButton::clicked, this, &MainWindow::processarDesenho);
    connect(ui->desenharPoligono, &QPushButton::clicked, this, &MainWindow::processarPoligono);
    connect(ui->desenharPoligono_2, &QPushButton::clicked, this, &MainWindow::processarPoligono);
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

void MainWindow::processarPoligono() {
    QString nome = ui->lineNome->text();
    QString tipo = ui->comboBox->currentText();
    std::list<Coordenada> listaDePontos;

    double xBase = ui->inputX->text().toDouble();
    double yBase = ui->inputY->text().toDouble();

    if (tipo == "RETANGULO") {
        double largura = ui->largura->text().toDouble();
        double altura = ui->comprimento->text().toDouble();

        // Gera os 4 vértices do retângulo (coordenadas de mundo)
        listaDePontos.push_back({xBase, yBase});
        listaDePontos.push_back({xBase + largura, yBase});
        listaDePontos.push_back({xBase + largura, yBase + altura});
        listaDePontos.push_back({xBase, yBase + altura});

    } else if (tipo == "POLIGONO") {
        int lados = ui->lados->text().toInt();
        double raio = ui->raio->text().toDouble();

        if (lados < 3) return; // Validação básica

        // Algoritmo para gerar vértices de um polígono regular
        for (int i = 0; i < lados; ++i) {
            double angulo = 2.0 * M_PI * i / lados;
            double x = xBase + raio * cos(angulo);
            double y = yBase + raio * sin(angulo);
            listaDePontos.push_back({x, y});
        }
    }

    // Envia para o Display File no MeuFrame
    ui->frame->adicionarPoligono(nome, listaDePontos);
}

MainWindow::~MainWindow()
{
    delete ui;
}
