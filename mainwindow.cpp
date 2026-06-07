#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <cmath>
#include <QMessageBox>
#include "Forma.h"
#include "dialogconfigwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame->window = Window(0.0, 0.0, 500, 250);//inicializa a câmera diretamente no Frame
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
    this->setDeslocamento();

    //stacked widget + comboBox
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidgetOperacoes, &QStackedWidget::setCurrentIndex);
    //botões
    connect(ui->Bt_add_forma, &QPushButton::clicked, this, &MainWindow::inputObjeto);
    connect(ui->bt_op, &QPushButton::clicked, this, &MainWindow::inputOperacao);
    //spinBox
    connect(ui->spinBoxDesloc, &QSpinBox::valueChanged, this, &MainWindow::setDeslocamento);
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
            if(sx == 0.0) sx = 1.0;
            if(sy == 0.0) sy = 1.0;
            ui->frame->escalarObjeto(ui->comboBoxDisplayFile->currentText(),sx, sy);
            break;
        }

        case 2:{
            ui->frame->rotacionarObjeto(ui->comboBoxDisplayFile->currentText(),
                                        ui->inputAnguloRotacao->text().toDouble(),
                                        ui->inputXRotacao->text().toDouble(),
                                        ui->inputYRotacao->text().toDouble(),
                                        ui->checkBoxCentroide->isChecked(), ui->checkBoxCoordenadasDoMundo->isChecked());
            break;
        }
    }
    ui->frame ->recalcularSCN();
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
            ui->frame->adicionarPonto(ui->lineNome->text(),
                                      ui->inputX->text().toDouble() + ui->frame->window.getCentro_x(),
                                      ui->inputY->text().toDouble() + ui->frame->window.getCentro_y());
            break;
        case 1://reta
            ui->frame->adicionarReta(ui->lineNome->text(),
                                    ui->inputXReta->text().toDouble() + ui->frame->window.getCentro_x(),
                                     ui->inputYReta->text().toDouble() + ui->frame->window.getCentro_y(),
                                    ui->inputXReta_2->text().toDouble() + ui->frame->window.getCentro_x (),
                                     ui->inputYReta_2->text().toDouble() + ui->frame->window.getCentro_y() );
            break;
        case 2://poligono
            this->processarPoligono(ui->inputXPoligono->text().toDouble() + ui->frame->window.getCentro_x(), // x do centro
                                    ui->inputYPoligono->text().toDouble() + ui->frame->window.getCentro_y(), // y do centro
                                   ui->inputLados->text().toInt(),
                                   ui->inputRaio->text().toDouble());
            break;
        case 3://retangulo
            this->processarPoligono(ui->inputXRetangulo->text().toDouble() + ui->frame->window.getCentro_x (), // x do canto
                                    ui->inputYRetangulo->text().toDouble() + ui->frame->window.getCentro_y() , // y do canto
                                   ui->comprimentoRetangulo->text().toDouble(),
                                   ui->alturaRetangulo->text().toDouble());
        break;
    }
    ui->comboBoxDisplayFile->addItem(ui->lineNome->text());
    ui->lineNome->clear();
}

//processa polígono
void MainWindow::processarPoligono(double x, double y, int l, double r){
    if (l< 3) return;

    std::list<Coordenada> listaDePontos;
    double offset = (l % 2 == 0) ? (M_PI / l) : (M_PI / 2.0);

    for (int i = 0; i < l; ++i){
        double angulo = 2.0 * M_PI * i / l + offset;
        double xbase = x + r * cos(angulo);
        double ybase = y + r * sin(angulo);
        listaDePontos.push_back({xbase, ybase});
    }

    ui->frame->adicionarPoligono(ui->lineNome->text(), listaDePontos);
}

//processa retângulo
void MainWindow::processarPoligono(double x, double y, double c, double h){
    std::list<Coordenada> listaDePontos;
    listaDePontos.push_back({x, y});
    listaDePontos.push_back({x + c, y});
    listaDePontos.push_back({x + c, y+ h});
    listaDePontos.push_back({x, y + h});

    ui->frame->adicionarPoligono(ui->lineNome->text(), listaDePontos);
}

void MainWindow::on_btn_winConfig_pressed()
{
    DialogConfigWindow winConfig = DialogConfigWindow(this);
    winConfig.setDisplay(ui->frame->window.getLargura(), ui->frame->window.getAltura());
    ;
    if(winConfig.exec() == QDialog::Accepted){
        ui->frame->window.setLargura(winConfig.getLarguraDigitada());
        ui->frame->window.setAltura(winConfig.getAlturaDigitada());
        ui->frame->window.setLimites();
        ui->frame->recalcularSCN();
    }
}

void MainWindow::setDeslocamento(){
    double valor = ui->spinBoxDesloc->value();
    if(valor>500){
        valor = 500;
    }
    this->deslocamentoWindow = valor;
}

//métodos da ação da window
void MainWindow::on_btn_cima_clicked(){
    ui->frame->window.setCentro_y(ui->frame->window.getCentro_y() + deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_baixo_clicked(){
     ui->frame->window.setCentro_y(ui->frame->window.getCentro_y() - deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_esquerda_clicked(){
    ui->frame->window.setCentro_x(ui->frame->window.getCentro_x() + deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_direita_clicked(){
    ui->frame->window.setCentro_x(ui->frame->window.getCentro_x() - deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_zoomMais_clicked(){
    ui->frame->window.setAltura(ui->frame->window.getAltura() + deslocamentoWindow);
    ui->frame->window.setLargura(ui->frame->window.getLargura() + deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_zoomMenos_clicked(){
    ui->frame->window.setAltura(ui->frame->window.getAltura() - deslocamentoWindow);
    ui->frame->window.setLargura(ui->frame->window.getLargura() - deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}


void MainWindow::on_btn_diagEsqCima_clicked(){
    ui->frame->window.setCentro_x(ui->frame->window.getCentro_x() - deslocamentoWindow);
    ui->frame->window.setCentro_y(ui->frame->window.getCentro_y() + deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_diagEsqBaixo_clicked(){
    ui->frame->window.setCentro_x(ui->frame->window.getCentro_x() - deslocamentoWindow);
    ui->frame->window.setCentro_y(ui->frame->window.getCentro_y() - deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_diagDirCima_clicked(){
    ui->frame->window.setCentro_x(ui->frame->window.getCentro_x() + deslocamentoWindow);
    ui->frame->window.setCentro_y(ui->frame->window.getCentro_y() + deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_diagDirBaixo_clicked(){
    ui->frame->window.setCentro_x(ui->frame->window.getCentro_x() + deslocamentoWindow);
    ui->frame->window.setCentro_y(ui->frame->window.getCentro_y() - deslocamentoWindow);
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_girarEsq_clicked(){;
    ui->frame->window.setAngulo(ui->frame->window.getAngulo()-10);
    //ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_girarDir_clicked(){
    ui->frame->window.setAngulo(ui->frame->window.getAngulo()+10);
    //ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

void MainWindow::on_btn_reset_clicked(){
    ui->frame->window.setCentro_x(0.0);
    ui->frame->window.setCentro_y(0.0);
    ui->frame->window.setAngulo(0.0);
    // DialogConfigWindow winConfig = DialogConfigWindow(this);
    // ui->frame->window.setAltura(winConfig.getAlturaDigitada());
    // ui->frame->window.setLargura(winConfig.getLarguraDigitada());
    ui->frame->window.setLimites();
    ui->frame->recalcularSCN();
}

MainWindow::~MainWindow()
{
    delete ui;
}







