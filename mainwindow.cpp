#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->desenharPonto, &QPushButton::clicked, this, &MainWindow::processarDesenhoPonto);
    //connect(ui->scrollBarEspessura, &QSlider::valueChanged, ui->frame, &MeuFrame::atualizarEspessuraSelecionada);
    //connect(ui->frame, &MeuFrame::formaSelecionada, ui->scrollBarEspessura, &QSlider::setValue);

}

void MainWindow::processarDesenhoPonto(){
    int x = ui->inputX->text().toInt();
    int y = ui->inputY->text().toInt();
    //int espessura = ui->scrollBarEspessura->value();
    ui->frame->adicionarPonto(x, y);
}

MainWindow::~MainWindow()
{
    delete ui;
}
