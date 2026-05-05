#ifndef JANELAGERENCIAVW_H
#define JANELAGERENCIAVW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "meuframe.h"
#include "janela.h"
#include "viewport.h"


namespace Ui {
class JanelaViewportWindow;
}

class JanelaViewportWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::JanelaViewportWindow *ui;

    QVector<Janela*> listaJanela;
    QVector<Viewport*> listaViewport;

    MeuFrame *frame;

protected:
    void closeEvent(QCloseEvent *event) override;
public:
    explicit JanelaViewportWindow(QWidget *parent = nullptr, MeuFrame *frame = nullptr);
    ~JanelaViewportWindow();

private slots:
    void on_pushButton_pressed();
};

#endif // JANELAGERENCIAVW_H
