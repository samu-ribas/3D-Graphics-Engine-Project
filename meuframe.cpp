#include "meuframe.h"
#include "Ponto.h"
#include <QPainter>
#include <QDebug>
#include "forma.h"

MeuFrame::MeuFrame(QWidget *parent) : QFrame(parent) {}



void MeuFrame:: adicionarPonto(QString name, double x, double y){
    displayFile.append(new Ponto(name ,x ,y));
    update();
}

void MeuFrame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    for(Forma* df : std::as_const(displayFile))
        df->desenhar(painter);

}

MeuFrame::~MeuFrame() {
    qDeleteAll(displayFile);
    displayFile.clear();
}