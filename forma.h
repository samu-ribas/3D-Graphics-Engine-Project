#ifndef FORMA_H
#define FORMA_H

#include <QPainter>
#include <QVector>
#include <QPoint>

#include "window.h"
#include "coordenada.h"

class Matriz;



//conjunto de constantes
enum class TipoForma{PONTO, RETA, POLIGONO};

class Forma
{
protected:
    QString nome;
    TipoForma o_tipo;
    std::list<Coordenada> p;
    Forma(QString n, TipoForma tipo) : nome(n), o_tipo(tipo){}
    Linha *recorte( Coordenada *p1, Coordenada *p2, Viewport viewport) {
        Linha *l = new Linha({{p1->xScn, p1->yScn}, {p2->xScn, p2->yScn}});
        //qDebug() << "1";
        Coordenada *novoPonto1 = nullptr;
        Coordenada *novoPonto2 = nullptr;

        if (p1->pos.none() || p2->pos.none()) {
            //qDebug() << "Um para dentro.";
            if (p1->pos.none()) {
                novoPonto1 = new Coordenada(p1->xScn, p1->yScn);
            }
            else {
                novoPonto1 = new Coordenada(p2->xScn, p2->yScn);
            }

            novoPonto2 = Linha::calcularIntercecao(*l, viewport.getTopo());
            //qDebug() << "Topo.";
            if (novoPonto2 == nullptr) {
                novoPonto2 = Linha::calcularIntercecao(*l, viewport.getFundo());
                //qDebug() << "Fundo.";
                if (novoPonto2 == nullptr) {
                    novoPonto2 = Linha::calcularIntercecao(*l, viewport.getDireita());
                    //qDebug() << "Direita.";
                    if (novoPonto2 == nullptr) {
                        novoPonto2 = Linha::calcularIntercecao(*l, viewport.getEsquerda());
                        //qDebug() << "Esquerda.";
                    }
                }
            }
        }
        else {
            //qDebug() << "Ambos para fora.";
            novoPonto1 = Linha::calcularIntercecao(*l, viewport.getTopo());
            //qDebug() << "Topo.";
            if (novoPonto1 == nullptr) {
                novoPonto1 = Linha::calcularIntercecao(*l, viewport.getFundo());
                //qDebug() << "Fundo.";
                if (novoPonto1 == nullptr) {
                    novoPonto1 = Linha::calcularIntercecao(*l, viewport.getDireita());
                    //qDebug() << "Direita.";
                    if (novoPonto1 == nullptr) {
                        novoPonto1 = Linha::calcularIntercecao(*l, viewport.getEsquerda());
                        //qDebug() << "Esquerda.";
                    }
                }
            }

            novoPonto2 = Linha::calcularIntercecao(*l, viewport.getEsquerda());
            //qDebug() << "Esquerda.";
            if (novoPonto2 == nullptr) {
                novoPonto2 = Linha::calcularIntercecao(*l, viewport.getDireita());
                //qDebug() << "Direita.";
                if (novoPonto2 == nullptr) {
                    novoPonto2 = Linha::calcularIntercecao(*l, viewport.getFundo());
                    //qDebug() << "Fundo.";
                    if (novoPonto2 == nullptr) {
                        novoPonto2 = Linha::calcularIntercecao(*l, viewport.getTopo());
                        //qDebug() << "Topo.";
                    }
                }
            }
        }
        if (novoPonto1 == nullptr || novoPonto2 == nullptr)
            return nullptr;
        return new Linha({*novoPonto1, *novoPonto2});
    }

public:

    virtual ~Forma() {}

    virtual void desenhar(QPainter &painter, Viewport viewport) = 0;
    virtual void aplicarTransformacao(const Matriz& m) = 0;
    virtual void atualizarCoordenadaScn(const Matriz& m, Janela window) = 0;

    Coordenada getCentroide() const { // retorna o centroide do objeto
        double cx = 0.0, cy = 0.0;
        if(p.empty())
            return {0.0, 0.0};

        for (const auto& pt : p){
            cx += pt.x;
            cy += pt.y;
        }
        return {cx / p.size(), cy / p.size()};
    }

    QString getNome() const { return nome; }
    TipoForma getTipo() const { return o_tipo; }

};

#endif // FORMA_H