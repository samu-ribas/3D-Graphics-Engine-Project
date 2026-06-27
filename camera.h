#ifndef CAMERA_H
#define CAMERA_H
#include "Forma.h"

class Camera : public Forma{
    public:
        Camera(double cx = 0.0, double cy = 0.0, double cz = 0.0);

        double getX() const;
        double getY() const;
        double getZ() const;
        double getAngulo() const;
        double getZoom() const;
        double getD() const;

        void setX(double valor);
        void setY(double valor);
        void setZ(double valor);
        void setAngulo(double valor);
        void setZoom(double z);
        void setD(double valor);

        void aumentarZoom();
        void diminuirZoom();
        void desenhar(QPainter &painter, const Matriz& mView, const Matriz& mProj, const Viewport& win, double zoom) override;
    private:
        double x, y, z; //atributos de posição (View Reference Point)
        double angulo; //atributos de orientação em graus (Pitch, Yaw, Roll)
        double zoom;
        double d; // Distância focal (será usada na perspectiva)
    };
#endif // CAMERA_H