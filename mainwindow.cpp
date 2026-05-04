#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <cmath>
#include <QMessageBox>
#include "forma.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidgetOperacoes, &QStackedWidget::setCurrentIndex);

    connect(ui->Bt_add_forma, &QPushButton::clicked, this, &MainWindow::inputObjeto);
    connect(ui->bt_op, &QPushButton::clicked, this, &MainWindow::inputOperacao);
}

void MainWindow::inputOperacao(){
    int op = ui->stackedWidgetOperacoes->currentIndex();
    QString nome = ui->lineNome->text();
    switch(op){
        case 0:{
            ui->frame->transladarObjeto(ui->comboBoxDisplayFile->currentText(),
                                        ui->inputXTranslacao->text().toDouble(),
                                        ui->inputYTranslacao->text().toDouble());
            break;
        }
        case 1:{
            double sx = ui->inputXEscala->text().isEmpty() ? 1.0 : ui->inputXEscala->text().toDouble();
            double sy = ui->inputYEscala->text().isEmpty() ? 1.0 : ui->inputYEscala->text().toDouble();
            if (sx == 0.0) sx = 1.0;
            if (sy == 0.0) sy = 1.0;
            ui->frame->escalarObjeto(ui->comboBoxDisplayFile->currentText(),sx, sy);
            break;
        }
        case 2:{
            ui->frame->rotacionarObjeto(ui->comboBoxDisplayFile->currentText(),
                                        ui->inputAnguloRotacao->text().toDouble(),
                                        ui->inputXRotacao->text().toDouble(),
                                        ui->inputYRotacao->text().toDouble(),
                                        ui->checkBox->isChecked());
            break;
        }
    }
}

void MainWindow::inputObjeto(){
    if((ui->lineNome->text()).trimmed().isEmpty() || ui->frame->contemObjeto(ui->lineNome->text())){
        QMessageBox::warning(this, "Erro", "Insira o nome do objeto!");
        ui->lineNome->setFocus();
        return;
    }

    int id = ui->stackedWidget->currentIndex();
    switch(id){
        case 0:// ponto
            ui->frame->adicionarPonto(ui->lineNome->text(),ui->inputX->text().toDouble(), ui->inputY->text().toDouble());
            break;
        case 1://reta
            ui->frame->adicionarReta(ui->lineNome->text(),
                                    ui->inputXReta->text().toDouble(),
                                    ui->inputYReta->text().toDouble(),
                                    ui->inputXReta_2->text().toDouble(),
                                    ui->inputYReta_2->text().toDouble());
            break;
        case 2:
            this->processarPoligono(ui->inputXPoligono->text().toDouble(), // x do centro
                                   ui->inputYPoligono->text().toDouble(), // y do centro
                                   ui->inputLados->text().toInt(),
                                   ui->inputRaio->text().toDouble());
            break;
        case 3:
            this->processarPoligono(ui->inputXRetangulo->text().toDouble(), // x do canto
                                   ui->inputYRetangulo->text().toDouble(), // y do canto
                                   ui->comprimentoRetangulo->text().toDouble(),
                                   ui->alturaRetangulo->text().toDouble());
        break;
    }
    ui->comboBoxDisplayFile->addItem(ui->lineNome->text());
    ui->lineNome->clear();
}

//polígono
void MainWindow::processarPoligono(double x, double y, int l, double r){
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
void MainWindow::processarPoligono(double x, double y, double c, double h){
    std::list<Coordenada> listaDePontos;
    listaDePontos.push_back({x, y});
    listaDePontos.push_back({x + c, y});
    listaDePontos.push_back({x + c, y+ h});
    listaDePontos.push_back({x, y + h});

    ui->frame->adicionarPoligono(ui->lineNome->text(), listaDePontos);
}

void MainWindow::on_btn_cima_clicked()
{
    ui->frame->window.centro_y += deslocamentoWindow;
    ui->frame->recalcularSCN();
    ui->frame->update();
}


void MainWindow::on_btn_baixo_clicked()
{
    ui->frame->window.centro_y -= deslocamentoWindow;
    ui->frame->recalcularSCN();
    ui->frame->update();
}

void MainWindow::on_btn_esquerda_clicked()
{
    ui->frame->window.centro_x += deslocamentoWindow;
    ui->frame->recalcularSCN();
    ui->frame->update();
}


void MainWindow::on_btn_direita_clicked()
{
    ui->frame->window.centro_x -= deslocamentoWindow;
    ui->frame->recalcularSCN();
    ui->frame->update();
}


void MainWindow::on_btn_zoomMais_clicked()
{
    ui->frame->window.altura -= deslocamentoWindow;
    ui->frame->window.largura -= deslocamentoWindow;
    ui->frame->recalcularSCN();
    ui->frame->update();
}


void MainWindow::on_btn_zoomMenos_clicked()
{
    ui->frame->window.altura += deslocamentoWindow;
    ui->frame->window.largura += deslocamentoWindow;
    ui->frame->recalcularSCN();
    ui->frame->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
