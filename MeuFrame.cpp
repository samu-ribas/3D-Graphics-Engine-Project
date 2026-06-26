#include "MeuFrame.h"
#include "Ponto.h"
#include "Reta.h"
#include "Poligono.h"
#include "modelo3d.h"
#include <QPainter>
#include <QDebug>

MeuFrame::MeuFrame(QWidget *parent) : QFrame(parent), viewport(50.0, 50.0, 600.0, 350.0) {}

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

void MeuFrame::adicionarModelo3D( QString nome, QString caminhoRecurso){
    Modelo3D* modelo = Modelo3D::carregarOBJ(nome, caminhoRecurso);
    if(modelo == nullptr)
        return;

    Matriz rotacaoY = Matriz::gerarMatrizRy(180.0);
    modelo->aplicarTransformacao(rotacaoY);

    displayFile.append(modelo);
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
                    int larg_vp = this->viewport.getLargura();
                    int alt_vp  = this->viewport.getAltura();

                    if(larg_vp <= 0 || alt_vp <= 0 || viewport.getLargura()== 0 || viewport.getAltura() == 0){
                        return;
                    }

                    double x_scn = x / (larg_vp / 2.0);
                    double y_scn = y / (alt_vp / 2.0);

                    px = x_scn * (viewport.getLargura() / 2.0) + camera.getX();
                    py = y_scn * (viewport.getAltura() / 2.0) + camera.getY();
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

void MeuFrame::recalcularSCN()
{
    Matriz translacao = Matriz::gerarMatrizT(-camera.getX(), -camera.getY(), -camera.getZ());
    Matriz rotacao    = Matriz::gerarMatrizRz(-camera.getAngulo());
    this->mView = rotacao * translacao;

    this->mProj = Matriz::gerarMatrizPerspectiva(camera.getD());

    this->update();
}
void MeuFrame::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    //painter.setRenderHint(QPainter::Antialiasing); //fica mais bonito

    painter.translate(this->viewport.getXvp(), this->viewport.getYvp());

    for(Forma* df : std::as_const(displayFile)){
        df->desenhar(painter, this->mView, this->mProj, this->viewport, this->camera.getZoom());
    }

    QPen canetaVermelha(Qt::darkRed, 6);
    painter.setPen(canetaVermelha);

    double altura = this->viewport.getAltura();
    double largura = this->viewport.getLargura();

    painter.drawLine(0, 0, largura, 0);
    painter.drawLine(largura, 0, largura, altura);
    painter.drawLine(largura, altura, 0, altura);
    painter.drawLine(0, altura, 0, 0);
}


MeuFrame::~MeuFrame() {
    qDeleteAll(displayFile);
    displayFile.clear();
}