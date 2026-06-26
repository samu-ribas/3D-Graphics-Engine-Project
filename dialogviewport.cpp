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

double DialogViewport::getXDigitado() const {
    return this->x;
}

double DialogViewport::getYDigitado() const {
    return this->y;
}

void DialogViewport::setDisplay(double largAtual, double altAtual, double xAtual, double yAtual) {
    ui->lcdNumberLarg->display(largAtual);
    ui->lcdNumberAlt->display(altAtual);
    // ui->lcdNumberX->display(xAtual);
    // ui->lcdNumberY->display(yAtual);
}

void DialogViewport::setDimensoes() {
    double inputLargura = ui->lineEditLargura->text().toDouble();
    double inputAltura = ui->lineEditAltura->text().toDouble();
    // double inputX = ui->lineEditX->text().toDouble();
    // double inputY = ui->lineEditY->text().toDouble();

    if(inputLargura > 0.0 && inputAltura > 0.0 && inputLargura<=891 && inputAltura<=431.0){
        this->largura = inputLargura;
        this->altura = inputAltura;
        // this->x = inputX;
        // this->y = inputY;

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