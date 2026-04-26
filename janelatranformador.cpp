#include "janelatranformador.h"
#include "ui_janelatranformador.h"
#include <QDebug>

JanelaTranformador::JanelaTranformador( QWidget *parent, QVector<Forma*> *df )
    : QMainWindow(parent)
    , ui(new Ui::JanelaTranformador)
{
    ui->setupUi(this);
    this->df = df;

    //ui->formaBox->addItem( "Abobrinha" );

    int max = (*df).length();
    qDebug() << max;
    //if ( max == 0 ) { return; }
    for ( int i = 0; i < max; i++ )
    {
        //qDebug() << "sim";
        ui->formaBox->addItem( (*df)[i]->getNome() );
    }
}

void JanelaTranformador::on_botaoTranformar_pressed()
{
    if ( ui->checkBoxEscala->isChecked() )
    {

    }
}

JanelaTranformador::~JanelaTranformador()
{
    delete ui;
}



