#include "meuframe.h"
#include "Ponto.h"
#include <QPainter>
#include "Reta.h"
#include "Poligono.h"
#include "Matriz.h"
#include "janelagerenciavw.h"
//#include <QDebug>

MeuFrame::MeuFrame( QWidget *parent ) : QFrame( parent ) {
    JanelaViewportWindow *meu = new JanelaViewportWindow(this, this);
    meu->show();
}

void MeuFrame:: adicionarPonto( QString name, double x, double y ){
    Ponto *novo_ponto = new Ponto( name, x, y );
    displayFile.append( novo_ponto );
    novo_ponto->atualizarCoordenadaScn( transdormadaViewport );
    update();
}

void MeuFrame:: adicionarReta( QString name, double x1, double y1, double x2, double y2 ){
    Reta *nova_reta = new Reta( name, x1, y1, x2, y2 );
    displayFile.append( nova_reta );
    nova_reta->atualizarCoordenadaScn( transdormadaViewport );
    update();
}

void MeuFrame:: adicionarPoligono( QString name, std::list<Coordenada> pontos ){
    Poligono *novo_poligono = new Poligono( name, pontos );
    displayFile.append( novo_poligono );
    novo_poligono->atualizarCoordenadaScn( transdormadaViewport );
    update();
}

void MeuFrame::paintEvent( QPaintEvent *event ){
    QFrame::paintEvent( event );
    QPainter painter( this );

    // Se a caneta para desenhar a borda
    QPen caneta(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(caneta);

    // Desenha a borda da viewport (para debug)


    painter.drawRect(
        viewportAtiva->getMin().x,
        viewportAtiva->getMin().y,
        viewportAtiva->getLargura(),
        viewportAtiva->getAltura()
    );

    // Desenha todos os objetos
    for( Forma* df : std::as_const( displayFile ))
        df->desenhar( painter, *viewportAtiva);
}

void MeuFrame::transladarObjeto( QString n, double dx, double dy ){
    for( Forma* df : std::as_const( displayFile )){
        if( df->getNome().compare( n ) == 0 ){
            Matriz t = Matriz::gerarMatrizT( dx, dy );
            df->aplicarTransformacao( t, transdormadaViewport);
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
            df->aplicarTransformacao( composta, transdormadaViewport );
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
            df->aplicarTransformacao( composta, transdormadaViewport );
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
    //qDebug() << "Ola";
    if ( windowAtiva == nullptr || viewportAtiva == nullptr ) return;

    Janela   *window   = this->windowAtiva;
    Viewport *viewport = this->viewportAtiva;

    //double distorcao = (double)this->width() / (double)this->height();

    Matriz translacaoWindow = Matriz::gerarMatrizT( -window->getCentro() );

    Matriz escala =Matriz::gerarMatrizE(
        (viewport->getLargura()) / (window->getLargura()),
        (viewport->getAltura()) / (window->getAltura())
    );

    Matriz rotacaoWindow = Matriz::gerarMatrizR( -window->getAngulo() );

    //Matriz rotacaoViewport = Matriz::gerarMatrizR( viewport->getAngulo() );

    Matriz translacaoViewport = Matriz::gerarMatrizT( viewport->getCentro() );

    this->transdormadaViewport = translacaoViewport * rotacaoWindow * escala * translacaoWindow;
    this->transdormadaViewport.imprimir();

    for ( Forma* obj : std::as_const( displayFile )) {
        obj->atualizarCoordenadaScn( this->transdormadaViewport );
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