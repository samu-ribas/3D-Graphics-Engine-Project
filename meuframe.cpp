#include "meuframe.h"
#include "Ponto.h"
#include <QPainter>
#include "Reta.h"
#include "Poligono.h"
#include "Matriz.h"

MeuFrame::MeuFrame(QWidget *parent) : QFrame(parent) {}

void MeuFrame:: adicionarPonto(QString name, double x, double y){
    displayFile.append(new Ponto(name ,x ,y));
    update();
}

void MeuFrame:: adicionarReta(QString name, double x1, double y1, double x2, double y2){
    displayFile.append(new Reta(name, x1,y1,x2,y2));
    update();
}

void MeuFrame:: adicionarPoligono(QString name, std::list<Coordenada> pontos){
    displayFile.append(new Poligono(name, pontos));    
    update();
}

void MeuFrame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    for(Forma* df : std::as_const(displayFile))
        df->desenhar(painter);
}

void MeuFrame::transladarObjeto(QString n, double dx, double dy){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome().compare(n) == 0){
            Matriz t = Matriz::gerarMatrizT(dx, dy);
            df->aplicarTransformacao(t);
            break;
        }
    }
    this->update();
}

void MeuFrame::escalarObjeto(QString n, double sx, double sy){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome().compare(n) == 0){
            Coordenada centro = df->getCentroide();
            Matriz mToOrigin = Matriz::gerarMatrizT(-centro.x, -centro.y);
            Matriz escala = Matriz::gerarMatrizE(sx, sy);
            Matriz mToReturn = Matriz::gerarMatrizT(centro.x, centro.y);

            Matriz composta = mToReturn * escala * mToOrigin;
            df->aplicarTransformacao(composta);
            break;
        }
    }
    this->update();
}

void MeuFrame::rotacionarObjeto(QString n, double angulo){
    for(Forma* df:std::as_const(displayFile)){
        if(df->getNome().compare(n) == 0){
            Coordenada centro = df->getCentroide();
            Matriz mToOrigin = Matriz::gerarMatrizT(-centro.x, -centro.y);
            Matriz mRotation = Matriz::gerarMatrizR(angulo);
            Matriz mToReturn = Matriz::gerarMatrizT(centro.x, centro.y);

            Matriz composta = mToReturn * mRotation * mToOrigin;

            df->aplicarTransformacao(composta);
            break;
        }
    }
    this->update();
}

bool MeuFrame::contemObjeto(const QString& nome) const {
    for(Forma* df : std::as_const(displayFile)) {
        if(df->getNome() == nome) {
            return true;
        }
    }
    return false;
}

MeuFrame::~MeuFrame() {
    qDeleteAll(displayFile);
    displayFile.clear();
}