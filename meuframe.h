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
    void adicionarReta(QString name, double x1, double y1, double x2, double y2);
    void adicionarPoligono(QString name, std::list<Coordenada> pontos);

    void transladarObjeto(QString n, double dx, double dy);
    void escalarObjeto(QString n, double sx, double sy);
    void rotacionarObjeto(QString nome, double angulo,double x, double y, bool usarCentroide);

    bool contemObjeto(const QString& nome) const;
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Forma*> displayFile;
};

#endif // MEUFRAME_H
