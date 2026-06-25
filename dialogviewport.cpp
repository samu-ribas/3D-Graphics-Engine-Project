#include "dialogviewport.h"
#include "ui_dialogviewport.h"
#include <QMessageBox>

DialogViewport::DialogViewport(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogViewport)
{
    ui->setupUi(this);
    ui->setupUi(this);
    connect(ui->btnAplicar, &QPushButton::pressed, this, &DialogViewport::setDimensoes);
    connect(ui->btnCancelar, &QPushButton::pressed, this, &DialogViewport::cancelar);
}

double DialogViewport::getLarguraDigitada() const{
    return this->largura;
}

double DialogViewport::getAlturaDigitada() const{
    return this->altura;
}

void DialogViewport::setDisplay(double largAtual, double altAtual) {
    ui->lcdNumberLarg->display(largAtual);
    ui->lcdNumberAlt->display(altAtual);
}

void DialogViewport::setDimensoes() {
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

void DialogViewport::cancelar(){
    this->reject();
}
DialogViewport::~DialogViewport()
{
    delete ui;
}
