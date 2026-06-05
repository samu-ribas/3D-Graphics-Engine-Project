#include "dialogconfigwindow.h"
#include "ui_dialogconfigwindow.h"
#include <QMessageBox>

DialogConfigWindow::DialogConfigWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogConfigWindow)
{
    ui->setupUi(this);
    connect(ui->btnAplicar, &QPushButton::pressed, this, &DialogConfigWindow::setDimensoes);
    connect(ui->btnCancelar, &QPushButton::pressed, this, &DialogConfigWindow::cancelar);
}

double DialogConfigWindow::getLarguraDigitada() const{
    return this->largura;
}

double DialogConfigWindow::getAlturaDigitada() const{
    return this->altura;
}

void DialogConfigWindow::setDisplay(double largAtual, double altAtual) {
    ui->lcdNumberLarg->display(largAtual);
    ui->lcdNumberAlt->display(altAtual);
}

void DialogConfigWindow::setDimensoes() {
    double inputLargura = ui->lineEditLargura->text().toDouble();
    double inputAltura = ui->lineEditAltura->text().toDouble();

    if(inputLargura > 0.0 && inputAltura > 0.0 && inputLargura<=891 && inputAltura<=431.0){
        this->largura = inputLargura;
        this->altura = inputAltura;

        ui->lineEditLargura->clear();
        ui->lineEditAltura->clear();

        this->accept();
    } else {
        QMessageBox::warning(this, "Erro: Dimensões inválidas.", "Dimensão máx: 891x431");
    }
}
void DialogConfigWindow::cancelar(){
    this->reject();
}

DialogConfigWindow::~DialogConfigWindow()
{
    delete ui;
}
