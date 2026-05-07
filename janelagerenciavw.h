#ifndef JANELAGERENCIAVW_H
#define JANELAGERENCIAVW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "meuframe.h"
#include "window.h"
#include "viewport.h"


namespace Ui {
class JanelaViewportWindow;
}

class JanelaViewportWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::JanelaViewportWindow *ui;

    QList<Janela*> listaJanela;
    QList<Viewport*> listaViewport;

    MeuFrame *frame;

    Viewport *buscar_viewport( QString nome );

    Janela *buscar_window( QString nome );

public:
    explicit JanelaViewportWindow( QWidget *parent = nullptr, MeuFrame *frame = nullptr );
    ~JanelaViewportWindow();

private slots:
    void on_criarViewport_pressed();
    void on_criarWindow_pressed();
    void on_windowAtivador_currentTextChanged(const QString &arg1);
};

#endif // JANELAGERENCIAVW_H
