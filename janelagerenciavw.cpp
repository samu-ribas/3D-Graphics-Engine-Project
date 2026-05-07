#include "janelagerenciavw.h"
#include "ui_janelagerenciavw.h"
#include <QDebug>

JanelaViewportWindow::JanelaViewportWindow( QWidget *parent, MeuFrame *frame )
    : QMainWindow( parent)
    , ui( new Ui::JanelaViewportWindow )
    , frame( frame )
{
    ui->setupUi(this);
    qDebug() << "AHHHH";
    // In your widget's constructor
    //this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);
    this->setWindowFlags( Qt::Tool | Qt::WindowMinMaxButtonsHint );
    //setWindowFlags(Qt::Tool);

    Viewport *padraoV = new Viewport(
        "Padrao",
        frame->width() / 2,
        frame->height() / 2,
        frame->width(),
        frame->height()
    );
    frame->setViewportAtiva( padraoV );
    listaViewport.push_back( padraoV );
    ui->viewportAtivador->addItem( "Padrão" );

    Janela *padraoW = new Janela(
        "Padrao",
        frame->width() / 2,
        frame->height() / 2,
        frame->width(),
        frame->height()
        );
    frame->setViewportAtiva( padraoW );
    listaViewport.push_back( padraoW );
    ui->viewportAtivador->addItem( "Padrão" );
}

JanelaViewportWindow::~JanelaViewportWindow() {
    delete ui;
}

void JanelaViewportWindow::on_criarViewport_pressed() {
    QString nome = ui->viewportNome->text();
    if ( nome == "" ) return;
    if ( buscar_window( nome ) != nullptr ) return;

    double altura = ui->viewportAltura->value();
    double largura = ui->viewportLargura->value();
    double x = ui->viewportX->value();
    double y = ui->viewportY->value();

    listaViewport.push_back(new Viewport( nome, x, y, largura, altura ));
    ui->viewportAtivador->addItem( nome );
    ui->viewportNome->clear();
}

void JanelaViewportWindow::on_criarWindow_pressed() {
    QString nome = ui->windowNome->text();
    if ( nome == "" ) return;
    if ( buscar_viewport( nome ) != nullptr ) return;

    double altura = ui->windowAltura->value();
    double largura = ui->windowLargura->value();
    double x = ui->windowX->value();
    double y = ui->windowY->value();

    Janela *novaJanela = new Janela( nome, x, y, largura, altura );
    listaJanela.push_back( novaJanela );
    if ( frame->hasJanelaAtiva() == false )
    {
        frame->setJanelaAtiva( novaJanela );
    }
    ui->windowAtivador->addItem( nome );
    ui->windowNome->clear();
}

Viewport *JanelaViewportWindow::buscar_viewport( QString nome)
{
    for ( Viewport* obj : std::as_const( listaViewport )) {
        if ( obj->getNome() == nome ) return obj;
    }
    return nullptr;
}

Janela *JanelaViewportWindow::buscar_window( QString nome)
{
    for ( Janela* obj : std::as_const( listaJanela )) {
        if ( obj->getNome() == nome ) return obj;
    }
    return nullptr;
}

void JanelaViewportWindow::on_windowAtivador_currentTextChanged(const QString &arg1)
{
    Janela *novaJanela = buscar_window(arg1);

    if (novaJanela == nullptr) return;

    listaJanela.push_back( novaJanela );
    frame->setJanelaAtiva( novaJanela );
}

