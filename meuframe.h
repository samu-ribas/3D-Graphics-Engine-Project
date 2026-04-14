#ifndef MEUFRAME_H
#define MEUFRAME_H

#include <QFrame>
#include <QVector>
#include <QMouseEvent> // Necessário
#include "forma.h"

class MeuFrame : public QFrame
{
    Q_OBJECT
public:
    explicit MeuFrame(QWidget *parent = nullptr);
    ~MeuFrame();
   void adicionarPonto(int x, int y);
/*
public slots:
    void atualizarEspessuraSelecionada(int novaEspessura);

signals:
    void formaSelecionada(int espessuraDaForma);
*/
protected:
    void paintEvent(QPaintEvent *event) override;
    /*

    void mousePressEvent(QMouseEvent *event) ;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    */
private:
    QVector<Forma*> formas;
    //Forma* m_formaSelecionada = nullptr;
    //bool m_arrastando = false;
};

#endif // MEUFRAME_H
