#include "meuframe.h"
#include "Ponto.h"
#include "Reta.h"
#include "Poligono.h"
#include "Matriz.h"
#include "forma.h"
#include <cmath>
#include <QPainter>

MeuFrame::MeuFrame(QWidget *parent) : QFrame(parent) {}

void MeuFrame:: adicionarPonto(QString name, double x, double y){
    displayFile.append(new Ponto(name ,x ,y));
    recalcularSCN();
}

void MeuFrame:: adicionarReta(QString name, double x1, double y1, double x2, double y2){
    displayFile.append(new Reta(name, x1,y1,x2,y2));
    recalcularSCN();
}

void MeuFrame:: adicionarPoligono(QString name, std::list<Coordenada> pontos){
    displayFile.append(new Poligono(name, pontos));
    recalcularSCN();
}

void MeuFrame::transladarObjeto(QString n, double dx, double dy){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome().compare(n) == 0){
            Matriz t = Matriz::gerarMatrizT(dx, dy);
            df->aplicarTransformacao(t);
            break;
        }
    }
    recalcularSCN();
}

void MeuFrame::escalarObjeto(QString n, double sx, double sy){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome().compare(n) == 0){
            Coordenada centro = df->getCentroide();
            Matriz mToOrigin = Matriz::gerarMatrizT(-centro.x_wc, -centro.y_wc);
            Matriz escala = Matriz::gerarMatrizE(sx, sy);
            Matriz mToReturn = Matriz::gerarMatrizT(centro.x_wc, centro.y_wc);

            Matriz composta = mToReturn * escala * mToOrigin;
            df->aplicarTransformacao(composta);
            break;
        }
    }
    recalcularSCN();
}

void MeuFrame::rotacionarObjeto(QString n, double angulo, double x, double y, bool usarCentroide){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome() == n){
            double px, py;

            //define quem é o pivô da transformação
            if(usarCentroide){
                Coordenada centro = df->getCentroide();
                px = centro.x_wc;
                py = centro.y_wc;
            }else{
                px = x;
                py = y;
            }
            Matriz mToOrigin = Matriz::gerarMatrizT(-px, -py);
            Matriz mRotation = Matriz::gerarMatrizR(-angulo);
            Matriz mToReturn = Matriz::gerarMatrizT(px, py);

            Matriz composta = mToReturn * mRotation * mToOrigin;
            df->aplicarTransformacao(composta);
            break;
        }
    }
    //qDebug()<< this->bit.b1.to_string();
    recalcularSCN();
}

bool MeuFrame::contemObjeto(const QString& nome) const {
    for(Forma* df : std::as_const(displayFile)) {
        if(df->getNome() == nome)
            return true;
    }
    return false;
}

void MeuFrame::recalcularSCN(){
    Matriz mTranslacao;
    Matriz mRotacao;
    Matriz mEscala;

    double distorcao = (double)this->width() / (double)this->height();

    mTranslacao.m[0][2] = -window.centro_x;
    mTranslacao.m[1][2] = -window.centro_y;

    double rad = -window.angulo * (M_PI / 180.0);
    mRotacao.m[0][0] = cos(rad);
    mRotacao.m[0][1] = -sin(rad);
    mRotacao.m[1][0] = sin(rad);
    mRotacao.m[1][1] = cos(rad);
    mEscala.m[0][0] = (2.0 / window.largura) / distorcao;
    mEscala.m[1][1] = 2.0 / window.altura;

    Matriz mCamera = mEscala * mRotacao * mTranslacao;

    for(Forma* forma : std::as_const(displayFile)){
        for(Coordenada& c : forma->getCoordenada()){
            Coordenada temp = mCamera * c;
            c.x_scn = temp.x_wc;
            c.y_scn = temp.y_wc;
        }
    }
    this->update();
}

void MeuFrame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    for(Forma* df : std::as_const(displayFile)){
        df->desenhar(painter, this->width(), this->height()); //passo tambem as dimensões da Viewport em pixels naquele exato frame
    }
}

MeuFrame::~MeuFrame() {
    qDeleteAll(displayFile);
    displayFile.clear();
}