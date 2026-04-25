#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <cmath>
#include "forma.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->desenharPoligono, &QPushButton::clicked, this, &MainWindow::processarPoligono);
    connect(ui->desenharPoligono_2, &QPushButton::clicked, this, &MainWindow::processarPoligono);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(ui->Bt_add_forma, &QPushButton::clicked, this, &MainWindow::inputCoordenadas);
}

void MainWindow::inputCoordenadas(){;
    int id = ui->stackedWidget->currentIndex();
    switch(id){
    case 0:
        this->processarDesenho(ui->inputX->text().toDouble(), ui->inputY->text().toDouble());
        break;
    case 1:
        this->processarDesenho(ui->inputXReta->text().toDouble(),
                                ui->inputYReta->text().toDouble(),
                                ui->inputXReta_2->text().toDouble(),
                                ui->inputYReta_2->text().toDouble());
        break;
    case 2:

        break;
    case 3:
        break;
    }
}

void MainWindow::processarDesenho(double x,  double y){
    ui->frame->adicionarPonto(ui->lineNome->text(),x, y);
}

void MainWindow::processarDesenho(double x1, double y1, double x2, double y2){
    ui->frame->adicionarReta(ui->lineNome->text(), x1, y1, x2, y2);
}

//essa função será alterada
void MainWindow::processarPoligono() {
    QString nome = ui->lineNome->text();
    QString tipo = ui->comboBox->currentText();
    std::list<Coordenada> listaDePontos;

    double xBase = ui->inputX_2->text().toDouble();
    double yBase = ui->inputY_2->text().toDouble();

    if (tipo == "RETANGULO") {
        double largura = ui->largura->text().toDouble();
        double altura = ui->comprimento->text().toDouble();

        listaDePontos.push_back({xBase, yBase});
        listaDePontos.push_back({xBase + largura, yBase});
        listaDePontos.push_back({xBase + largura, yBase + altura});
        listaDePontos.push_back({xBase, yBase + altura});

    } else if (tipo == "POLIGONO") {
        int lados = ui->lados->text().toInt();
        double raio = ui->raio->text().toDouble();

        if (lados < 3) return;
        //algoritmo para poligono
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
