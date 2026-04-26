#include "meuframe.h"
#include "Ponto.h"
#include <QPainter>
#include "forma.h"
#include "Reta.h"
#include "Poligono.h"

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

Forma* MeuFrame::acharNome( QString nome )
{
    int tam = displayFile.length();
    for ( int i = 0; i < tam; i++ )
    {
        //if ( QString::compare( displayFile[i]->getNome(), nome ) )
        if ( displayFile[i]->getNome() == nome )
            return displayFile[i];
    }
    return nullptr;
}

QVector<Forma*> *MeuFrame::getDisplayFile()
{
    return &displayFile;
}

MeuFrame::~MeuFrame() {
    qDeleteAll(displayFile);
    displayFile.clear();
}