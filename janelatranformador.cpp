#include "janelatranformador.h"
#include "ui_janelatranformador.h"
#include <QDebug>

JanelaTranformador::JanelaTranformador( QWidget *parent, MeuFrame *frame )
    : QMainWindow(parent)
    , ui(new Ui::JanelaTranformador)
{
    ui->setupUi(this);
    this->frame = frame;

    QVector<Forma*> *df = frame->getDisplayFile();
    //ui->formaBox->addItem( "Abobrinha" );
    setWindowFlag( Qt::Tool, true );

    int max = (*df).length();
    qDebug() << max;
    //if ( max == 0 ) { return; }
    for ( int i = 0; i < max; i++ )
    {
        //qDebug() << "sim";
        ui->formaBox->addItem( (*df)[i]->getNome() );
    }

    ui->widgetEscala->hide();
    ui->widgetTranslacao->hide();
    ui->widgetRotacao->hide();
}

void JanelaTranformador::on_botaoTranformar_pressed()
{
    QString nome = ui->formaBox->currentText();
    Forma* obj = frame->acharNome( nome );
    if ( obj == nullptr ) return;

    std::vector<double> initialCods = obj->getPos();

    Matriz tranfomacaoFinal = Matriz();

    Matriz origem = Matriz::gerarMatrizTranslacao(
        -initialCods.at(0), -initialCods.at(1)
        );

    Matriz posisaoOriginal = Matriz::gerarMatrizTranslacao(
        initialCods.at(0), initialCods.at(1)
        );

    if ( ui->checkBoxEscala->isChecked() )
    {

        double ex = ui->escalaX->value();
        double ey = ui->escalaY->value();
        Matriz escala = Matriz::gerarMatrizEscala( ex, ey );

        if ( ui->escalaCentroide->isChecked() )
        {
            std::vector<double> centroide = obj->getCentroide();

            Matriz origemCentroide = Matriz::gerarMatrizTranslacao( -centroide.at(0), -centroide.at(1) );
            Matriz voltaOriginalCentroide = Matriz::gerarMatrizTranslacao( centroide.at(0), centroide.at(1) );

            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, origemCentroide );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, escala );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, voltaOriginalCentroide );
        }
        else
        {
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, origem );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, escala );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, posisaoOriginal );
        }
    }

    if ( ui->checkBoxRotacao->isChecked() )
    {
        double angulo = ui->rotacaoAngulo->value();
        Matriz rotacao = Matriz::gerarMatrizRotacao( angulo );

        //double eixoX = 0;
        //double eixoY = 0;
        if ( ui->rotacaoCentoride->isChecked() )
        {
            std::vector<double> centroide = obj->getCentroide();

            Matriz origemCentroide = Matriz::gerarMatrizTranslacao( -centroide.at(0), -centroide.at(1) );
            Matriz voltaOriginalCentroide = Matriz::gerarMatrizTranslacao( centroide.at(0), centroide.at(1) );

            //eixoX = ui->rotacaoEixoX->value();
            //eixoY = ui->rotacaoEixoY->value();

            //Matriz eixo = Matriz::gerarMatrizTranslacao( eixoX, eixoY );
            //Matriz volta = Matriz::gerarMatrizTranslacao( -eixoX, -eixoY );

            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, origemCentroide );
            //tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, eixo );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, rotacao );
            //tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, volta );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, voltaOriginalCentroide );

        }
        else if ( ui->rotacaoEspecifico->isChecked() )
        {
            double eixoX = ui->rotacaoEixoX->value();
            double eixoY = ui->rotacaoEixoY->value();

            Matriz eixo = Matriz::gerarMatrizTranslacao( -eixoX, -eixoY );
            Matriz volta = Matriz::gerarMatrizTranslacao( eixoX, eixoY );

            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, eixo );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, rotacao );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, volta );
        }
        else
        {
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, origem );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, rotacao );
            tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, posisaoOriginal );
        }

    }

    if ( ui->checkBoxTraslacao->isChecked() )
    {
        double tx = ui->translacaoX->value();
        double ty = ui->translacaoY->value();
        Matriz translacao = Matriz::gerarMatrizTranslacao( tx, ty );

        tranfomacaoFinal = Matriz::multiplicar( tranfomacaoFinal, translacao );
    }

    obj->transfomar( tranfomacaoFinal );
    (*frame).update();
}

void JanelaTranformador::on_escalaSlider_sliderPressed()
{
    this->sliderEscalaPressionado = true;
}

void JanelaTranformador::on_escalaSlider_sliderReleased()
{
    this->sliderEscalaPressionado = false;
}

void JanelaTranformador::on_escalaSlider_valueChanged( int value )
{

    QString nome = ui->formaBox->currentText();
    Forma* obj = frame->acharNome( nome );
    if ( obj == nullptr ) return;

    std::vector<double> posisaoOriginal;
    if ( ui->escalaCentroide->isChecked() )
    {
        posisaoOriginal = obj->getCentroide();
    }
    else
    {
        posisaoOriginal = obj->getPos();
    }

    Matriz tranfomacaoFinal = Matriz();

    Matriz origem = Matriz::gerarMatrizTranslacao(
        -posisaoOriginal.at(0), -posisaoOriginal.at(1)
        );

    Matriz translacaoDeVolta = Matriz::gerarMatrizTranslacao(
        posisaoOriginal.at(0), posisaoOriginal.at(1)
        );
}

JanelaTranformador::~JanelaTranformador()
{
    delete ui;
}




