#ifndef MEUFRAME_H
#define MEUFRAME_H

#include <QFrame>
#include <QVector>
#include "forma.h"

class MeuFrame : public QFrame
{
    Q_OBJECT
public:
    explicit MeuFrame(QWidget *parent = nullptr);
    ~MeuFrame();
   void adicionarPonto(QString nome, double x, double y);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Forma*> displayFile;
};

#endif // MEUFRAME_H
