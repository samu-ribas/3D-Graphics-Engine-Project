#ifndef JANELATRANFORMADOR_H
#define JANELATRANFORMADOR_H

#include <QMainWindow>
#include "meuframe.h"
namespace Ui {
class JanelaTranformador;
}

class JanelaTranformador : public QMainWindow
{
    Q_OBJECT

public:
    explicit JanelaTranformador(QWidget *parent = nullptr, MeuFrame *frame = nullptr);
    ~JanelaTranformador();

private slots:
    void on_botaoTranformar_pressed();

    void on_escalaSlider_sliderPressed();

    void on_escalaSlider_sliderReleased();

    void on_escalaSlider_valueChanged(int value);

private:
    Ui::JanelaTranformador *ui;
    MeuFrame *frame;

    bool sliderEscalaPressionado = false;


};

#endif // JANELATRANFORMADOR_H
