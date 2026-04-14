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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Forma*> formas;

};

#endif // MEUFRAME_H
