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

    void atualizar_display_valores_window(Janela *window);
    void atualizar_display_valores_viewport(Viewport *viewport);


public:
    explicit JanelaViewportWindow( QWidget *parent = nullptr, MeuFrame *frame = nullptr );
    ~JanelaViewportWindow();

private slots:
    void on_criarViewport_pressed();
    void on_criarWindow_pressed();
    void on_windowAtivador_currentTextChanged(const QString &arg1);

    void on_viewportAtivador_currentTextChanged(const QString &arg1);
    void on_windowDiminuir_pressed();
    void on_windowAumentarTamanho_pressed();
    void on_viewportDiminuir_pressed();
    void on_viewportAumentar_pressed();
    void on_viewportEsquerda_pressed();
    void on_viewportDireita_pressed();
    void on_viewportSubir_pressed();
    void on_viewportDecer_pressed();
    void on_viewportRotacaAntihorario_pressed();
    void on_viewportRotacaHorario_pressed();
};

#endif // JANELAGERENCIAVW_H
