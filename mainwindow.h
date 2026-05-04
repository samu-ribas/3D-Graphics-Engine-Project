#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void processarPoligono(double x, double y, int l, double r); // polígono
    void processarPoligono(double x, double y, double c, double h); // retângulo
    void inputOperacao();

private slots:
    void inputObjeto();

private:
    Ui::MainWindow *ui;
    double deslocamentoWindow = 50.0;
};
#endif // MAINWINDOW_H
