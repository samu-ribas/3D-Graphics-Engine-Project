#ifndef DIALOGVIEWPORT_H
#define DIALOGVIEWPORT_H

#include <QDialog>

namespace Ui {
class DialogViewport;
}

class DialogViewport : public QDialog
{
    Q_OBJECT

public:
    explicit DialogViewport(QWidget *parent = nullptr);
    ~DialogViewport();

    double getLarguraDigitada() const;
    double getAlturaDigitada() const;
    double getXDigitado() const;
    double getYDigitado() const;

    void setDisplay(double largAtual, double altAtual, double xAtual, double yAtual);
    void setDimensoes();
    void cancelar();

private:
    Ui::DialogViewport *ui;
    double largura, altura, x, y;

};

#endif // DIALOGVIEWPORT_H
