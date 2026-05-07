#include "janelagerenciavw.h"
#include "ui_janelagerenciavw.h"
#include <QDebug>

JanelaViewportWindow::JanelaViewportWindow( QWidget *parent, MeuFrame *frame )
    : QMainWindow( parent)
    , ui( new Ui::JanelaViewportWindow )
    , frame( frame )
{
    ui->setupUi(this);
    qDebug() << "Ola mundo!";
    // In your widget's constructor
    //this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);
    this->setWindowFlags( Qt::Tool | Qt::WindowMinMaxButtonsHint );
    //setWindowFlags(Qt::Tool);

    Viewport *padraoV = new Viewport(
        "Padrao",
        450, 225,
        900,
        450
    );
    frame->setViewportAtiva( padraoV );
    listaViewport.push_back( padraoV );
    atualizar_display_valores_viewport(padraoV);


    Janela *padraoW = new Janela(
        "Padrao",
        450, 225,
        900,
        450
        );
    frame->setJanelaAtiva( padraoW );
    listaJanela.push_back( padraoW );
    ui->windowAtivador->addItem( "Padrao" );
    atualizar_display_valores_window(padraoW);

    padraoW = new Janela(
        "CemPorCem",
        50, 50,
        100,
        100
        );
    listaJanela.push_back( padraoW );
    ui->windowAtivador->addItem( "CemPorCem" );
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

    //qDebug() << "AHHHH";
    frame->setJanelaAtiva( novaJanela );
    atualizar_display_valores_window( novaJanela );
}

void JanelaViewportWindow::on_viewportAtivador_currentTextChanged(const QString &arg1)
{
    Viewport *novaViewport = buscar_viewport(arg1);

    if (novaViewport == nullptr) return;

    frame->setViewportAtiva( novaViewport );
    atualizar_display_valores_viewport( novaViewport );
}

void JanelaViewportWindow::atualizar_display_valores_window(Janela *window)
{
    ui->labelWindowCentro ->setText(tr("Centro: %1, %2").arg( window->getCentro().x ).arg( window->getCentro().y ));
    ui->labelWindowLargura->setText(tr("Largura: %1")   .arg( window->getLargura()));
    ui->labelWindowAltura ->setText(tr("Altura: %1")    .arg( window->getAltura()));
    ui->labelWindowAngulo ->setText(tr("Angulo: %1º")   .arg( window->getAngulo()));
}

void JanelaViewportWindow::atualizar_display_valores_viewport(Viewport *viewport)
{
    ui->labelViewportCentro ->setText(tr("Centro: %1, %2").arg( viewport->getCentro().x ).arg( viewport->getCentro().y ));
    ui->labelViewportLargura->setText(tr("Largura: %1")   .arg( viewport->getLargura()));
    ui->labelViewportAltura ->setText(tr("Altura: %1")    .arg( viewport->getAltura()));
}



