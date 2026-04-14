#include "meuframe.h"
#include "ponto.h"
#include <QPainter>
#include <QDebug>

MeuFrame::MeuFrame(QWidget *parent) : QFrame(parent) {}



void MeuFrame:: adicionarPonto(int x, int y){
    formas.append(new Ponto(x,y));
    update();
}


void MeuFrame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    qDebug() << "[Renderização] PaintEvent chamado. Endereço da janela:" << this << "| Formas na lista:" << formas.size();

    for(Forma* forma : std::as_const(formas))
        forma->desenhar(painter);

}

MeuFrame::~MeuFrame() {
    qDeleteAll(formas);
    formas.clear();
}
