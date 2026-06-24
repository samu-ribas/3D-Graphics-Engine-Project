#include "MeuFrame.h"
#include "Ponto.h"
#include "Reta.h"
#include "Poligono.h"
#include "modelo3d.h"
#include <cmath>
#include <QPainter>
#include <QDebug>

MeuFrame::MeuFrame(QWidget *parent) : QFrame(parent), window(0,0,0,0) {}

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

void MeuFrame::adicionarModelo3D( QString nome, QString caminhoRecurso) {
    Modelo3D* modelo = Modelo3D::carregarOBJ(nome, caminhoRecurso);
    if(modelo == nullptr){
        qDebug() << "Falha ao carregar OBJ";
        return;
    }
    Matriz t = Matriz::gerarMatrizT(window.getCentro_x(), window.getCentro_y(), 0.0);
    modelo->aplicarTransformacao(t);

    displayFile.append(modelo);
    qDebug() << "Modelo carregado com sucesso";
    recalcularSCN();
}

void MeuFrame::transladarObjeto(QString n, double dx, double dy, double dz){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome() == n){
            Matriz t = Matriz::gerarMatrizT(dx, dy, dz);
            df->aplicarTransformacao(t);
            break;
        }
    }
}

void MeuFrame::escalarObjeto(QString n, double sx, double sy, double sz){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome() == n){
            Coordenada centro = df->getCentroide();

            Matriz mToOrigin = Matriz::gerarMatrizT(-centro.x_wc, -centro.y_wc, -centro.z_wc);
            Matriz escala = Matriz::gerarMatrizE(sx, sy, sz);
            Matriz mToReturn = Matriz::gerarMatrizT(centro.x_wc, centro.y_wc, centro.z_wc);

            Matriz composta = mToReturn * escala * mToOrigin;
            df->aplicarTransformacao(composta);
            break;
        }
    }
}

void MeuFrame::rotacionarObjeto(QString n, double angulo, double x, double y, double z, char eixo, bool usarCentroide, bool usarCoordWindow){
    for(Forma* df : std::as_const(displayFile)){
        if(df->getNome() == n){
            double px, py, pz;

            if(usarCentroide){
                Coordenada centro = df->getCentroide();
                px = centro.x_wc;
                py = centro.y_wc;
                pz = centro.z_wc; // Puxa o Z do centroide
            }else{
                if(usarCoordWindow){
                    px = x;
                    py = y;
                    pz = z;
                }else{
                    int larg_vp = this->width() - this->window.getMargem() * 2;
                    int alt_vp  = this->height() - this->window.getMargem() * 2;

                    if(larg_vp <= 0 || alt_vp <= 0 || window.getLargura()== 0 || window.getAltura() == 0){
                        return;
                    }

                    double x_scn = x / (larg_vp / 2.0);
                    double y_scn = y / (alt_vp / 2.0);

                    px = x_scn * (window.getLargura() / 2.0) + window.getCentro_x();
                    py = y_scn * (window.getAltura() / 2.0) + window.getCentro_y();
                    pz = z;
                }
            }

            Matriz mToOrigin = Matriz::gerarMatrizT(-px, -py, -pz);

            Matriz mRotation;
            if(eixo == 'X'){
                mRotation = Matriz::gerarMatrizRx(angulo);
            }else if(eixo == 'Y'){
                mRotation = Matriz::gerarMatrizRy(angulo);
            }else
                mRotation = Matriz::gerarMatrizRz(angulo);

            Matriz mToReturn = Matriz::gerarMatrizT(px, py, pz);

            Matriz composta = mToReturn * mRotation * mToOrigin;
            df->aplicarTransformacao(composta);
            break;
        }
    }
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

    mTranslacao.m[0][3] = -window.getCentro_x();
    mTranslacao.m[1][3] = -window.getCentro_y();
    mTranslacao.m[2][3] = 0.0; // câmera estática no eixo Z por enquanto

    double rad = -window.getAngulo() * (M_PI/180.0);
    mRotacao.m[0][0] = cos(rad);
    mRotacao.m[0][1] = -sin(rad);
    mRotacao.m[1][0] = sin(rad);
    mRotacao.m[1][1] = cos(rad);
    mRotacao.m[2][2] = 1.0;

    double zoom = window.getZoomViewport();
    mEscala.m[0][0] = (2.0/window.getLargura()) * zoom;
    mEscala.m[1][1] = (2.0/window.getAltura()) * zoom;
    mEscala.m[2][2] = 1.0;

    this->mCameraAtual = mEscala * mRotacao * mTranslacao;
    this->update();
}


void MeuFrame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    double altura = this->window.getAltura();
    double largura = this->window.getLargura();
    int x_canto = (this->width() - largura ) / 2;
    int y_canto = (this->height() - altura) / 2;

    //move a origem para esse canto centralizad
    painter.translate(x_canto, y_canto);

    for(Forma* df : std::as_const(displayFile)){
        df->desenhar(painter, this->mCameraAtual, this->window);
    }

    QPen canetaVermelha(Qt::darkRed, 6);
    painter.setPen(canetaVermelha);

    painter.drawLine(0, 0, largura, 0);
    painter.drawLine(largura, 0, largura, altura);
    painter.drawLine(largura, altura, 0, altura);
    painter.drawLine(0, altura, 0, 0);
}

MeuFrame::~MeuFrame() {
    qDeleteAll(displayFile);
    displayFile.clear();
}