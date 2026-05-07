#include "meuframe.h"
#include "Ponto.h"
#include <QPainter>
#include "Reta.h"
#include "Poligono.h"
#include "Matriz.h"
#include "janelagerenciavw.h"
//#include <QDebug>

MeuFrame::MeuFrame( QWidget *parent ) : QFrame( parent ) {
    JanelaViewportWindow *ahhhh = new JanelaViewportWindow(this, this);
    ahhhh->show();

}

void MeuFrame:: adicionarPonto( QString name, double x, double y ){
    displayFile.append( new Ponto( name, x, y ));
    update();
}

void MeuFrame:: adicionarReta( QString name, double x1, double y1, double x2, double y2 ){
    displayFile.append( new Reta( name, x1, y1, x2, y2 ));
    update();
}

void MeuFrame:: adicionarPoligono( QString name, std::list<Coordenada> pontos ){
    displayFile.append( new Poligono( name, pontos ));
    update();
}

void MeuFrame::paintEvent( QPaintEvent *event ){
    QFrame::paintEvent( event );
    QPainter painter( this );

    for( Forma* df : std::as_const( displayFile ))
        df->desenhar( painter );
}

void MeuFrame::transladarObjeto( QString n, double dx, double dy ){
    for( Forma* df : std::as_const( displayFile )){
        if( df->getNome().compare( n ) == 0 ){
            Matriz t = Matriz::gerarMatrizT( dx, dy );
            df->aplicarTransformacao( t );
            break;
        }
    }
    this->update();
}

void MeuFrame::escalarObjeto( QString n, double sx, double sy ){
    for( Forma* df : std::as_const( displayFile )){
        if( df->getNome().compare( n ) == 0 ){
            Coordenada centro = df->getCentroide();
            Matriz mToOrigin = Matriz::gerarMatrizT( -centro.x, -centro.y );
            Matriz escala = Matriz::gerarMatrizE( sx, sy );
            Matriz mToReturn = Matriz::gerarMatrizT( centro.x, centro.y );

            Matriz composta = mToReturn * escala * mToOrigin;
            df->aplicarTransformacao( composta );
            break;
        }
    }
    this->update();
}

void MeuFrame::rotacionarObjeto( QString n, double angulo, double x, double y, bool usarCentroide ){
    for( Forma* df : std::as_const( displayFile )){
        if( df->getNome() == n ){
            double px, py;

            //define quem é o pivô da transformação
            if( usarCentroide ){
                Coordenada centro = df->getCentroide();
                px = centro.x;
                py = centro.y;
            }else{
                px = x;
                py = y;
            }
            Matriz mToOrigin = Matriz::gerarMatrizT( -px, -py );
            Matriz mRotation = Matriz::gerarMatrizR( angulo );
            Matriz mToReturn = Matriz::gerarMatrizT( px, py );

            Matriz composta = mToReturn * mRotation * mToOrigin;
            df->aplicarTransformacao( composta );
            break;
        }
    }
    this->update();
}

bool MeuFrame::contemObjeto( const QString& nome ) const {
    for( Forma* df : std::as_const( displayFile )) {
        if( df->getNome() == nome ) {
            return true;
        }
    }
    return false;
}

void MeuFrame::atualizarTransformada() {
    if ( windowAtiva == nullptr || viewportAtiva == nullptr ) return;

    Janela   *window   = this->windowAtiva;
    Viewport *viewport = this->viewportAtiva;

    //double distorcao = (double)this->width() / (double)this->height();

    Matriz translacaoWindow = Matriz::gerarMatrizT( -window->getCentro() );

    /*Matriz escala = Matriz::gerarMatrizE(
        ( window->getLargura() ) / ( viewport->getLargura() ),
        ( window->getAltura() ) / ( viewport->getAltura() )
    );*/

   //Matriz rotacao = Matriz::gerarMatrizR( window->getAngulo() );

    //Matriz translacaoViewport = Matriz::gerarMatrizT( viewport->getCentro() );

    //transdormadaViewport = translacaoWindow * escala * translacaoViewport;
    transdormadaViewport = translacaoWindow;

    for ( Forma* obj : std::as_const( displayFile )) {
        obj->atualizarCoordenadaScn( transdormadaViewport );
    }
    this->update();
}

void MeuFrame::setJanelaAtiva( Janela *novaJanela ) {
    if ( novaJanela == this->windowAtiva ) return;

    this->windowAtiva = novaJanela;
    atualizarTransformada();
}

void MeuFrame::setViewportAtiva( Viewport *novaViewport ) {
    if ( novaViewport == this->viewportAtiva ) return;

    this->viewportAtiva = novaViewport;
    atualizarTransformada();
}

bool MeuFrame::hasJanelaAtiva() {
    if ( this->windowAtiva != nullptr ) return true;
    return false;
}
bool MeuFrame::hasViewportAtiva() {
    if ( this->viewportAtiva != nullptr ) return true;
    return false;
}

MeuFrame::~MeuFrame() {
    qDeleteAll( displayFile );
    displayFile.clear();
}