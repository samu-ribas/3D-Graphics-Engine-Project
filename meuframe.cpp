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
    //QPen canetaDebug(Qt::white);
    //canetaDebug.setWidth(50);
    //painter.setPen(canetaDebug);
    for(Forma* forma : std::as_const(formas)){
        forma->desenhar(painter);
    }
}
/*
void MeuFrame::mousePressEvent(QMouseEvent *event){
    for (int i = formas.size() - 1; i >= 0; --i){
        if(formas[i]->contem(event->pos().x(), event->pos().y())){
            m_formaSelecionada = formas[i];
            m_arrastando = true;

            emit formaSelecionada(m_formaSelecionada->getEspessura());
            return;
        }
    }
    m_formaSelecionada = nullptr;
}


void MeuFrame::mouseMoveEvent(QMouseEvent *event){
    if(m_arrastando && m_formaSelecionada != nullptr){
        m_formaSelecionada->setPosicao(event->pos().x(), event->pos().y());
        update();
    }
}

void MeuFrame::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    m_arrastando = false;
}

void MeuFrame::atualizarEspessuraSelecionada(int novaEspessura) {
    if(m_formaSelecionada != nullptr){
        m_formaSelecionada->setEspessura(novaEspessura);
        update();
    }
}
*/
MeuFrame::~MeuFrame() {
    qDeleteAll(formas);
    formas.clear();
}
