#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <cmath>
#include <QMessageBox>
#include "forma.h"
//#include "Matriz.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidgetOperacoes, &QStackedWidget::setCurrentIndex);

    connect(ui->Bt_add_forma, &QPushButton::clicked, this, &MainWindow::inputCoordenadas);
    connect(ui->bt_op, &QPushButton::clicked, this, &MainWindow::inputOperacao);
}

void MainWindow::inputOperacao(){
    int op = ui->stackedWidgetOperacoes->currentIndex();
    QString nome = ui->lineNome->text();
    switch(op){
        case 0:{
            // Matriz::gerarMatrizT(ui->inputXTranslacao->text().toDouble(), ui->inputYTranslacao->text().toDouble());
            break;
        }
        case 1:{
            // Matriz::gerarMatrizE(ui->inputXEscala->text().toDouble(), ui->inputYEscala->text().toDouble());
            break;
        }
        case 2:{

            break;
        }
    }
}

void MainWindow::inputCoordenadas(){;
    if((ui->lineNome->text()).trimmed().isEmpty()){
        QMessageBox::warning(this, "Erro", "Insira o nome do objeto!");
        return;
    }

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
            this->processarDesenho(ui->inputXPoligono->text().toDouble(), // x do centro
                                   ui->inputYPoligono->text().toDouble(), // y do centro
                                   ui->inputLados->text().toInt(),
                                   ui->inputRaio->text().toDouble());
            break;
        case 3:
            this->processarDesenho(ui->lineNome->text(),
                                   ui->inputXRetangulo->text().toDouble(), // x do canto
                                   ui   ->inputYRetangulo->text().toDouble(), // y do canto
                                   ui->comprimentoRetangulo->text().toDouble(),
                                   ui->alturaRetangulo->text().toDouble());
        break;
    }
    ui->lineNome->clear();
}

// ponto
void MainWindow::processarDesenho(double x,  double y){
    ui->frame->adicionarPonto(ui->lineNome->text(),x, y);
}
//reta
void MainWindow::processarDesenho(double x1, double y1, double x2, double y2){
    ui->frame->adicionarReta(ui->lineNome->text(), x1, y1, x2, y2);
}
//polígono
void MainWindow::processarDesenho(double x, double y, int l, double r){
    if (l< 3) return;

    std::list<Coordenada> listaDePontos;
    double offset = (l % 2 == 0) ? (M_PI / l) : (M_PI / 2.0);

    for (int i = 0; i < l; ++i){
        double angulo = 2.0 * M_PI * i / l - offset;
        double xbase = x + r * cos(angulo);
        double ybase = y + r * sin(angulo);
        listaDePontos.push_back({xbase, ybase});
    }

    ui->frame->adicionarPoligono(ui->lineNome->text(), listaDePontos);
}
//retângulo
void MainWindow::processarDesenho(QString nome, double x, double y, double c, double h){
    std::list<Coordenada> listaDePontos;
    listaDePontos.push_back({x, y});
    listaDePontos.push_back({x + c, y});
    listaDePontos.push_back({x + c, y+ h});
    listaDePontos.push_back({x, y + h});

    ui->frame->adicionarPoligono(nome, listaDePontos);
}

MainWindow::~MainWindow()
{
    delete ui;
}
