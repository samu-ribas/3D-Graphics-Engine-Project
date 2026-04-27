#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>
#include <list>
#include <cmath>
//#include "forma.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->desenharPonto, &QPushButton::clicked, this, &MainWindow::processarDesenho);
    connect(ui->desenharReta, &QPushButton::clicked, this, &MainWindow::processarDesenho);
    connect(ui->desenharPoligono, &QPushButton::clicked, this, &MainWindow::processarPoligono);
    connect(ui->desenharRetangulo, &QPushButton::clicked, this, &MainWindow::processarPoligono);
}

void MainWindow::processarDesenho()
{
    QString nome = ui->lineNome->text();
    if ( ui->frame->acharNome( nome ) != nullptr )
    {
        mostrarPopup();
        return;
    }

    QString tipo = ui->comboBox->currentText();

    if ( tipo == "PONTO" ){
        double x = ui->pontoX->value();
        double y = ui->pontoY->value();
         ui->frame->adicionarPonto(nome ,x, y);
    } else {
        double x = ui->retaX1->value();
        double y = ui->retaY1->value();
        double x2 = ui->retaX2->value();
        double y2 = ui->retaY2->value();
        ui->frame->adicionarReta(nome, x, y, x2, y2);
    }

}

void MainWindow::processarPoligono() {
    QString nome = ui->lineNome->text();
    QString tipo = ui->comboBox->currentText();
    std::list<std::vector<double>> listaDePontos;

    if ( tipo == "RETANGULO" )
    {
        double xBase = ui->retanguloBaseX->value();
        double yBase = ui->retanguloBaseY->value();

        double largura = ui->retanguloComprimento->value();
        double altura = ui->retanguloAltura->value();

        listaDePontos.push_back({xBase, yBase, 1.0});
        listaDePontos.push_back({xBase + largura, yBase , 1.0});
        listaDePontos.push_back({xBase + largura, yBase + altura, 1.0});
        listaDePontos.push_back({xBase, yBase + altura, 1.0});

    } else if ( tipo == "POLIGONO" )
    {
        double xBase = ui->poligonoBase->value();
        double yBase = ui->poligonoBaseY->value();

        int lados = ui->poligonoLado->value();
        double raio = ui->poligonoRaio->value();

        if (lados < 3) return;
        //algoritmo para poligono
        for (int i = 0; i < lados; ++i) {
            double angulo = 2.0 * M_PI * i / lados;
            double x = xBase + raio * cos(angulo);
            double y = yBase + raio * sin(angulo);
            listaDePontos.push_back({x, y, 1.0});
        }
    }

    // Envia para o Display File no MeuFrame
    ui->frame->adicionarPoligono(nome, listaDePontos);
}

void MainWindow::mostrarPopup()
{
    qDebug() << "Mostrando popup...";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    JanelaTranformador *janela = new JanelaTranformador( this, ui->frame );
    janela->show();
}

