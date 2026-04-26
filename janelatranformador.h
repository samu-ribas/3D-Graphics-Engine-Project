#ifndef JANELATRANFORMADOR_H
#define JANELATRANFORMADOR_H

#include <QMainWindow>
#include "forma.h"

namespace Ui {
class JanelaTranformador;
}

class JanelaTranformador : public QMainWindow
{
    Q_OBJECT

public:
    explicit JanelaTranformador(QWidget *parent = nullptr, QVector<Forma*> *df = nullptr);
    ~JanelaTranformador();

private slots:
    void on_botaoTranformar_pressed();

private:
    Ui::JanelaTranformador *ui;
    QVector<Forma*> *df;
};

#endif // JANELATRANFORMADOR_H
