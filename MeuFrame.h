#ifndef MEUFRAME_H
#define MEUFRAME_H
#include <QFrame>
#include <QVector>
#include "Matriz.h"
#include "camera.h"

class MeuFrame : public QFrame
{
    Q_OBJECT
public:
    explicit MeuFrame(QWidget *parent = nullptr);
    ~MeuFrame();


    Viewport viewport;
    Camera camera;
    Matriz mView; // Transformação para Coordenadas de Câmera (Viewing)
    Matriz mProj; // Projeção Perspectiva e Mapeamento para SCN

    void adicionarPonto(QString nome, double x, double y);
    void adicionarReta(QString name, double x1, double y1, double x2, double y2);
    void adicionarPoligono(QString name, std::list<Coordenada> pontos);
    void adicionarModelo3D(QString nome, QString caminhoRecurso);
    void transladarObjeto(QString n, double dx, double dy, double dz);
    void escalarObjeto(QString n, double sx, double sy, double sz);
    void rotacionarObjeto(QString nome, double angulo,double x, double y, double z, char eixo, bool usarCentroide, bool usarCoordWindow);

    bool contemObjeto(const QString& nome) const;
    void recalcularSCN();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Forma*> displayFile;
};
#endif // MEUFRAME_H
