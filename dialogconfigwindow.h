#ifndef DIALOGCONFIGWINDOW_H
#define DIALOGCONFIGWINDOW_H

#include <QDialog>

namespace Ui {
class DialogConfigWindow;
}

class DialogConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfigWindow(QWidget *parent = nullptr);
    ~DialogConfigWindow();
    double getLarguraDigitada() const;
    double getAlturaDigitada() const;
    void setDisplay(double largAtual, double altAtual);
    void setDimensoes();
    void cancelar();
private:
    Ui::DialogConfigWindow *ui;
    double largura, altura;
};

#endif // DIALOGCONFIGWINDOW_H
